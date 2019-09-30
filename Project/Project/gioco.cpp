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
	sf::Clock clock;
	sf::Time tempoUpdate = sf::Time::Zero;

	while (window.isOpen()) {
		tempoUpdate = clock.restart();

		sf::Event event;
 		while (window.pollEvent(event)) {
   			switch (event.type)
			{
			case sf::Event::Closed: window.close();
				break;
			case sf::Event::KeyPressed:
			{
				if (event.key.code == sf::Keyboard::Space) {
					nave.muovi(tempoUpdate);
				}
				if (event.key.code == sf::Keyboard::A) {
					nave.ruotaL();
				}
				if (event.key.code == sf::Keyboard::D) {
					nave.ruotaR();
				}
				if (event.key.code == sf::Keyboard::F) {
					nave.spara();
				}
			}; break;
			default:
				break;
			}
 		}
		window.clear(sf::Color::Black);

		gestioneEventi(nave, mappa);

		if (mappa.ricercaPianeta(nave.getPosizione().x, nave.getPosizione().y)) {
			std::cout << nave.getPosizione().y << "\n";
		}
		
		window.draw(mappa);
		window.draw(nave);
		window.display();

	}
}
