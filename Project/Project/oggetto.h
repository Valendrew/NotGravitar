#ifndef _OGGETTO_H
#define _OGGETTO_H

#include <SFML/Graphics.hpp>

class oggetto : public sf::Drawable, public sf::Transformable {
private:
	enum tipologia {
		BENZINA = 35,
		BENZINA_BEST = 60,
		CUORE = 100
	};

	float capacita_;
	char nomeFile_[50];
	tipologia tipo_;
	sf::RectangleShape entita_;
	sf::Texture texture_;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	oggetto();
	oggetto(const char tipo[], const char nomefile[], sf::Vector2f pos, float angolo_rotazione, sf::Vector2f size);
	tipologia getTipologia();
	float getCapacita();
};

#endif