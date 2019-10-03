#ifndef NAVE_H
#define NAVE_H

#include "comportamento.h"
#include "proiettile.hpp"

class Nave : public Comportamento {
private:
	//proiettiliP proiettilil;
	int carburante_;
	float velocita_;
	float angolodirotazione_;
public:
	Nave(float vita, const char nomeFile[], sf::IntRect dimensione_texture, float cord_x, float cord_y, float larghezza_e, float altezza_e, float angolo_rotazione, float velocita, int carburante);
	Nave();
	void ruotaL();
	void ruotaR();
	void spara();
	void setCarburante(int carburante_);
	int getCarburante();
	void colpito();
	void fill(int carburante_);
	void muovi(sf::Time deltaTime);
	sf::Vector2f getPosizione();
	void setPosizione(sf::Vector2f pos);
};

#endif