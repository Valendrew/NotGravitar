#include "gioco.hpp"
#include <iostream>

void Gioco::gestioneEventi(Nave nave, Mappa mappa)
{
	
}

Gioco::Gioco()
{
	eventi_H = nullptr;
	eventi_T = nullptr;
}

void Gioco::avviaGioco()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	Mappa mappa = Mappa(LARGHEZZA, ALTEZZA);
	Nave nave = Nave();
	sf::RenderWindow window(sf::VideoMode(LARGHEZZA, ALTEZZA), "Test", sf::Style::Default, settings);
	bool tornaUniverso = true;
	sf::Vector2f f;
	bool flag[3] = { false, false, false };

	sf::Clock clock;
	while (window.isOpen()) {
		sf::Event event;
 		while (window.pollEvent(event)) {
   			switch (event.type)
			{
			case sf::Event::Closed: window.close();
				break;
			case sf::Event::KeyPressed:
			{
				if (event.key.code == sf::Keyboard::Space) {
					//nave.muovi();
					flag[0] = true;
				}
				if (event.key.code == sf::Keyboard::A) {
					//nave.ruotaL();
					flag[1] = true;
				}
				if (event.key.code == sf::Keyboard::D) {
					flag[2] = true;
					//nave.ruotaR();
				}
				if (event.key.code == sf::Keyboard::F) {
					nave.spara(nave.getRotazione());
				}
			}; break;
			case sf::Event::KeyReleased:
			{
				if (event.key.code == sf::Keyboard::Space) {
					//nave.muovi();
					flag[0] = false;
				}
				if (event.key.code == sf::Keyboard::A) {
					//nave.ruotaL();
					flag[1] = false;
				}
				if (event.key.code == sf::Keyboard::D) {
					flag[2] = false;
					//nave.ruotaR();
				}
				if (event.key.code == sf::Keyboard::F) {
					nave.spara(nave.getRotazione());
				}
			}; break;
			default:
				break;
			}
 		}
		window.clear(sf::Color::Black);

		gestioneEventi(nave, mappa);

		sf::Int32 elapsedTime = clock.getElapsedTime().asMilliseconds();
		if (elapsedTime > 40) {
			if (flag[0]) {
				nave.muovi();
			}
			if (flag[1]) {
				nave.ruotaL();
			}
			if (flag[2]) {
				nave.ruotaR();
			}
			clock.restart();
		}

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
		}
		
		window.draw(mappa);
		window.draw(nave);
		window.display();

	}
}
