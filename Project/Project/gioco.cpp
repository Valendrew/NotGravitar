#include "gioco.hpp"
#include <iostream>

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
		}
	}
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

void Gioco::update()
{
	if (stato_ == UNIVERSO) {
		controlloPassaggioUniverso();
		controlloPassaggioPianeta();
	}
	else if (stato_ = PIANETA) {
		controlloUscitaPianeta();
		controlloCollisioneSuperficie();
		controlloCollisioneProiettili();
	}
	movimentoNavicella();
}

void Gioco::render()
{
	window_.clear(sf::Color::Black);
	window_.draw(mappa_);
	window_.draw(nave_);
	window_.display();
}

Gioco::Gioco() : 
	window_(sf::VideoMode(LARGHEZZA, ALTEZZA), "Not-Gravitar")
	, nave_(100, "Texture/ship3.png", LARGHEZZA/2, ALTEZZA/2, 35, 35, 0, 0.5, 0.3, 10)
	, mappa_(LARGHEZZA, ALTEZZA)
	, clock_()
{
	nave_movimento = false;
	nave_rotazioneL = false;
	nave_rotazioneR = false;
	nave_spara = false;
	collisione_nave = false;
	posizione_entrata_pianeta_ = sf::Vector2f(0, 0);

	stato_ = UNIVERSO;

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
