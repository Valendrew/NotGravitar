#ifndef _COMPORTAMENTO_H
#define _COMPORTAMENTO_H

#include "SFML\Graphics.hpp"

class Comportamento : public sf::Drawable, public sf::Transformable {
protected:
	float vita_;
	
	sf::RectangleShape entita_;
	sf::Texture texture_;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public: 
	Comportamento(float vita, const char nomeFile[], sf::IntRect dimensione_texture, float cord_x, float cord_y, float larghezza_e, float altezza_e, float angolo_rotazione);
	Comportamento();

};
#endif // !_COMPORTAMENTO_H
