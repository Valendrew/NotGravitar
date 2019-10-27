#include "gioco.hpp"
#include <stdlib.h>
#include <iostream>

void Gioco::processaEventi()
{
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

	int gestioneMouse = gestisciMouse();
	if (bottoneMouse == sf::Mouse::Button::Left && gestioneMouse == 1) {
		window_.close();
	}
	else if (bottoneMouse == sf::Mouse::Button::Left && gestioneMouse == 0) {

		std::string stringa_start = schermataScritte.getStart().getString();
		//compare torna 0 se le due stringhe sono uguali
		if (stringa_start.compare("RESTART") == 0) {
			mappa_.restart(LARGHEZZA, ALTEZZA);
			punteggio_ = 0;
			nave_.restart(100, 100, 100, 0, 10, false);
			stato_ = UNIVERSO;
			schermataScritte.setPunteggio();
			schermataScritte.aggiornaTesto("PUNTEGGIO: ", punteggio_);
		}
		else if (stringa_start.compare("START") == 0) {
			stato_ = UNIVERSO;
		}
		else if (stringa_start.compare("RESUME") == 0) {
			stato_ = salva_stato_;
			schermataScritte.setPunteggio();
		}
		schermataScritte.setStart();
	}
	else if (gestioneMouse == 2) {
		salva_stato_ = stato_;
		stato_ = PAUSA;
		schermataScritte.SetPausa();
	}
	
	
}

int Gioco::gestisciMouse() {

	sf::Vector2i posizioneMouse = sf::Mouse::getPosition(window_);
	int pulsantePremuto = -1;

	if (stato_ == GAMEOVER || stato_ == PAUSA || stato_ == START) {
		pulsantePremuto = schermataScritte.gestioneMouse(posizioneMouse);
	}
	else {
		if (pausa_.getGlobalBounds().contains(posizioneMouse.x, posizioneMouse.y)) {
			pulsantePremuto = 2;
			pausa_.setFillColor(sf::Color::Color(255, 255, 255, 255));
		}
		else
			pausa_.setFillColor(sf::Color::Color(255, 255, 255, 160));
	}
	return pulsantePremuto;

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
	else if (key == sf::Keyboard::R) {
		nave_raggiotraente_ == isPressed;
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

void Gioco::controlloPassaggioUniverso()
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
		// Se è possibile spostare la navicella in un altro universo
		if (mappa_.spostamento(direzione_universo)) {
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
		// Se è impossibile visitare l'universo nel quale si vuole accedere
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
	}
}

void Gioco::controlloCollisioneProiettili()
{
	// Vengono controllati i proiettili della Nave contro i Bunker (e viceversa)
	nave_.controlloProiettili(mappa_.getProiettili());

	//Viene restituiro un intoro dato che ad uno stesso ciclo possono essere stati colpiti piu bunker

	//Somma 1 tante volte perche per piu render di fila da il bunker come colpito in quell'istante(?)
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
	if (mappa_.aggiornaPunteggioBunker()) {
		punteggio_ += 10;
	}
	else if (mappa_.aggiornaPunteggioPianeta()) {
			punteggio_ += 50;
	}
	else if (mappa_.aggiornaPunteggioUniverso()) {
		punteggio_ += 100;
	}
	schermataScritte.aggiornaTesto("PUNTEGGIO: ", punteggio_);

}

void Gioco::controlloGameOver() {

	if (nave_.getDistrutto()) {
		stato_ = GAMEOVER;
		schermataScritte.SetGameOver();
	}
}

void Gioco::update()
{
	if (stato_ == UNIVERSO) {
		controlloGameOver();

		controlloPassaggioUniverso();
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
	}
}

void Gioco::render()
{
	window_.clear(sf::Color::Black);

	if (stato_ == UNIVERSO || stato_ == PIANETA) {
		// TODO: SPOSTARE IN UN ALTRA FUNZIONE DI GESTIONE DEL GIOCO
		schermataScritte.aggiornaTesto("VITA: ", nave_.getVita());
		schermataScritte.aggiornaTesto("CARBURANTE: ", nave_.getCarburante());

		window_.draw(mappa_);
		nave_.drawComportamento(window_, sf::RenderStates());

		window_.draw(pausa_);
		window_.draw(schermataScritte.getPunteggio());
		window_.draw(schermataScritte.getVita());
		window_.draw(schermataScritte.getCarburante());
	}
	else {
		window_.draw(schermataScritte.getTitolo());
		window_.draw(schermataScritte.getStart());
		window_.draw(schermataScritte.getExit());
		window_.draw(schermataScritte.getSubtitle());

		if(stato_ != START)
		window_.draw(schermataScritte.getPunteggio());
	}
	window_.display();
}

Gioco::Gioco() :
	window_(sf::VideoMode(LARGHEZZA, ALTEZZA), "Not-Gravitar", sf::Style::Default, sf::ContextSettings(0, 0, 8))
	, nave_(LARGHEZZA, ALTEZZA, 100, 10, "Texture/ship_2.png", "Texture/ship_2d.png",
		sf::Vector2f(100, 100), sf::Vector2f(60, 60), 0, 300, 2.f, 10)
	, mappa_(LARGHEZZA, ALTEZZA)
	, clock_()
	,schermataScritte(LARGHEZZA, ALTEZZA)
{
	pausa_.setSize(sf::Vector2f(61.8, 64.0));
	texture_.loadFromFile("Texture/pausa2.png");
	texture_.setSmooth(true);
	pausa_.setFillColor(sf::Color::Color(255,255,255,160));
	pausa_.setTexture(&texture_);

	punteggio_ = 0;
	schermataScritte.aggiornaTesto("PUNTEGGIO: ", punteggio_);

	float pausa_size = schermataScritte.getPunteggio().getGlobalBounds().height + 15;
	pausa_.setSize(sf::Vector2f(pausa_size, pausa_size));
	pausa_.setPosition(LARGHEZZA - pausa_.getSize().x, 0);

	nave_movimento_ = false;
	nave_rotazioneL_ = false;
	nave_rotazioneR_ = false;
	nave_spara_ = false;
	nave_raggiotraente_ == false;

	posizione_entrata_pianeta_ = sf::Vector2f(); // posizione della nave prima di entrare nel pianeta

	time_frame_ = sf::seconds(1.f / 144.f);

	stato_ = START;
}

void Gioco::avviaGioco()
{
	sf::Clock refresh_;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (window_.isOpen()) {
			processaEventi();

			timeSinceLastUpdate += refresh_.restart();
			if (timeSinceLastUpdate > time_frame_) {
				timeSinceLastUpdate -= time_frame_;
				processaEventi();
				update();
			}
			
			render();
	}
}