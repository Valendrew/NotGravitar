#ifndef UNIVERSO_H
#define UNIVERSO_H

#include <stdlib.h> 
#include <iostream>
#include "pianeta.h"
#include <SFML/Graphics.hpp>

struct nodoPianeta {
	Pianeta *pianeta_;
	bool visitato;
	nodoPianeta *next;
};
typedef nodoPianeta *listaPianeti;

struct coordinate {
	int x;
	int y;
};

class Universo : public sf::Drawable, public sf::Transformable {
private:
	int width;
	int height;
	listaPianeti lista_Pianeti;
	int numeroPianeti;
	bool matriceSpawn[18][24];
	//Dimensione delle celle dove spawneranno i pianeti rispetto alla grandezza della finestra
	coordinate dimensioniCelle;
	//Booleano per verificare se è la prima volta che visito un universo o meno (in caso affermativo genero gli universi adiacenti)
	bool visitato;
	int idPianeta;
	listaPianeti generaPianeti(listaPianeti p);
	//Precondizione: la lista p passata è = NULL
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	listaPianeti pianetaAttuale;
	listaPianeti headInsert(listaPianeti L, Pianeta* p);
	
public:
	Universo(int width, int height);
	Universo();
	listaPianeti distruggiPianeta(listaPianeti p);
	listaPianeti getPianeti();
	listaPianeti getPianetaAttuale();
	coordinate getDimensioniCelle();
	void setDimensioniCelle(int x, int y);
	bool getMatriceSpawn(int i, int j);
	int getNumeroPianeti();
	void setVisitato();
	bool pianetaAttualeRicerca(int x_astronave, int y_astronave);
	bool getVisitato();
	bool distrutto();
	int controlloPassaggioSuperficie(sf::Vector2f pos);
	bool controlloCollisioneSuperficie(sf::Vector2f pos);
	proiettile_ptr getProiettili();
	void uscitaPianeta();
};
#endif // !UNIVERSO_H