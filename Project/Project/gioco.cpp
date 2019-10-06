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
		nave_.muovi(time_frame_);
	}
	if (nave_rotazioneL) {
		nave_.ruotaL();
	}
	if (nave_rotazioneR) {
		nave_.ruotaR();
	}
	if (nave_spara) {
		//if (clock_.getElapsedTime().asMilliseconds() > 200) {
			nave_.spara();
			//clock_.restart();
		//}
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

	if (direzione != -1) {
		if (mappa_.spostamento(direzione)) {
			switch (direzione)
			{
			case 0: nave_.setPosition(sf::Vector2f(nave_.getPosition().x, ALTEZZA - nave_.getDimensione().y));
				break;
			case 1: nave_.setPosition(sf::Vector2f(nave_.getDimensione().x, nave_.getPosition().y));
				break;
			case 2: nave_.setPosition(sf::Vector2f(nave_.getPosition().x, nave_.getDimensione().y));
				break;
			case 3: nave_.setPosition(sf::Vector2f(LARGHEZZA - nave_.getDimensione().x, nave_.getPosition().y));
			default:
				break;
			}
		}
		else {
			float deg_angolo = nave_.getRotation();
			float angolo = nave_.getRotation() * PI / 180;
			float s_x = cos(angolo);
			float s_y = sin(angolo);

			float new_angolo;
			if (direzione == 1 || direzione == 3) {
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

	bool check = mappa_.ricercaPianeta(punti[0].position.x, punti[0].position.y);
	if (!check) check = mappa_.ricercaPianeta(punti[1].position.x, punti[1].position.y);

	if (check) {
		stato_ = PIANETA;
		posizione_entrata_pianeta_ = sf::Vector2f(punti[0].position.x - 50, punti[0].position.y - 50);
		
		nave_.setRotation(180);
		nave_.setPosition(sf::Vector2f(LARGHEZZA / 2, 40));
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

		nave_.setPosition(posizione_entrata_pianeta_);
		posizione_entrata_pianeta_ = sf::Vector2f(0, 0);

		mappa_.uscitaPianeta();
	}
}

void Gioco::controlloPassaggioSuperficie()
{
	int direzione = -1;
	sf::VertexArray bordo = nave_.getPosizioneFrontale();

	int i = 0;

	while (i < bordo.getVertexCount() && direzione == -1)
	{
		direzione = mappa_.controlloPassaggioSuperficie(bordo[i].position);
		i++;
	}

	if (direzione != -1) {
		if (direzione == 0) {
			nave_.setPosition(sf::Vector2f(LARGHEZZA - nave_.getDimensione().x, nave_.getPosition().y));
		}
		else {
			nave_.setPosition(sf::Vector2f(nave_.getDimensione().x, nave_.getPosition().y));
		}
	}
}

void Gioco::controlloCollisioneSuperficie()
{
	bool collisione_superficie = false;
	sf::VertexArray bordo = nave_.getPosizioneFrontale();

	if (mappa_.controlloCollisioneSuperficie(bordo[0].position)) {
		collisione_superficie = true;
	}
	else if (mappa_.controlloCollisioneSuperficie(bordo[1].position)) {
		collisione_superficie = true;
	}

	if (collisione_superficie) {
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
	nave_.controlloProiettili(mappa_.getProiettili());
}

void Gioco::update()
{
	if (stato_ == UNIVERSO) {
		controlloPassaggioUniverso();
		controlloPassaggioPianeta();
	}
	else if (stato_ = PIANETA) {
		controlloUscitaPianeta();
		controlloPassaggioSuperficie();
		controlloCollisioneSuperficie();
	}
	//controlloCollisioneProiettili();
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
	, nave_(LARGHEZZA, ALTEZZA, 100, "Texture/ship3.png", sf::Vector2f(40, 40), sf::Vector2f(40, 40), 0, 450, 1.2f, 10)
	, mappa_(LARGHEZZA, ALTEZZA)
	, clock_()
{
	time_frame_ = sf::seconds(1.f / 240.f);
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
