#ifndef _COMPORTAMENTO_H
#define _COMPORTAMENTO_H

#include "proiettile.hpp"
#include <SFML/Graphics.hpp>

struct ProiettileNode { // lista di proiettili
	Proiettile *proiettile;
	ProiettileNode *next;
};
typedef ProiettileNode *proiettile_ptr;

class Comportamento : public sf::Drawable, public sf::Transformable {
protected:
	sf::Clock clock_;
	float vita_;
	unsigned int larghezza_finestra;
	unsigned int altezza_finestra;

	sf::RectangleShape entita_;
	sf::Texture texture_;

	proiettile_ptr proiettili_;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Comportamento(unsigned int width, unsigned int height, float vita, const char nomeFile[], sf::Vector2f pos, sf::Vector2f size, float angolo_rotazione);
	Comportamento();
	sf::Vector2f getPosizione();
	void setPosizione(sf::Vector2f pos);
	sf::Vector2f getDimensione();
	float getRotation();
	void setRotation(float rot);
	sf::FloatRect getBordi();
	void spara(float angolo);
	void controlloProiettili(proiettile_ptr lista_proiettili);
	void eliminaProiettile(proiettile_ptr p);

};
#endif // !_COMPORTAMENTO_H
