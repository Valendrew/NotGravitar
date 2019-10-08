#ifndef NAVE_H
#define NAVE_H

#include "comportamento.h"
#include "proiettile.hpp"

class Nave : public Comportamento {
protected:
	//proiettiliP proiettilil;
	int carburante_;
	float velocita_movimento_;
	float velocita_rotazione_;
public:
	Nave(unsigned int width, unsigned int height, float vita, const char nomeFile[], sf::Vector2f pos, sf::Vector2f size, float angolo_rotazione, float velocita_movimento, float velocita_rotazione, int carburante);
	Nave();
	void ruotaL();
	void ruotaR();
	void spara();
	void setCarburante(int carburante_);
	int getCarburante();
	sf::VertexArray getPosizioneFrontale();
	void colpito();
	void fill(int carburante_);
	void muovi(sf::Time deltaTime);
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);
	proiettile_ptr getProiettili();
	void restart(float vita, float cord_x, float cord_y, float angolo_rotazione, int carburante);
};

#endif