#ifndef _BUNKER_STRONGER_H
#define _BUNKER_STRONGER_H

#include "bunker.h"
#include <SFML/Graphics.hpp>


class BunkerStronger : public Bunker{
protected:
public:
	void spara();
	BunkerStronger(unsigned int larghezza_finestra, unsigned int altezza_finestra, float vita, float danno, 
		const char nomeFile[], const char nomeFileDistrutto[], sf::Vector2f posizione, sf::Vector2f dimensione, float angolo_rotazione);
	BunkerStronger();
};
#endif // !_BUNKER_STRONGER_H

