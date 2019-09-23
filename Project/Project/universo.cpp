#include "universo.hpp";
  
listaPianeti Universo::generaPianeti(listaPianeti p) {
	int numPianeti = numeroPianeti - 1;
	p = new nodoPianeta;
	p->visitato = false;
	int spawn_x = -dimensioniCelle.x;
	int spawn_y = -dimensioniCelle.y;
	int i = 0, j = 0; 
	bool ok = true;
	while (i<18 && ok)
	{
		while (j<24 && ok)
		{
			if (matriceSpawn[i][j])
			{
				//p->pianeta_ = new Pianeta(idPianeta, spawn_x-25, spawn_y-25, width, height);//25 è il radius del pianeta
				p->pianeta_ = new Pianeta(idPianeta, spawn_x, spawn_y, width, height);//25 è il radius del pianeta
				ok = false;
				matriceSpawn[i][j] = false;
			}
			spawn_x += dimensioniCelle.x;
			j++;
		}
		spawn_x = 0;
		spawn_y += dimensioniCelle.y;
		j = 0;
		i++;
	}
	p->next = NULL;
	while (numPianeti > 0) {
		//diminuisco di 1 la i perche quando esco dal ciclo precedente viene aumentata senza effettivamente esaminare
		//la relativa riga
		i--;
		spawn_y -= dimensioniCelle.y;
		idPianeta++;
		listaPianeti tmp = new nodoPianeta;
		tmp->visitato = false;
		ok = true;
		while (i < 18 && ok)
		{
			while (j < 24 && ok)
			{
				if (matriceSpawn[i][j])
				{
					//tmp->pianeta_ = new Pianeta(idPianeta, spawn_x-25, spawn_y-25, width, height);//25 è il radius del pianeta
					tmp->pianeta_ = new Pianeta(idPianeta, spawn_x, spawn_y, width, height);//25 è il radius del pianeta
					ok = false;
					matriceSpawn[i][j] = false;
				}
				spawn_x += dimensioniCelle.x;
				j++;
			}
			spawn_x = 0;
			spawn_y += dimensioniCelle.y;
			j = 0;
			i++;
		}
		tmp->next = p;
		p = tmp;
		numPianeti--;
	}

	return p;

}

Universo::Universo(int d, int width_, int height_) {
	width = width_;
	height = height_;
	dimensioniCelle.x = width_ / 24;
	dimensioniCelle.y = height_ / 18;
	listaPianeti p = NULL;
	numeroPianeti = rand() % 3 + 3; //Pianeti da 3 a 5
	visitato = false;
	idPianeta = 0;
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

	lista_Pianeti = generaPianeti(p);
}
Universo::Universo() :Universo(0, 0, 0)
{

}
listaPianeti Universo::distruggiPianeta(listaPianeti p)
{
	return listaPianeti();
}
void Universo::setDimensioniCelle(int x, int y) {
	dimensioniCelle.x = x;
	dimensioniCelle.y = y;
}
coordinate Universo::getDimensioniCelle() {
	return dimensioniCelle;
}
listaPianeti Universo::getPianeti() {
	return lista_Pianeti;
}
bool Universo::getMatriceSpawn(int i, int j) {
	return matriceSpawn[i][j];
}
int Universo::getNumeroPianeti() {
	return numeroPianeti;
}
bool Universo::getVisitato() {
	return visitato;
}
void Universo::setVisitato() {
	visitato = true;
}

bool Universo::pianetaAttualeRicerca(int x_astronave, int y_astronave) {
	listaPianeti app = lista_Pianeti;
	pianetaAttuale = nullptr;
	bool found = false;

	while (app != nullptr && !found) {
		int x_pianeta = (*app->pianeta_).getPosizione().x;
		int y_pianeta = (*app->pianeta_).getPosizione().y;
		int radius_pianeta = (*app->pianeta_).getRaggio();

		if ((x_pianeta <= x_astronave && x_astronave <= x_pianeta + radius_pianeta) && (y_pianeta <= y_astronave && y_astronave <= y_pianeta + radius_pianeta)) {
			pianetaAttuale = app;
			found = true;
		}
		app = app->next;
	}

	return found;
}

void Universo::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	listaPianeti pianeti_print = lista_Pianeti;
	
	if (pianetaAttuale == nullptr) {
		while (pianeti_print != nullptr) {
			target.draw(*pianeti_print->pianeta_);
			pianeti_print = pianeti_print->next;
		}
	}
	else {
		(*pianetaAttuale->pianeta_).drawSuperficie(target, states);
	}
}
