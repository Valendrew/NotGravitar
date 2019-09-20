#include <SFML\Graphics.hpp>
#include "nave.hpp"
#include "pianeta.h"

const int WIDTH = 1280;
const int HEIGHT = 720;

int main() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Test", sf::Style::Default, settings);
	//sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Test");

	Pianeta p = Pianeta(0, 200, 200, WIDTH, HEIGHT);
	Nave n = Nave(50, "Texture/ship3.png", sf::IntRect(), 300, 200, 32, 37, 0, 2, 50);

	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type)
			{
			case sf::Event::Closed: window.close();
				break;
			default:
				break;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) n.muovi();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) n.ruota(-1.f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) n.ruota(1.0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) n.spara(5.f);
		window.clear(sf::Color::Black);
		window.draw(p.getSuperficie());
		window.draw(n);
		window.display();
		
	}
	return 0;
}