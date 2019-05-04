#include "bunker.h"

Bunker::Bunker(float vita, const char nomeFile[], sf::IntRect dimensione_texture, float cord_x, float cord_y, float larghezza_e, float altezza_e, float angolo_rotazione)
: Comportamento(vita, nomeFile, dimensione_texture, cord_x, cord_y, larghezza_e, altezza_e, angolo_rotazione) {
	entita_.setOrigin(0, 0 + altezza_e);
}

Bunker::Bunker() : Comportamento() {}
