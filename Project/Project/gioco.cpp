#include "gioco.hpp"
#include <iostream>
#include <stdlib.h>

void Gioco::inserisciEvento(char stato_, char tipo[], sf::Int32 time)
{
	if (eventi_H == nullptr) {
		eventi_H = new Eventi;
		eventi_H->time = time;
		eventi_H->e.stato = stato_;
	
		int i = 0;
		while (tipo[i] != '\0' && i < 100) {
			eventi_H->e.tipo[i] = tipo[i];
			i++;
		}

		eventi_H->prev = nullptr;
		eventi_H->next = nullptr;

		eventi_T = eventi_H;
	}
	else {
		eventi_ptr tmp_e = new Eventi;
		tmp_e->time = time;
		tmp_e->e.stato = stato_;

		int i = 0;
		while (tipo[i] != '\0' && i < 100) {
			tmp_e->e.tipo[i] = tipo[i];
			i++;
		}

		tmp_e->next = eventi_H;
		tmp_e->prev = nullptr;
		eventi_H->prev = tmp_e;
		eventi_H = tmp_e;
		//delete tmp_e;
	}
}

Gioco::eventi_ptr Gioco::eliminaEvento()
{
	if (eventi_T != nullptr) {
		eventi_ptr e = eventi_T;
		eventi_T = eventi_T->prev;
		return e;
	}
	else {
		return nullptr;
	}
}

void Gioco::aggiornaEvento(eventi_ptr evento)
{
	switch (evento->e.stato)
	{
	default:
		break;
	}
}

void Gioco::processaEventi()
{
	sf::Event event;
	while (window_.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed: window_.close();
			break;
		case sf::Event::KeyPressed: {
				gestisciMovimentoNave(event.key.code, true);
		}
			break;
		case sf::Event::KeyReleased:
				gestisciMovimentoNave(event.key.code, false);
			break;

		case sf::Event::MouseMoved: {

			sf::Vector2i posizioneMouse;
			posizioneMouse.x = sf::Mouse::getPosition(window_).x;
			posizioneMouse.y = sf::Mouse::getPosition(window_).y;
			gestisciMouse(posizioneMouse);
		}
			break;
		case sf::Event::MouseButtonPressed: {

			mouseClick(sf::Mouse::Button::Left);
		}
			break;
		}

	
	}
}

void Gioco::mouseClick(sf::Mouse::Button bottoneMouse) {
	
	sf::Vector2i posizioneMouse;
	posizioneMouse.x = sf::Mouse::getPosition(window_).x;
	posizioneMouse.y = sf::Mouse::getPosition(window_).y;
	int gestioneMouse = gestisciMouse(posizioneMouse);
	if (bottoneMouse == sf::Mouse::Button::Left && gestioneMouse == 1) {
		window_.close();
	}
	else if (bottoneMouse == sf::Mouse::Button::Left && gestioneMouse == 0) {

		std::string app = start_.getString();
		//compare torna 0 se le due stringhe sono uguali
		if (!app.compare("RESTART")) {
			mappa_.restart(LARGHEZZA, ALTEZZA);
			nave_.restart(100, LARGHEZZA/2, ALTEZZA/2, 0, 10);
			stato_ = UNIVERSO;
			punteggio_text.setPosition(5, 0);
		}
		else if (!app.compare("START")) {
			stato_ = UNIVERSO;
		}
		else if (!app.compare("RESUME")) {
			stato_ = salva_stato;
		}
		//Le due linee seguenti servono per ridimensionare subito lo start, altrimenti una volata premuta la pausa si visualizzerebbe "RESUME" a dimensione 60
		//invece che 55 per un istante
		start_.setCharacterSize(55);
		start_.setPosition(LARGHEZZA / 2 - start_.getGlobalBounds().width / 2, ALTEZZA / 2);

	}
	else if (gestioneMouse == 2) { 
		stato_ = PAUSA;
	}
	
	
}
int Gioco::gestisciMouse(sf::Vector2i posizioneMouse) {

	int pulsantePremuto = -1;

	/*Grazie a questo booleano posso verificare che l'astronave non stia compiando azioni. Senza di esso se tengo premuto un pulsante di movimento
	mentre premo pausa, l'astronave continuerà comunque a muoversi*/
	bool nave_ferma = !(nave_movimento || nave_rotazioneL || nave_rotazioneR || nave_spara);

	if (stato_ == GAMEOVER || stato_ == PAUSA || stato_ == START) {
		if (start_.getGlobalBounds().contains(posizioneMouse.x, posizioneMouse.y)) {
			start_.setCharacterSize(60);
			pulsantePremuto = 0;
		}
		else {
			start_.setCharacterSize(55);
			if (exit_.getGlobalBounds().contains(posizioneMouse.x, posizioneMouse.y)) {
				exit_.setCharacterSize(60);
				pulsantePremuto = 1;
			}
			else exit_.setCharacterSize(55);
		}
		start_.setPosition(LARGHEZZA / 2 - start_.getGlobalBounds().width / 2, ALTEZZA / 2);
		exit_.setPosition(LARGHEZZA / 2 - exit_.getGlobalBounds().width / 2, ALTEZZA / 2 + 100);
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
		nave_movimento = isPressed;
	}
	else if (key == sf::Keyboard::A) {
		nave_rotazioneL = isPressed;
	}
	else if (key == sf::Keyboard::D) {
		nave_rotazioneR = isPressed;
	}
	else if (key == sf::Keyboard::Space) {
		nave_spara = isPressed;
	}
	else if (key == sf::Keyboard::G) {
		debug = isPressed;
	}
}

