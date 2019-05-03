#ifndef MAPPA_H
#define MAPPA_H

#include <stdlib.h> 
#include "universo.hpp";
#include <stdlib.h>  
struct nodoMappa {
	Universo *u;
	coordinate c;
	nodoMappa *next;
};

typedef nodoMappa *listaUniversi;

class Mappa {
private:
	listaUniversi list_universi;
	listaUniversi posizioneAttuale; //puntatore  dove si trova l'astronave
	listaUniversi universoDiGioco;  //puntatore all'universo dove attualmente si devono distruggere i pianeti
	//astrovane a;
	//findUniversi cerca un universo con coordinate x,y all'interno della lista e lo resistuisce (ritorna NULL se non lo trova)
	listaUniversi findUniverso(int x, int y);
	int distanza;
	coordinate dimensioniCelle;
public:
	Mappa(int distanza, int dim_x, int dim_y);
	//addUniveso aggiunge un universo con coordinate x,y alla lista di universi
	listaUniversi addUniverso(int x, int y);
	//spostamento gestisce lo spostamento della navicella, modificando il puntatore posizioneAttuale ed eventualmente crea nuovi universi
	//adiacenti a quello attuale
	void spostamento(int i);
	listaUniversi getPosizioneAttuale();
};

#endif