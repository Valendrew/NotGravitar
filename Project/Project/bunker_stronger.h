#ifndef _BUNKER_STRONGER_H
#define _BUNKER_STRONGER_H

#include "bunker.h"
#include <SFML/Graphics.hpp>


class BunkerStronger : public Bunker{
protected:
public:
	void spara();
	BunkerStronger(unsigned int width, unsigned int height, float vita, const char nomeFile[], const char nomeFileDistrutto[50], sf::Vector2f pos, sf::Vector2f size, float angolo_rotazione);
	BunkerStronger();
};
#endif // !_BUNKER_STRONGER_H

