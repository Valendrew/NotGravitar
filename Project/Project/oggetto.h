#ifndef _OGGETTO_H
#define _OGGETTO_H

#include <SFML/Graphics.hpp>



class Oggetto : public sf::Drawable, public sf::Transformable {
private:
	
	enum tipologia {
		BENZINA = 4,
		BENZINA_BEST = 8,
		CUORE = 100
	};
	float capacita_;
	char nomeFile_[50];

	tipologia tipo_;
	sf::RectangleShape entita_;
	sf::Texture texture_;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void copiaStringa(char stringa[], int lunghezza, char stringa_da_copiare[]);
public:
	Oggetto();
	Oggetto(const char tipo[], const char nomefile[], sf::Vector2f pos, float angolo_rotazione, sf::Vector2f size);
	void getTipologia(char tipologia []);
	float getCapacita();
	sf::Vector2f getPosition();
};

#endif