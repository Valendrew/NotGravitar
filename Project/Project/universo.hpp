#ifndef UNIVERSO_H
#define UNIVERSO_H

#include <stdlib.h>
#include "pianeta.h"

#include <SFML/Graphics.hpp>

struct coordinate {
	int x;
	int y;
};

struct nodoPianeta {
	Pianeta *pianeta_;
	bool visitato;
	nodoPianeta *next;
};
typedef nodoPianeta *listaPianeti;

class Universo : public sf::Drawable, public sf::Transformable {
protected:
	int larghezza_finestra_;
	int altezza_finestra_;

	listaPianeti lista_Pianeti;
	int numero_pianeti_;

	bool matrice_spawn_[18][24];

	//Dimensione delle celle dove spawneranno i pianeti rispetto alla grandezza della finestra
	coordinate dimensioni_celle_;
	//Booleano per verificare se è la prima volta che visito un universo o meno (in caso affermativo genero gli universi adiacenti)
	bool visitato_;
	int id_pianeta_;

	listaPianeti generaPianeti(listaPianeti p);
	//Precondizione: la lista p passata è = NULL
	listaPianeti pianetaAttuale;
	listaPianeti headInsert(listaPianeti L, Pianeta* p);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Universo(int larghezza_finestra, int altezza_finestra);
	Universo();

	listaPianeti distruggiPianeta(listaPianeti p);
	listaPianeti getPianeti();
	listaPianeti getPianetaAttuale();

	coordinate getDimensioniCelle();
	void setDimensioniCelle(int x, int y);

	bool getMatriceSpawn(int i, int j);
	int getNumeroPianeti();

	bool getVisitato();
	void setVisitato();

	bool pianetaAttualeRicerca(int x_astronave, int y_astronave);
	bool distrutto();

	int controlloPassaggioSuperficie(sf::Vector2f pos);
	bool controlloCollisioneSuperficie(sf::Vector2f pos);
	proiettile_ptr getProiettili();

	void uscitaPianeta();
	void controlloProiettili(proiettile_ptr lista_proiettili);
};
#endif // !UNIVERSO_H