#ifndef PROIETTILE_H
#define PROIETTILE_H

#include <SFML/Graphics.hpp>

const double PI_G = 3.1416;

class Proiettile : public sf::Drawable, public sf::Transformable {
private:
	sf::RectangleShape proiettile_;

	float velocita_;
	float x_;
	float y_;

	int danno_;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Proiettile(sf::Vector2f dimensione, sf::Vector2f posizione, float angolo, float velocita, float danno);
	Proiettile();

	sf::RectangleShape getProiettile();

	float getVelocita();
	void setVelocita(float velocita_);
	
	sf::FloatRect getGlobalBounds();

	sf::Vector2f getPosition();

	void setColor(sf::Color color);

	void muovi();
};

#endif