#include <SFML\Graphics.hpp>
#include "pianeta.h";

const int WIDTH = 1280;
const int HEIGHT = 720;

int main() {
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Test");
	
	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
		}

		window.clear(sf::Color::Black);
		window.display();
		
	}
	return 0;
}