#ifndef _COMPORTAMENTO_H
#define _COMPORTAMENTO_H

#include "proiettile.hpp"
#include <SFML/Graphics.hpp>

class Comportamento : public sf::Drawable, public sf::Transformable {
protected:
	float vita_;

	sf::RectangleShape entita_;
	sf::Texture texture_;

	struct ProiettileNode { // lista di proiettili
		Proiettile *proiettile;
		ProiettileNode *next;
	};
	typedef ProiettileNode *proiettile_ptr;
	proiettile_ptr proiettili_;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Comportamento(float vita, const char nomeFile[], float cord_x, float cord_y, float larghezza_e, float altezza_e, float angolo_rotazione);
	Comportamento();
	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosizione();
	void getRotazione(float rot);
	float getRotazione();
	void spara(float angolo);
	void eliminaProiettile(proiettile_ptr p);

};
#endif // !_COMPORTAMENTO_H
