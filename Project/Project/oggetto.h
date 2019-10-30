#ifndef _OGGETTO_H
#define _OGGETTO_H

#include <SFML/Graphics.hpp>

enum Tipologia {
	BENZINA = 3,
	BENZINA_BEST = 6,
	CUORE = 60,
	DEFAULT = 0
};

class Oggetto : public sf::Drawable, public sf::Transformable {
private:
	
	
	float capacita_;

	Tipologia tipo_;
	sf::RectangleShape entita_;
	sf::Texture texture_;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Oggetto();
	Oggetto(Tipologia tipo, const char nomefile[], sf::Vector2f pos, float angolo_rotazione, sf::Vector2f size);
	Tipologia getTipologia();
	sf::Vector2f getPosition();
};

#endif