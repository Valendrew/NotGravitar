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
	bool distrutto_;
	int id_pianeta_;
	int numPianetiPrecedenti;

	void generaPianeti();
	void ottieniTipologiaPianeta(char tipologia[], char texture[]);
	void copiaStringa(char stringa[], int lunghezza, char stringa_da_copiare[]);

	listaPianeti pianetaAttuale;
	void headInsert(Pianeta* p);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Universo(int larghezza_finestra, int altezza_finestra);
	Universo();

	//Provare a restutire un puntatore per settare il colore quando è distrutto
	

	bool pianetaAttualeRicerca(sf::Vector2f posizione);
	bool distrutto();
	bool getDistrutto();

	bool aggiornaPunteggioBunker();
	bool distruzionePianetaAttuale();
	void cambiaColorePianeta();

	int controlloPassaggioSuperficie(sf::Vector2f pos);
	bool controlloCollisioneSuperficie(sf::Vector2f pos);
	proiettile_ptr getProiettili();

	void controlloRaggio(sf::ConvexShape raggio);

	void uscitaPianeta();
	int controlloProiettili(proiettile_ptr lista_proiettili);
	int pianetiRimanenti();
};
#endif // !UNIVERSO_H