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

void Gioco::gestioneEventi(sf::Int32 time)
{
	sf::Vector2f nave_pos = nave_.getPosizione();

	if (nave_pos.x > LARGHEZZA) {
		char tipo[100] = "BOUND_WIDTH";
		inserisciEvento(stato_, tipo, time);
	}
	if (nave_pos.x < 0) {
		char tipo[100] = "BOUND_WIDTH";
		inserisciEvento(stato_, tipo, time);
	}
	if (nave_pos.y > ALTEZZA) {
		char tipo[100] = "BOUND_HEIGHT";
		inserisciEvento(stato_, tipo, time);
	}
	if (nave_pos.y < 0) {
		char tipo[100] = "BOUND_HEIGHT";
		inserisciEvento(stato_, tipo, time);
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
		case sf::Event::KeyPressed:
			gestisciMovimentoNave(event.key.code, true);
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
}

void Gioco::update()
{
	if (nave_movimento) {
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

void Gioco::render()
{
	window_.clear(sf::Color::Black);
	window_.draw(mappa_);
	window_.draw(nave_);
	window_.display();
}

Gioco::Gioco() : 
	window_(sf::VideoMode(LARGHEZZA, ALTEZZA), "Not-Gravitar")
	, nave_(100, "Texture/ship3.png", LARGHEZZA/2, ALTEZZA/2, 35, 35, 0, 0.3, 0.15, 10)
	, mappa_(LARGHEZZA, ALTEZZA)
	, clock_()
{
	nave_movimento = false;
	nave_rotazioneL = false;
	nave_rotazioneR = false;
	nave_spara = false;

	stato_ = 'U';
	eventi_H = nullptr;
	eventi_T = nullptr;
}

void Gioco::avviaGioco()
{
	//bool tornaUniverso = true;
	//sf::Vector2f f;
	//bool flag[3] = { false, false, false };

	while (window_.isOpen()) {
		processaEventi();
		update();
		render();

		/*eventi_ptr e = eliminaEvento();
		if (e != nullptr) {
			aggiornaEvento(e);
		}

		gestioneEventi(clock.getElapsedTime().asMilliseconds());


		if (tornaUniverso) {
			if (mappa.ricercaPianeta(nave.getPosizione().x, nave.getPosizione().y)) {
				tornaUniverso = false;
				f.x = mappa.getPosizioneAttuale()->u->getPianetaAttuale()->pianeta_->getPosizione().x - 20;
				f.y = mappa.getPosizioneAttuale()->u->getPianetaAttuale()->pianeta_->getPosizione().y - 25;
			}
		}
		else {
			if (nave.getPosizione().y <= 0) {
				tornaUniverso = true;
				nave.setPosition(f);
			}
		}*/
	}
}
