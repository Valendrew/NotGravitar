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

	float danno_;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Proiettile(sf::Vector2f dimensione, sf::Vector2f posizione, float angolo, float velocita, float danno, sf::Color colore);
	Proiettile();
	void setDistrutto();
	float getDanno();
	sf::Vector2f getPosition();
	sf::RectangleShape getProiettile();
	sf::FloatRect getGlobalBounds();
	void muovi();
};

#endif