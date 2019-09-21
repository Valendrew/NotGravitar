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

	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type)
			{
			case sf::Event::Closed: window.close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Space) {
					nave.muovi();
				}; break;
			default:
				break;
			}
		}
		window.clear(sf::Color::Black);

		gestioneEventi(nave, mappa);

		if (mappa.ricercaPianeta(nave.getPosition().x, nave.getPosition().y)) {
		
		}

		window.draw(mappa);
		window.draw(nave);
		window.display();

	}
}