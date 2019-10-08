#ifndef BUNKER_H
#define BUNKER_H

// include header
#include "comportamento.h"
#include <SFML/Graphics.hpp>

class Bunker : public Comportamento {
protected:
	char nomeFileDistrutto_[50];
	float angolo_sparo;
	bool distrutto = false;
public: 
	void spara();
	void setDistrutto();
	proiettile_ptr getProiettili();
	Bunker(unsigned int width, unsigned int height, float vita, const char nomeFile[], const char nomeFileDistrutto[], sf::Vector2f pos, sf::Vector2f size, float angolo_rotazione);
	Bunker();
};
#endif // !BUNKER_H
