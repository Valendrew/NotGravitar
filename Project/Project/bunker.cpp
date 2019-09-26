#include "bunker.h"

Bunker::Bunker(float vita, const char nomeFile[], float cord_x, float cord_y, float larghezza_e, float altezza_e, float angolo_rotazione)
: Comportamento(vita, nomeFile, cord_x, cord_y, larghezza_e, altezza_e, angolo_rotazione) {
	entita_.setOrigin(0, 0 + altezza_e);
}

Bunker::Bunker() : Comportamento() {}
