#include "gioco.hpp"
#include <stdlib.h>
#include <iostream>

void Gioco::processaEventi()
{
	/* Vengono gestiti gli input da parte dell'utente, 
	per poter controllare le azioni dell'astronave */
	sf::Event event;

	while (window_.pollEvent(event)) {

		switch (event.type) {
			case sf::Event::Closed: window_.close();
				break;
			case sf::Event::KeyPressed: 
				gestisciMovimentoNave(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				gestisciMovimentoNave(event.key.code, false);
			break;

		case sf::Event::MouseMoved: {
			gestisciMouse();
		}
			break;
		case sf::Event::MouseButtonPressed:
			mouseClick(sf::Mouse::Button::Left);
			break;
		}
	}
}

void Gioco::mouseClick(sf::Mouse::Button bottoneMouse) {
	/*Metodo per la gestione del click del mouse nei menu di inizio, pausa e restart*/

	int gestione_mouse_ = gestisciMouse();

	//caso exit: chiudo il gioco
	if (bottoneMouse == sf::Mouse::Button::Left && gestione_mouse_ == 1) {
		window_.close();
	}
	//caso start, restart o resume
	else if (bottoneMouse == sf::Mouse::Button::Left && gestione_mouse_ == 0) {

		std::string stringa_start_ = schermata_scritte_.getStart().getString();
		//compare torna 0 se le due stringhe sono uguali

		//caso restart: reinizializzo gli attributi e richiamo il restart di mappa e nave
		if (stringa_start_.compare("RESTART") == 0) {
			mappa_.restart(LARGHEZZA, ALTEZZA);
			punteggio_ = 0;
			nave_.restart(100, sf::Vector2f(100, 100), 0, 10, false);
			stato_ = UNIVERSO;
			schermata_scritte_.setPunteggio();
			schermata_scritte_.aggiornaTesto("PUNTEGGIO: ", punteggio_);
			nave_movimento_ = false;
			nave_rotazioneL_ = false;
			nave_rotazioneR_ = false;
			nave_spara_ = false;
			nave_raggio_ = false;
			restart_ = true;
			posizione_entrata_pianeta_ = sf::Vector2f();
		}
		//caso start: il gico ha inizio
		else if (stringa_start_.compare("START") == 0) {
			stato_ = UNIVERSO;
		}
		//caso resume: riprendo il gioco dopo la pausa
		else if (stringa_start_.compare("RESUME") == 0) {
			stato_ = salva_stato_;
			schermata_scritte_.setPunteggio();
		}
		schermata_scritte_.setStart();
	}
	//caso pausa: metto il gioco in pausa
	else if (gestione_mouse_ == 2) {
		salva_stato_ = stato_;
		stato_ = PAUSA;
		schermata_scritte_.setPausa();
	}
	
	
}

int Gioco::gestisciMouse() {
	/*Metodo per sapere quale scritta è stata premuta restituisco un intero (compreso fra -1 e 2)
	-1: non ho cliccato nulla
	 0: ho cliccato il pulsante di start, restart o resume
	 1: ho cliccato il pulsante di exit
	 2: ho cliccato il pulsante di pausa
	 */
	sf::Vector2i posizione_mouse_ = sf::Mouse::getPosition(window_);
	int pulsante_premuto_ = -1;

	if (stato_ == GAMEOVER || stato_ == PAUSA || stato_ == START) {
		pulsante_premuto_ = schermata_scritte_.gestioneMouse(posizione_mouse_);
	}
	else {
		if (pausa_.getGlobalBounds().contains(posizione_mouse_.x, posizione_mouse_.y)) {
			pulsante_premuto_ = 2;
			pausa_.setFillColor(sf::Color::Color(255, 255, 255, 255));
		}
		else
			pausa_.setFillColor(sf::Color::Color(255, 255, 255, 160));
	}
	return pulsante_premuto_;

}

void Gioco::gestisciMovimentoNave(sf::Keyboard::Key key, bool isPressed)
{
	/* Questa funzione si occupa di impostare i booleani per la gestione
	della nave come veri, se è stato premuto il pulsante associato, oppure falsi
	Questi booleani verrano poi utilizzati quando verrà verificato se effettuare
	o meno un determinato movimento */

	if (key == sf::Keyboard::W) {
		nave_movimento_ = isPressed;
	}
	else if (key == sf::Keyboard::A) {
		nave_rotazioneL_ = isPressed;
	}
	else if (key == sf::Keyboard::D) {
		nave_rotazioneR_ = isPressed;
	}
	else if (key == sf::Keyboard::Space) {
		nave_spara_ = isPressed;
	}
	else if (key == sf::Keyboard::R) {
		nave_raggio_ = isPressed;
	}
}

void Gioco::movimentoNavicella()
{
	/* Viene gestito il movimento dell'astronave e la sua rotazione, quest'ultima
	viene effettuata solo se il booleano della relativa rotazione è vero*/

	// Viene passato sia il booleano (per determinare se muoverla) che il framerate
	nave_.muovi(time_frame_, nave_movimento_);

	if (nave_rotazioneL_) {
		nave_.ruotaSinistra();
	}
	if (nave_rotazioneR_) {
		nave_.ruotaDestra();
	}
}

void Gioco::controlloSparo()
{
	/* Viene effettuato lo sparo dell'astronave solo se
	è attivato il booleano */
	if (nave_spara_) {
		nave_.spara();
	}
}

void Gioco::controlloRaggio()
{
	/* Viene gestita l'attivazione del raggio traente, passando
	il booleano alla funzione dell'astronave che se ne occupa, per poi
	determinare se un oggetto è stato assorbito, e nel caso effettuare
	l'incremento del relativo parametro */
	nave_.attivaRaggio(nave_raggio_);

	if (nave_raggio_) {

		Tipologia oggetto_assorbito = DEFAULT;
		oggetto_assorbito = mappa_.controlloRaggio(nave_.getRaggio());

		if (oggetto_assorbito != DEFAULT) {

			if (oggetto_assorbito == CUORE) {
				nave_.aggiungiVita(oggetto_assorbito);
			}
			else {
				nave_.riempiCarburante(oggetto_assorbito);
			}
		}
		
	}
}

void Gioco::controlloPassaggioSistemaSolare()
{	
	/* Viene effettuato il controllo per il passaggio da un sistema solare
	ad un altro. Per questo motivo vengono prima di tutto determinati i punti della
	parte anteriore dell'astronave. Dopo di che, in base alla posizione, viene determinato
	verso quale direzione effettuare il passaggio. */
	sf::VertexArray punti = nave_.getPosizioneFrontale();

	int direzione_universo = -1;

	int i = 0;
	while (i < punti.getVertexCount() && direzione_universo == -1)
	{
		if (punti[i].position.x >= LARGHEZZA) direzione_universo = 1;
		else if (punti[i].position.x <= 0) direzione_universo = 3;
		else if (punti[i].position.y >= ALTEZZA) direzione_universo = 2;
		else if (punti[i].position.y <= 0) direzione_universo = 0;

		i++;
	}

	/* Nel caso debba essere effettuato uno spostamento (se possibile), questa condizione
	restituirà vero. */
	if (direzione_universo != -1) {
		/* Se è possibile spostare la navicella in un altro sistema solare, allora
		verrà aggiornata la nuova posizione per permettere un movimento
		naturale dell'astronave */
		if (mappa_.spostamentoSistemaSolare(direzione_universo)) {
			switch (direzione_universo)
			{
			case 0: nave_.passaggioAmbiente(sf::Vector2f(nave_.getPosition().x, ALTEZZA - nave_.getSize().y));
				break;
			case 1: nave_.passaggioAmbiente(sf::Vector2f(nave_.getSize().x, nave_.getPosition().y));
				break;
			case 2: nave_.passaggioAmbiente(sf::Vector2f(nave_.getPosition().x, nave_.getSize().y));
				break;
			case 3: nave_.passaggioAmbiente(sf::Vector2f(LARGHEZZA - nave_.getSize().x, nave_.getPosition().y));
			default:
				break;
			}
		}
		/*  Nel caso non sia possibile accedere al sistema solare, allora verrà
		calcolata una nuova posizione della navicella per simulare un rimbalzo sul bordo */
		else {
			// Calcolo per il rimbalzo della navicella sul bordo dello schermo
			float angolo = nave_.getRotation() * PI / 180; // angolo in radianti
			float s_x = cos(angolo);
			float s_y = sin(angolo);

			float nuovo_angolo;
			// Nel caso il rimbalzo debba essere effettuato lungo l'asse X
			if (direzione_universo == 1 || direzione_universo == 3) {
				nuovo_angolo = asin(s_y * -1) * 180 / PI;
				if (s_x < 0) {
					nuovo_angolo = 180 - (nuovo_angolo);
				}
			}
			// Nel caso il rimbalzo debba essere effettuato lungo l'asse Y
			else {
				nuovo_angolo = acos(s_x * -1) * 180 / PI;
				if (s_y < 0) {
					nuovo_angolo = 270 - (nuovo_angolo - 90);
				}
				
			}
			nave_.setRotation(nuovo_angolo); // viene impostato il nuovo angolo
		}
	}
}

void Gioco::controlloPassaggioPianeta()
{
	/* Viene effettuato il controllo per entrare devo un pianeta, per questo
	deve essere ottenuta la posizione frontale dell'astronave, per poi verificare 
	se la sua posizione coincide con il pianeta. Nel caso si verificasse questa
	condizione, viene aggiornato il nuovo stato del gioco, su PIANETA, per poi
	cambiare la posizione dell'astronave, solo dopo aver salvato la posizione precedente
	(da riutilizzare nell'uscita del pianeta) */
	sf::VertexArray punti = nave_.getPosizioneFrontale();

	bool entrata_pianeta = false;

	int i = 0;
	while (i < punti.getVertexCount() && !entrata_pianeta)
	{
		entrata_pianeta = mappa_.ricercaPianeta(punti[i].position);
		i++;
	}

	if (entrata_pianeta) {
		stato_ = PIANETA;
		posizione_entrata_pianeta_ = sf::Vector2f(punti[0].position.x - 2 * nave_.getSize().x, punti[0].position.y - 2 * nave_.getSize().y);
		
		nave_.setRotation(180); // la nave punta verso SUD
		nave_.passaggioAmbiente(sf::Vector2f(LARGHEZZA / 2, 80));
	}
}

void Gioco::controlloUscitaPianeta()
{
	/* Viene gestita l'uscita dal pianeta, controllando se la posizione
	dell'astronave è vicina al bordo superiore. In tal caso viene cambiato lo stato,
	da PIANETA a UNIVERSO, per poi aggiornare la posizione dell'astronave a quella
	precedente all'entrata nel pianeta.*/
	sf::VertexArray punti = nave_.getPosizioneFrontale();

	bool uscita_pianeta = false;

	int i = 0;
	while (i < punti.getVertexCount() && !uscita_pianeta)
	{
		if (punti[i].position.y <= 0) uscita_pianeta = true;

		i++;
	}

	if (uscita_pianeta) {
		stato_ = UNIVERSO;
		mappa_.uscitaPianeta();

		nave_.passaggioAmbiente(posizione_entrata_pianeta_);

		posizione_entrata_pianeta_ = sf::Vector2f();
	}
}

void Gioco::controlloPassaggioSuperficie()
{
	/* Viene gestito il passaggio da una superficie ad un'altra
	(sono 3 in totale su un singolo pianeta), controllando se la posizione
	della navicella è vicina al bordo sinistro oppure destro.*/
	sf::VertexArray punti = nave_.getPosizioneFrontale();

	int direzione = -1;

	int i = 0;
	while (i < punti.getVertexCount() && direzione == -1)
	{
		direzione = mappa_.controlloPassaggioSuperficie(punti[i].position);
		i++;
	}

	if (direzione != -1) {
		int offset = nave_.getSize().x;
		if (direzione == 0) {
			nave_.passaggioAmbiente(sf::Vector2f(LARGHEZZA -offset, nave_.getPosition().y));
		}
		else {
			nave_.passaggioAmbiente(sf::Vector2f(offset, nave_.getPosition().y));
		}
	}
}

void Gioco::controlloCollisioneSuperficie()
{
	/* Viene controllato se l'astronave ha toccato il bordo della superficie, 
	in tal caso viene effettuato un rimbalzo della nave, per poi diminuire la sua vita*/
	sf::VertexArray punti = nave_.getPosizioneFrontale();

	bool collisione_superficie = false;

	int i = 0;
	while (i < punti.getVertexCount() && !collisione_superficie)
	{
		collisione_superficie = mappa_.controlloCollisioneSuperficie(punti[i].position);
		i++;
	}

	if (collisione_superficie) {
		// La nave viene fatta rimbalzare
		float angolo = nave_.getRotation() * PI / 180;
		float s_x = cos(angolo);
		float s_y = sin(angolo);

		float new_angolo = acos(s_x * -1) * 180 / PI;

		if (s_y < 0) {
			new_angolo = 270 - (new_angolo - 90);
		}

		nave_.setRotation(new_angolo);

		nave_.setDannoCollisione(); // viene diminuita la vita a causa della collisione
	}
}

void Gioco::controlloCollisioneProiettili()
{
	// Vengono controllati i proiettili della Nave contro i Bunker (e viceversa)
	nave_.controlloProiettili(mappa_.getProiettili());

	//Viene restituito un intero dato che ad uno stesso ciclo possono essere stati colpiti piu bunker
	int numeroBunkerColpiti = 0;
	numeroBunkerColpiti = mappa_.controlloProiettili(nave_.getProiettili());
	punteggio_ += numeroBunkerColpiti;
}

void Gioco::controlloCollisioneProiettiliSuperficie()
{
	/* Viene ottenuta una lista ausiliaria contenente i proiettili
	dell'astronave. Per ogni proiettile viene controllato se la sua posizione
	è contenuta all'interno della superficie, in caso positivo esso viene eliminato*/
	proiettile_ptr lista_p = nave_.getProiettili();

	while (lista_p != nullptr)
	{
		sf::Vector2f posizione_proiettile = (*lista_p->proiettile).getPosition();

		if (mappa_.controlloCollisioneSuperficie(posizione_proiettile))
			lista_p = nave_.eliminaProiettile(lista_p);
		else
			lista_p = lista_p->next;
	}
}

void Gioco::controlloAggiornamentoPunteggio() {
	/*Viene aggiornato il punteggio*/

	if (mappa_.aggiornaPunteggioBunker()) {
		punteggio_ += 9;
	}
	else if (mappa_.aggiornaPunteggioPianeta()) {
			punteggio_ += 49;
	}
	else if (mappa_.aggiornaPunteggioUniverso()) {
		punteggio_ += 99;
	}
	schermata_scritte_.aggiornaTesto("PUNTEGGIO: ", punteggio_);

}

void Gioco::controlloGameOver() {
	/* Se la nave è distrutta, ossia se ha finito
	il carburante oppure la vita, il gioco termina e viene
	mostrata la schermata di gameover */

	if (nave_.getDistrutto()) {
		stato_ = GAMEOVER;
		schermata_scritte_.setGameOver();
	}
}

void Gioco::update()
{
	// Nel caso l'astronave si trovi nell'Universo
	if (stato_ == UNIVERSO) {
		controlloGameOver();

		controlloPassaggioSistemaSolare();
		controlloPassaggioPianeta();

		movimentoNavicella();
	}
	// Nel caso l'astronave si trovi nel Pianeta
	else if (stato_ == PIANETA) {
		controlloGameOver();
		controlloAggiornamentoPunteggio();

		controlloUscitaPianeta();

		controlloPassaggioSuperficie();
		controlloCollisioneSuperficie();

		controlloCollisioneProiettili();
		controlloCollisioneProiettiliSuperficie();

		movimentoNavicella();
		controlloSparo();

		controlloRaggio();
	}
}

void Gioco::render()
{
	window_.clear(sf::Color::Black); // vengono eliminati i render precedenti

	// Se l'astronave è ancora in gioco (ossia nell'Universo o nel Pianeta)
	if (stato_ == UNIVERSO || stato_ == PIANETA) {
		// Vengono aggiornati i valori relativi alla vita e al carburante
		schermata_scritte_.aggiornaTesto("VITA: ", nave_.getVita());
		schermata_scritte_.aggiornaTesto("CARBURANTE: ", nave_.getCarburante());

		// Viene mostrata l'attuale schermata (che sia il sistema solare oppure il pianeta)
		window_.draw(mappa_);
		nave_.drawComportamento(window_, sf::RenderStates()); // Viene mostrata l'astronave

		// Vengono disegnati il "bottone" per la pausa, il punteggio, la vita e il carburante
		window_.draw(pausa_);
		window_.draw(schermata_scritte_.getPunteggio());
		window_.draw(schermata_scritte_.getVita());
		window_.draw(schermata_scritte_.getCarburante());
	}
	// Nel caso in cui il gioco sia in pausa, nel menù o in schermata di gameover
	else { 
		window_.draw(schermata_scritte_.getTitolo());
		window_.draw(schermata_scritte_.getStart());
		window_.draw(schermata_scritte_.getExit());
		window_.draw(schermata_scritte_.getSubtitle());

		if (stato_ != START)
		window_.draw(schermata_scritte_.getPunteggio());
	}
	window_.display();
}

Gioco::Gioco() :
	window_(sf::VideoMode(LARGHEZZA, ALTEZZA), "Not-Gravitar", sf::Style::Default, sf::ContextSettings(0, 0, 8))
	, nave_(LARGHEZZA, ALTEZZA, 100, 10, "Texture/ship_1.png", "Texture/ship_1d.png",
		sf::Vector2f(50, 50), sf::Vector2f(52, 52), 0, 300, 2.f, 10)
	, mappa_(LARGHEZZA, ALTEZZA)
	,schermata_scritte_(LARGHEZZA, ALTEZZA)
{
	// Pausa opera come un bottone, nonostante sia una shape con la propria texture
	pausa_.setSize(sf::Vector2f(61.8, 64.0));
	texture_.loadFromFile("Texture/pausa2.png");
	texture_.setSmooth(true);
	pausa_.setFillColor(sf::Color(255,255,255,160));
	pausa_.setTexture(&texture_);

	float pausa_size = schermata_scritte_.getPunteggio().getGlobalBounds().height + 15;
	pausa_.setSize(sf::Vector2f(pausa_size, pausa_size));
	pausa_.setPosition(LARGHEZZA - pausa_.getSize().x, 0);

	punteggio_ = 0; // viene impostato il punteggio a 0
	schermata_scritte_.aggiornaTesto("PUNTEGGIO: ", punteggio_);

	// Vengono impostati a falso i booleani relativi ai movimenti e le azioni dell'astronave
	nave_movimento_ = false;
	nave_rotazioneL_ = false;
	nave_rotazioneR_ = false;
	nave_spara_ = false;
	nave_raggio_ = false;

	restart_ = false; // booleano per riavviare il gioco una volta terminato (se desiderato dall'utente)

	posizione_entrata_pianeta_ = sf::Vector2f(); // posizione della nave prima di entrare nel pianeta

	time_frame_ = sf::seconds(1.f / 144.f); // frametime

	// Lo stato iniziale sarà il menù
	stato_ = START;
}

void Gioco::avviaGioco()
{
	/*
	In questa funzione vengono richiamati i principali metodi
	per la gestione del gioco, ossia processaEventi, update e render
	*/
	sf::Clock refresh_;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (window_.isOpen()) {
			/*restart_ è a true se ho perso e ho premuto restart nel menu apposito. Vengono quindi reinizializzate
			le variabili refresh_ e timeSinceLastUpdate*/
			if (restart_) {
				refresh_.restart();
				timeSinceLastUpdate = sf::Time::Zero;
				restart_ = false;
			}

			processaEventi();

			timeSinceLastUpdate += refresh_.restart();
			/*
			Questa condizione serve per garantire che il gioco
			sia aggiornato con un framerate costante*/
			if (timeSinceLastUpdate > time_frame_) {
				timeSinceLastUpdate -= time_frame_;
				processaEventi();
				update();
			}
			
			render();
	}
}