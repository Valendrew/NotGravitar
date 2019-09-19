#include <SFML\Graphics.hpp>
#include "nave.hpp"
#include "pianeta.h"
#include "mappa.hpp"

const int WIDTH = 1280;
const int HEIGHT = 720;

int main() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Test", sf::Style::Default, settings);
	//sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Test");

	Pianeta p = Pianeta(0, 200, 200, WIDTH, HEIGHT);
	Nave n = Nave(50, "Texture/ship3.png", sf::IntRect(), 300, 200, 32, 37, 0, 20, 50);
	Mappa m = Mappa(WIDTH, HEIGHT);

	bool change = false;
	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type)
			{
			case sf::Event::Closed: window.close();
				break;
			case sf::Event::KeyPressed:
				if (sf::Keyboard::Space) {
					change = !change;
				}
			default:
				break;
			}
		}

		window.clear(sf::Color::Black);

		if (change) window.draw(p.getSuperficie());
		else window.draw(m);
		//window.draw(n);
		window.display();
		
	}
	return 0;
}