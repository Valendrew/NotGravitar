#pragma once
#include <SFML/Graphics.hpp>
#include "proiettile.hpp"
using namespace std;

struct proiettili {
	Proiettile *val;
	proiettili *next;
};
typedef proiettili *proiettiliP;

class Nave : public sf::Sprite {
private:
	proiettiliP proiettilil;
	int vita;
	int carburante;
	float velocita;

public:
	Nave(float x, float y, float r, float velocita_, int carburante_ = 10, int vita_ = 10);
	Nave();
	void setVita(int vita_);
	int getVita();
	void setCarburante(int carburante_);
	int getCarburante();
	void colpito();
	void fill(int carburante_);
	void muovi();
	void spara(sf::Vector2f dimensioni, int velocita);
	void updateProiettili(sf::RenderWindow &window);
	bool collisioneProiettile(Proiettile proiettile);
	void eliminaListaProiettili(proiettiliP head);
};