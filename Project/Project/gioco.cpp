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
	/*Metodo per sapere quale scritta � stata premuta restituisco un intero (compreso fra -1 e 2)
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
	if (key == sf::Keyboard::W) {
		nave_movimento_ = isPressed;

		//nave_.cambiaTextureMovimento(nave_movimento_);
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
	else if (key == sf::Keyboard::Down) {
		nave_raggio_ = isPressed;
	}
}

void Gioco::movimentoNavicella()
{
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
	if (nave_spara_) {
		nave_.spara();
	}
}

void Gioco::controlloRaggio()
{
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

	if (direzione_universo != -1) {
		// Se � possibile spostare la navicella in un altro universo
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
		// Se � impossibile visitare l'universo nel quale si vuole accedere
		else {
			// Rimbalzo della navicella sul bordo dello schermo
			float deg_angolo = nave_.getRotation();
			float angolo = nave_.getRotation() * PI / 180;
			float s_x = cos(angolo);
			float s_y = sin(angolo);

			float new_angolo;
			if (direzione_universo == 1 || direzione_universo == 3) {
				new_angolo = asin(s_y * -1) * 180 / PI;
				if (s_x < 0) {
					new_angolo = 180 - (new_angolo);
				}
			}
			else {
				new_angolo = acos(s_x * -1) * 180 / PI;
				if (s_y < 0) {
					new_angolo = 270 - (new_angolo - 90);
				}
				
			}
			nave_.setRotation(new_angolo);
		}
	}
}

void Gioco::controlloPassaggioPianeta()
{
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
		float deg_angolo = nave_.getRotation();
		float angolo = nave_.getRotation() * PI / 180;
		float s_x = cos(angolo);
		float s_y = sin(angolo);

		float new_angolo = acos(s_x * -1) * 180 / PI;

		if (s_y < 0) {
			new_angolo = 270 - (new_angolo - 90);
		}

		nave_.setRotation(new_angolo);

		nave_.setDannoCollisione();
	}
}

void Gioco::controlloCollisioneProiettili()
{
	// Vengono controllati i proiettili della Nave contro i Bunker (e viceversa)
	nave_.controlloProiettili(mappa_.getProiettili());

	//Viene restituiro un intero dato che ad uno stesso ciclo possono essere stati colpiti piu bunker

	int numeroBunkerColpiti = 0;
		numeroBunkerColpiti = mappa_.controlloProiettili(nave_.getProiettili());
		punteggio_ += numeroBunkerColpiti;
}

void Gioco::controlloCollisioneProiettiliSuperficie()
{
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

	if (nave_.getDistrutto()) {
		stato_ = GAMEOVER;
		schermata_scritte_.setGameOver();
	}
}

void Gioco::update()
{
	if (stato_ == UNIVERSO) {
		controlloGameOver();

		controlloPassaggioSistemaSolare();
		controlloPassaggioPianeta();

		movimentoNavicella();
	}
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
	window_.clear(sf::Color::Black);

	if (stato_ == UNIVERSO || stato_ == PIANETA) {
		// TODO: SPOSTARE IN UN ALTRA FUNZIONE DI GESTIONE DEL GIOCO
		schermata_scritte_.aggiornaTesto("VITA: ", nave_.getVita());
		schermata_scritte_.aggiornaTesto("CARBURANTE: ", nave_.getCarburante());

		window_.draw(mappa_);
		nave_.drawComportamento(window_, sf::RenderStates());

		window_.draw(pausa_);
		window_.draw(schermata_scritte_.getPunteggio());
		window_.draw(schermata_scritte_.getVita());
		window_.draw(schermata_scritte_.getCarburante());
	}
	else {
		window_.draw(schermata_scritte_.getTitolo());
		window_.draw(schermata_scritte_.getStart());
		window_.draw(schermata_scritte_.getExit());
		window_.draw(schermata_scritte_.getSubtitle());

		if(stato_ != START)
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
	pausa_.setSize(sf::Vector2f(61.8, 64.0));
	texture_.loadFromFile("Texture/pausa2.png");
	texture_.setSmooth(true);
	pausa_.setFillColor(sf::Color::Color(255,255,255,160));
	pausa_.setTexture(&texture_);

	punteggio_ = 0;
	schermata_scritte_.aggiornaTesto("PUNTEGGIO: ", punteggio_);

	float pausa_size = schermata_scritte_.getPunteggio().getGlobalBounds().height + 15;
	pausa_.setSize(sf::Vector2f(pausa_size, pausa_size));
	pausa_.setPosition(LARGHEZZA - pausa_.getSize().x, 0);

	nave_movimento_ = false;
	nave_rotazioneL_ = false;
	nave_rotazioneR_ = false;
	nave_spara_ = false;
	nave_raggio_ = false;
	restart_ = false;

	posizione_entrata_pianeta_ = sf::Vector2f(); // posizione della nave prima di entrare nel pianeta

	time_frame_ = sf::seconds(1.f / 144.f);

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
			/*restart_ � a true se ho perso e ho premuto restart nel menu apposito. Vengono quindi reinizializzate
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