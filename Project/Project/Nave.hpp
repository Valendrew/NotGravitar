#ifndef NAVE_H
#define NAVE_H

#include "comportamento.h"
#include "proiettile.hpp"

struct proiettili {
	Proiettile *val;
	proiettili *next;
};
typedef proiettili *proiettiliP;

class Nave : public Comportamento {
private:
	proiettiliP proiettilil;
	int carburante_;
	float velocita_;

public:
	Nave(float vita, const char nomeFile[], sf::IntRect dimensione_texture, float cord_x, float cord_y, float larghezza_e, float altezza_e, float angolo_rotazione, float velocita, int carburante);
	Nave();
	void rotate(float r);
	void setCarburante(int carburante_);
	int getCarburante();
	void colpito();
	void fill(int carburante_);
	void muovi();
};

#endif