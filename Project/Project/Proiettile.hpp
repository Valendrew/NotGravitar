#ifndef MAPPA_H
#define MAPPA_H

#include <SFML/Graphics.hpp>
const double PI = 3.14159265;

class Proiettile : public sf::Drawable, sf::Transformable {
private:
	float velocita;
	float x;
	float y;
public:
	Proiettile();
	Proiettile(sf::Vector2f dim, sf::Vector2f pos, float angolo, float velocita_);
	void setVelocita(float velocita_);
	float getVelocita();
	void muovi();
};

#endif