#include <SFML\Graphics.hpp>
#include "pianeta.h";
#include "universo.hpp";
#include "mappa.hpp";
const int WIDTH = 1280;
const int HEIGHT = 720;

int main() {
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Test");
	Mappa mappa_ = Mappa(2, WIDTH, HEIGHT);

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

		window.draw(mappa_);
		window.display();
		
	}
	return 0;
}