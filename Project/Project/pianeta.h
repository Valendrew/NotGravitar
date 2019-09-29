#ifndef PIANETA_H
#define PIANETA_H

// includes
#include "bunker.h"
#include "superficie_pianeta.h"

class Pianeta : public sf::Drawable, public sf::Transformable {
private: 
	int id_;
	sf::CircleShape shape_;
	SuperficiePianeta superficie_;
	bool distrutto_;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public: 
	Pianeta(int id, float cord_x, float cord_y, unsigned int width, unsigned int height);
	int getRaggio();
	sf::Vector2f getPosizione();
	void cambiaColore();
	void drawSuperficie(sf::RenderTarget& target, sf::RenderStates states);
};
#endif // !PIANETA_H