void Gioco::movimentoNavicella()
{
	if (nave_movimento && !collisione_nave) {
		nave_.muovi();
	}
	if (nave_rotazioneL) {
		nave_.ruotaL();
	}
	if (nave_rotazioneR) {
		nave_.ruotaR();
	}
	if (nave_spara) {
		if (clock_.getElapsedTime().asMilliseconds() > 200) {
			nave_.spara(nave_.getRotazione());
			clock_.restart();
		}
	}
}

void Gioco::controlloPassaggioUniverso()
{
	bool print = clock_.getElapsedTime().asMilliseconds() >= 2000;
	sf::VertexArray punti = nave_.getPosizioneFrontale();

	int direzione = -1;
	for (int i = 0; i < punti.getVertexCount(); i++)
	{
		if (punti[i].position.x >= LARGHEZZA) direzione = 1;
		else if (punti[i].position.x <= 0) direzione = 3;
		else if (punti[i].position.y >= ALTEZZA) direzione = 2;
		else if (punti[i].position.y <= 0) direzione = 0;
	}
	float rotazione = nave_.getRotazione();
	if (debug) {
		std::cout << "Punto L: " << punti[0].position.x << ", " << punti[0].position.y << ". PUNTO R: " << punti[1].position.x << ", " << punti[1].position.y << std::endl;
		std::cout << "ROTAZIONE: " << rotazione << std::endl << std::endl;
	}

	if (direzione != -1) {
		if (mappa_.spostamento(direzione)) {

			//se sposto mi sposto in un altro sistema solare ed è nuovo (non ci sono mai stato) allora setto nuovo_universo a true cosi da aggiornare
			//correttamente il punteggio quando lo avro distrutto
			if (mappa_.getPosizioneAttuale().x == mappa_.getPosizioneDiGioco().x && mappa_.getPosizioneAttuale().y == mappa_.getPosizioneDiGioco().y)
				nuovo_universo = true;

			switch (direzione)
			{
			case 0: nave_.setPosizione(sf::Vector2f(nave_.getPosizione().x, ALTEZZA - nave_.getDimensione().y));
				break;
			case 1: nave_.setPosizione(sf::Vector2f(nave_.getDimensione().x, nave_.getPosizione().y));
				break;
			case 2: nave_.setPosizione(sf::Vector2f(nave_.getPosizione().x, nave_.getDimensione().y));
				break;
			case 3: nave_.setPosizione(sf::Vector2f(LARGHEZZA - nave_.getDimensione().x, nave_.getPosizione().y));
			default:
				break;
			}
		}
		else {
			collisione_nave = true;
		}
	}
	else {
		collisione_nave = false;
	}
}

void Gioco::controlloPassaggioPianeta()
{
	sf::VertexArray punti = nave_.getPosizioneFrontale();

	bool check = mappa_.ricercaPianeta(punti[0].position.x, punti[0].position.y);
	if (!check) check = mappa_.ricercaPianeta(punti[1].position.x, punti[1].position.y);

	if (check) {
		stato_ = PIANETA;
		posizione_entrata_pianeta_ = sf::Vector2f(punti[0].position.x - 50, punti[0].position.y - 50);
	}
}

void Gioco::controlloUscitaPianeta()
{
	sf::VertexArray punti = nave_.getPosizioneFrontale();

	int direzione = -1;
	bool cambia_stato = false;
	for (int i = 0; i < punti.getVertexCount(); i++)
	{
		if (punti[i].position.y <= 0) cambia_stato = true;
	}
	if (cambia_stato) {
		stato_ = UNIVERSO;

		nave_.setPosizione(posizione_entrata_pianeta_);
		posizione_entrata_pianeta_ = sf::Vector2f(0, 0);

		mappa_.uscitaPianeta();
	}
}

void Gioco::controlloCollisioneSuperficie()
{
	sf::VertexArray bordo = nave_.getPosizioneFrontale();

	if (mappa_.controlloCollisioneSuperficie(bordo)) {
		collisione_nave = true;
	}
	else {
		collisione_nave = false;
	}
}

