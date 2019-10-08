#ifndef MAPPA_H
#define MAPPA_H

#include "universo.hpp";
struct nodoMappa {
	Universo *u;
	coordinate c;
	nodoMappa *next;
};

typedef nodoMappa *listaUniversi;

class Mappa : public sf::Drawable, public sf::Transformable  {
protected:

	sf::RectangleShape entita_;
	sf::Texture texture_;
	int width;
	int height;
	int distanza;
	listaUniversi list_universi;
	listaUniversi posizioneAttuale; //puntatore  dove si trova l'astronave
	listaUniversi universoDiGioco;  //puntatore all'universo dove attualmente si devono distruggere i pianeti
	listaUniversi addUniverso(int x, int y); //addUniveso aggiunge un universo con coordinate x,y alla lista di universi
	bool statoAttacco;
	//findUniversi cerca un universo con coordinate x,y all'interno della lista e lo resistuisce (ritorna NULL se non lo trova)
	listaUniversi findUniverso(int x, int y);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Mappa();
	Mappa(int dim_x, int dim_y);
	int controlloPassaggioSuperficie(sf::Vector2f pos);
	bool controlloCollisioneSuperficie(sf::Vector2f pos);
	void uscitaPianeta();
	/*spostamento gestisce lo spostamento della navicella, modificando il puntatore posizioneAttuale ed eventualmente crea nuovi universi
	adiacenti a quello attuale */
	bool spostamento(int i);
	bool ricercaPianeta(int x_astronave, int y_astronave);
	proiettile_ptr getProiettili();
	void controlloProiettili(proiettile_ptr lista_proiettili);
	Universo getUniversoDiGioco();
	coordinate getPosizioneAttuale();
	coordinate getPosizioneDiGioco();
};

#endif