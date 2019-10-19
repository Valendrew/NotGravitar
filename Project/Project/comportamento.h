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
	unsigned int larghezza_finestra_;
	unsigned int altezza_finestra_;

	float vita_;
	float danno_;
	bool distrutto_;

	char nomeFile_[50];
	char nomeFileDistrutto_[50];

	sf::RectangleShape entita_;
	sf::Texture texture_;
	sf::Texture texture_distrutto_;

	sf::Clock clock_;
	proiettile_ptr proiettili_;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Comportamento(unsigned int larghezza_finestra, unsigned int altezza_finestra, float vita, float danno, 
		const char nomeFile[], const char nomeFileDistrutto[], sf::Vector2f posizione, sf::Vector2f dimensione, float angolo_rotazione);
	Comportamento();

	void restart(float vita, float cord_x, float cord_y, float angolo_rotazione, bool distrutto);

	sf::Vector2f getPosizione();
	void setPosizione(sf::Vector2f pos);
	sf::FloatRect getGlobalBounds();
	sf::Vector2f getDimensione();

	float getRotation();
	void setRotation(float rotazione);

	void controlloProiettili(proiettile_ptr lista_proiettili);
	proiettile_ptr eliminaProiettile(proiettile_ptr p);
	void eliminaProiettiliBordo();
	void resetProiettili();

	float getVita();
	bool getDistrutto();
	void setDistrutto();
	void diminuisciVita(float danno);
	void drawComportamento(sf::RenderTarget& target, sf::RenderStates states);
};
#endif // !_COMPORTAMENTO_H
