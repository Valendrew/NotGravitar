#ifndef PIANETA_H
#define PIANETA_H

// include
#include "bunker.h"
#include "superficie_pianeta.h"

class Pianeta : public sf::Drawable, public sf::Transformable {
private: 
	int id_;
	sf::CircleShape shape_;
	SuperficiePianeta superficie_;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public: 
	Pianeta(int id, float cord_x, float cord_y, unsigned int width, unsigned int height);
	int getRadius();
	SuperficiePianeta getSuperficie();
	void cambiaColore();
};
#endif // !PIANETA_H
