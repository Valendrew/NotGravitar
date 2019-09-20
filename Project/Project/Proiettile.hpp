#ifndef MAPPA_H
#define MAPPA_H

#include <SFML/Graphics.hpp>
const double PI_G = 3.1416;

class Proiettile : public sf::Drawable, public sf::Transformable {
private:
	sf::RectangleShape proiettile_;
	float velocita_;
	float x;
	float y;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	sf::RectangleShape getProiettile();
	Proiettile();
	Proiettile(sf::Vector2f dim, sf::Vector2f pos, float angolo, float velocita_);
	void setVelocita(float velocita_);
	float getVelocita();
	void muovi();
};

#endif