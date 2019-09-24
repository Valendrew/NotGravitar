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
					nave.muovi();
				}
				if (event.key.code == sf::Keyboard::A) {
					nave.ruotaL();
				}
				if (event.key.code == sf::Keyboard::D) {
					nave.ruotaR();
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
