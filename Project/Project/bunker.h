#ifndef BUNKER_H
#define BUNKER_H

// include header
#include "comportamento.h"

class Bunker : public Comportamento {
private: 
public: 
	Bunker(float vita, const char nomeFile[], sf::IntRect dimensione_texture, float cord_x, float cord_y, float larghezza_e, float altezza_e, float angolo_rotazione);
	Bunker();
};
#endif // !BUNKER_H