void Gioco::controlloCollisioneProiettili()
{
}
void Gioco::controlloDistruzioneBunker() {
	//quando un singolo bunker verra distrutto +10 punti, quando distruggo l'ultimo bunker +50 punti
}
void Gioco::controlloDistruzioneSistemaSolare() {
	if (mappa_.getUniversoDiGioco().distrutto() && nuovo_universo) {
		punteggio_ += 100;
		nuovo_universo = false;
	}
}

void Gioco::update()
{
	if (stato_ == UNIVERSO) {
		controlloDistruzioneSistemaSolare();
		controlloPassaggioUniverso();
		controlloPassaggioPianeta();
	}
	else if (stato_ == PIANETA) {
		controlloUscitaPianeta();
		controlloCollisioneSuperficie();
		controlloCollisioneProiettili();
		controlloDistruzioneBunker();
	}
	else if (stato_ == GAMEOVER) {
		start_.setString("RESTART");
		subtitle_.setString("GAME OVER");
		subtitle_.setPosition(LARGHEZZA / 2 - subtitle_.getGlobalBounds().width / 2, 140);
		start_.setPosition(LARGHEZZA / 2 - start_.getGlobalBounds().width / 2, ALTEZZA / 2);
		punteggio_text.setPosition(LARGHEZZA / 2 - punteggio_text.getGlobalBounds().width / 2, 210);
	}
	else if (stato_ == PAUSA) {
		start_.setString("RESUME");
		subtitle_.setString("");
		start_.setPosition(LARGHEZZA / 2 - start_.getGlobalBounds().width / 2, ALTEZZA / 2);

	}
	else if (stato_ == START) {
		start_.setString("START");
		subtitle_.setString("");
		start_.setPosition(LARGHEZZA / 2 - start_.getGlobalBounds().width / 2, ALTEZZA / 2);
		titolo_.setPosition(LARGHEZZA / 2 - titolo_.getGlobalBounds().width / 2, 10);
		exit_.setPosition(LARGHEZZA / 2 - exit_.getGlobalBounds().width / 2, ALTEZZA / 2 + 100);
	}
	//grazie a questo controllo la nave   smette di/non puo iniziare a   muoversi 
	if (stato_ == START || stato_ == PAUSA) {
		nave_movimento = false;
		nave_rotazioneL = false;
		nave_rotazioneR = false;
		nave_spara = false;
	}
	movimentoNavicella();
}

void Gioco::render()
{
	window_.clear(sf::Color::Black);
	if (stato_ == UNIVERSO || stato_ == PIANETA) {
		window_.draw(mappa_);
		window_.draw(nave_);
		window_.draw(pausa_);
		aggiornaPunteggio();
		window_.draw(punteggio_text);
	}
	else {
		window_.draw(titolo_);
		window_.draw(start_);
		window_.draw(exit_);
		window_.draw(subtitle_);
		if (stato_ == GAMEOVER)
			window_.draw(punteggio_text);
	}
	
	window_.display();
}

void Gioco::aggiornaPunteggio() {
	char app[30] = "Punteggio: ";
	char app2[10];
	_itoa_s(punteggio_, app2, 10, 10);
	strcat_s(app, app2);
	punteggio_text.setString(app);
}

Gioco::Gioco() :
	window_(sf::VideoMode(LARGHEZZA, ALTEZZA), "Not-Gravitar")
	, nave_(100, "Texture/ship3.png", LARGHEZZA / 2, ALTEZZA / 2, 35, 35, 0, 0.5, 0.3, 10)
	, mappa_(LARGHEZZA, ALTEZZA)
	, clock_()
	, punteggio_text("",32, sf::Color::Blue, sf::Color::Magenta, 1.5 ,5 ,0 ,1)
	,titolo_("NON GRAVITAR", 120, sf::Color::Red, sf::Color::Yellow, 1.5,0 , 0, 4)
	,subtitle_("",60, sf::Color::Red, sf::Color::Transparent, 1.5, 0, 0, 0)
	,start_("",55, sf::Color::Green, sf::Color::Transparent, 1.5, 0, 0, 0)
	,exit_("EXIT", 55, sf::Color::Magenta, sf::Color::Transparent, 1.5, 0, 0, 0)

{
	pausa_.setSize(sf::Vector2f(61.8, 64.0));
	texture_.loadFromFile("Texture/pausa2.png");
	texture_.setSmooth(true);
	pausa_.setFillColor(sf::Color::Color(255,255,255,160));
	pausa_.setTexture(&texture_);
	pausa_.setPosition(LARGHEZZA - pausa_.getSize().x, 0);

	punteggio_ = 0;
	aggiornaPunteggio();
	
	
	nuovo_universo = true;
	nave_movimento = false;
	nave_rotazioneL = false;
	nave_rotazioneR = false;
	nave_spara = false;
	collisione_nave = false;
	posizione_entrata_pianeta_ = sf::Vector2f(0, 0);

	stato_ = START;

	eventi_H = nullptr;
	eventi_T = nullptr;

	debug = false;
}


void Gioco::avviaGioco()
{
	while (window_.isOpen()) {
		processaEventi();
		update();
		render();
	}
}
