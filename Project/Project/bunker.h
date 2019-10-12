#ifndef BUNKER_H
#define BUNKER_H

// include header
#include "comportamento.h"
#include <SFML/Graphics.hpp>

class Bunker : public Comportamento {
protected:
	float angolo_sparo_;
	bool distrutto_;
public: 
	Bunker(unsigned int larghezza_finestra, unsigned int altezza_finestra, float vita, float danno, 
		const char nomeFile[], const char nomeFileDistrutto[], sf::Vector2f posizione, sf::Vector2f dimensione, float angolo_rotazione);
	Bunker();

	void spara();

	void setDistrutto();

	proiettile_ptr getProiettili();
};
#endif // !BUNKER_H
