#ifndef NAVE_H
#define NAVE_H

#include "comportamento.h"
#include "proiettile.hpp"

class Nave : public Comportamento {
protected:
	//proiettiliP proiettilil;
	float carburante_;
	float carburante_movimento_;
	float velocita_attuale_movimento_;
	float velocita_movimento_;
	float velocita_rotazione_;

	void cambiaTextureMovimento(bool movimento);
public:
	Nave(unsigned int larghezza_finestra, unsigned int altezza_finestra, float vita, float danno,
		const char nomeFile[], const char nomeFileDistrutto[], sf::Vector2f posizione, sf::Vector2f dimensione, 
		float angolo_rotazione, float velocita_movimento, float velocita_rotazione, float carburante);
	Nave();

	void ruotaSinistra();
	void ruotaDestra();

	void spara();

	int getCarburante();
	void setCarburante(int carburante);
	void riempiCarburante(int carburante);

	sf::VertexArray getPosizioneFrontale();
	
	void muovi(sf::Time deltaTime, bool movimento);
	void passaggioAmbiente(sf::Vector2f posizione);
	void setDannoCollisione();

	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);
	proiettile_ptr getProiettili();
	void restart(float vita, float cord_x, float cord_y, float angolo_rotazione, float carburante, bool distrutto);
};

#endif