#ifndef BUNKER_H
#define BUNKER_H

// include header
#include "Proiettile.h"
#include <SFML\Graphics.hpp>

class Bunker : public sf::Drawable, public sf::Transformable {
private: float vita_;
		 Proiettile proiettile_;
		 sf::RectangleShape shape_;
		 virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public: Bunker(float cord_x, float cord_y, float size, float angolo_rotazione);
		Bunker();
};
#endif // !BUNKER_H
