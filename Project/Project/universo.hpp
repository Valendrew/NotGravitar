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
	Pianeta* pianeta_;
	nodoPianeta* next;
};
typedef nodoPianeta* listaPianeti;

class Universo : public sf::Drawable, public sf::Transformable {
protected:
	int larghezza_finestra_;
	int altezza_finestra_;

	listaPianeti lista_Pianeti;
	int numero_pianeti_;

	bool matrice_spawn_[18][24];

	//Dimensione delle celle dove spawneranno i pianeti rispetto alla grandezza della finestra
	coordinate dimensioni_celle_;

	bool visitato_;
	bool* distrutto_;
	int id_pianeta_;

	void generaPianeti();
	listaPianeti pianetaAttuale;
	void headInsert(Pianeta* p);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Universo(int larghezza_finestra, int altezza_finestra);
	Universo();

	Pianeta getPianetaAttuale();

	bool pianetaAttualeRicerca(sf::Vector2f posizione);
	bool distrutto();
	bool getDistrutto();
	bool restaUnSoloPianeta();


	int controlloPassaggioSuperficie(sf::Vector2f pos);
	bool controlloCollisioneSuperficie(sf::Vector2f pos);
	proiettile_ptr getProiettili();

	void uscitaPianeta();
	void controlloProiettili(proiettile_ptr lista_proiettili);
};
#endif // !UNIVERSO_H