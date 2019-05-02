#ifndef BUNKER_H
#define BUNKER_H

// include header
#include <SFML\Graphics.hpp>

class Bunker : public sf::Drawable, public sf::Transformable {
private: float vita_;
		 sf::RectangleShape shape_;
		 sf::Texture texture_;
		 virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public: Bunker(float cord_x, float cord_y, float size, float angolo_rotazione, sf::Texture texture);
		Bunker();
};
#endif // !BUNKER_H
