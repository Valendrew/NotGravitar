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
	Nave(unsigned int larghezza_finestra, unsigned int altezza_finestra, float vita, float danno,
		const char nomeFile[], const char nomeFileDistrutto[], sf::Vector2f posizione, sf::Vector2f dimensione, 
		float angolo_rotazione, float velocita_movimento, float velocita_rotazione, int carburante);
	Nave();

	void ruotaSinistra();
	void ruotaDestra();

	void spara();

	int getCarburante();
	void setCarburante(int carburante);
	void riempiCarburante(int carburante);

	sf::VertexArray getPosizioneFrontale();

	void colpito();
	
	void muovi(sf::Time deltaTime);

	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);

	proiettile_ptr getProiettili();

	void restart(float vita, float cord_x, float cord_y, float angolo_rotazione, int carburante);
};

#endif