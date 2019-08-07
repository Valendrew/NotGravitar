#ifndef UNIVERSO_H
#define UNIVERSO_H

struct nodoPianeta {
	bool visitato;
	nodoPianeta *next;
};

typedef nodoPianeta *listaPianeti;

struct coordinate {
	int x;
	int y;
};

class Universo {
private:
	listaPianeti lista_Pianeti;
	int numeroPianeti;
	bool matriceSpawn[18][24];
	//Dimensione delle celle dove spawneranno i pianeti rispetto alla grandezza della finestra
	coordinate dimensioniCelle;
	//Booleano per verificare se è la prima volta che visito un universo o meno (in caso affermativo genero gli universi adiacenti)
	bool visitato;

	listaPianeti generaPianeti(listaPianeti p);
	//Precondizione: la lista p passata è = NULL

public:
	Universo(int distanza, int x, int y);

	Universo();
	listaPianeti distruggiPianeta(listaPianeti p);
	listaPianeti getPianeti();
	coordinate getDimensioniCelle();
	void setDimensioniCelle(int x, int y);
	bool getMatriceSpawn(int i, int j);
	int getNumeroPianeti();
	void setVisitato();
	bool getVisitato();
};
#endif // !UNIVERSO_H