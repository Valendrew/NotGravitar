#include <SFML\Graphics.hpp>
#include "pianeta.h";

const int WIDTH = 1280;
const int HEIGHT = 720;

int main() {
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Test");
	Pianeta p = Pianeta(0, 200, 200, WIDTH, HEIGHT);

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

		window.clear(sf::Color::Black);
		window.draw(p.getSuperficie());
		window.display();
		
	}
	return 0;
}