#ifndef NAVE_H
#define NAVE_H

#include "comportamento.h"
#include "proiettile.hpp"

class Nave : public Comportamento {
private:
	//proiettiliP proiettilil;
	int carburante_;
	float velocita_movimento_;
	float velocita_rotazione_;
public:
	Nave(float vita, const char nomeFile[], float cord_x, float cord_y, float larghezza_e, float altezza_e, float angolo_rotazione, float velocita_movimento, float velocita_rotazione, int carburante);
	Nave();
	void ruotaL();
	void ruotaR();
	void setCarburante(int carburante_);
	int getCarburante();
	sf::VertexArray getPosizioneFrontale();
	void colpito();
	void fill(int carburante_);
	void muovi();
};

#endif