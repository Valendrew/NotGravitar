#include "universo.hpp";
#include <stdlib.h>     
#include <iostream>     
#include <time.h> 
#include <iostream>
listaPianeti universo::generaPianeti(listaPianeti p) {
	int numPianeti = numeroPianeti - 1;
	p = new nodoPianeta;
	p->visitato = false;
	p->next = NULL;
	while (numPianeti > 0) {
		listaPianeti tmp = new nodoPianeta;
		tmp->visitato = false;
		tmp->next = p;
		p = tmp;
		numPianeti--;
	}

	return p;

}

universo::universo(int d, int x, int y) {
	dimensioniCelle.x = x;
	dimensioniCelle.y = y;
	listaPianeti p = NULL;
	numeroPianeti = rand() % 3 + 3; //Pianeti da 3 a 5
	visitato = false;
	lista_Pianeti = generaPianeti(p);

	//setto tutta la matrice di spawn a false (i pianeti saranno generati dove avro true)
	for (int i = 0; i < 24; i++)
		for (int j = 0; j < 18; j++)
			matriceSpawn[j][i] = false;

	int col = 0;
	int row = 0;
	int i = 0;
	int j = 0;
	int numPianeti = numeroPianeti;
	//ciclo tante volte quanti sono i pianeti
	while (numPianeti > 0) {

		//col e row assumono un valore che dipende dalla distanza (d) che si vuole avere tra i vari pianeti escludendo inoltre
		//la cornice e le celle sottostanti la cornice cosi da evitare che i pianeti sforino dallo schermo o che vengano 
		//attaccati al bordo (sarebbe brutto)
		col = rand() % (24 - 2 * d + 2) + (d - 1);
		row = rand() % (18 - 2 * d + 2) + (d - 1);
		i = d;
		bool ok = true;
		//i due while scorrono una matrice di dimensione [d*2 +1] [d*2 +1] con "al centro" il valore di matriceSpawn[row][col]
		//cosi da verificare che ne la posizione generata ne le posizioni attorno siano gia occupate da un true
		//questo serve per non far venire i pianeti attaccati e in generale per rispettare la distanza scelta
		while (i >= -d && ok)
		{
			j = d;
			while (j >= -d && ok)
			{
				if (matriceSpawn[row - i][col - j])
					ok = false;
				j--;
			}
			i--;
		}
		//se la variabile ok è ancora a true significa che true puo essere assegnato alla posizione matriceSpawn[row][col]
		//rispettando comunque il vincolo della distanza
		if (ok) {
			matriceSpawn[row][col] = true;
			numPianeti--;
		}
	}
}
universo::universo() :universo(0, 0, 0)
{

}
void universo::setDimensioniCelle(int x, int y) {
	dimensioniCelle.x = x;
	dimensioniCelle.y = y;
}
coordinate universo::getDimensioniCelle() {
	return dimensioniCelle;
}
listaPianeti universo::getPianeti() {
	return lista_Pianeti;
}
bool universo::getMatriceSpawn(int i, int j) {
	return matriceSpawn[i][j];
}
int universo::getNumeroPianeti() {
	return numeroPianeti;
}
bool universo::getVisitato() {
	return visitato;
}
void universo::setVisitato() {
	visitato = true;
}
