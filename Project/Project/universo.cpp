#include "universo.hpp";

listaPianeti Universo::generaPianeti(listaPianeti p) {
	int spawn_x = dimensioni_celle_.x;
	int spawn_y = dimensioni_celle_.y;
	int i = 1, j = 1;
	while (i < 17)
	{
		while (j < 23)
		{
			if (matrice_spawn_[i][j])
			{
				Pianeta* pi = new Pianeta(id_pianeta_, sf::Vector2f(spawn_x, spawn_y), larghezza_finestra_, altezza_finestra_);//25 è il radius del pianeta
				id_pianeta_++;

				if (p == nullptr) {
					p = new nodoPianeta;
					p->visitato = false;
					p->pianeta_ = pi;
					p->next = nullptr;
				}
				else {
					listaPianeti tmp = new nodoPianeta;
					tmp->visitato = false;
					tmp->pianeta_ = pi;
					tmp->next = p;
					p = tmp;
				}
				//p = headInsert(p, pi);
			}
			spawn_x += dimensioni_celle_.x;
			j++;
		}
		spawn_x = 0;
		spawn_y += dimensioni_celle_.y;
		j = 0;
		i++;
	}
	return p;
}

listaPianeti Universo::headInsert(listaPianeti L, Pianeta* p) {
	if (L == nullptr) {
		L = new nodoPianeta;
		L->visitato = false;
		L->pianeta_ = p;
		L->next = nullptr;
	}
	else {
		listaPianeti tmp = new nodoPianeta;
		tmp->visitato = false;
		tmp->pianeta_ = p;
		tmp->next = L;
		L = tmp;
	}
	return L;
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

Universo::Universo(int larghezza_finestra, int altezza_finestra) {
	larghezza_finestra_ = larghezza_finestra;
	altezza_finestra_ = altezza_finestra;
	dimensioni_celle_.x = larghezza_finestra / 24;
	dimensioni_celle_.y = altezza_finestra / 18;
	listaPianeti p = nullptr;
	numero_pianeti_ = rand() % 2 + 4; //Pianeti da 4 a 5
	visitato_ = false;
	id_pianeta_ = 0;
	//setto tutta la matrice di spawn a false (i pianeti saranno generati dove avro true)
	for (int i = 0; i < 24; i++)
		for (int j = 0; j < 18; j++)
			matrice_spawn_[j][i] = false;

	int col = 0;
	int row = 0;
	int i = 0;
	int j = 0;
	int numPianeti = numero_pianeti_;
	//ciclo tante volte quanti sono i pianeti
	while (numPianeti > 0) {

		//col e row assumono un valore che dipende dalla distanza (d=2) che si vuole avere tra i vari pianeti escludendo inoltre
		//la cornice e le celle sottostanti la cornice cosi da evitare che i pianeti sforino dallo schermo o che vengano 
		//attaccati al bordo (sarebbe brutto)
		/*col = rand() % (24 - 2 * d + 2) + (d - 1);
		row = rand() % (18 - 2 * d + 2) + (d - 1);*/
		col = rand() % (22) + (1);
		row = rand() % (16) + (1);
		i = 2;
		bool ok = true;
		//i due while scorrono una matrice di dimensione [d*2 +1] [d*2 +1] con "al centro" il valore di matriceSpawn[row][col]
		//cosi da verificare che ne la posizione generata ne le posizioni attorno siano gia occupate da un true
		//questo serve per non far venire i pianeti attaccati
		while (i >= -2 && ok)
		{
			j = 2;
			while (j >= -2 && ok)
			{
				if (matrice_spawn_[row - i][col - j])
					ok = false;
				j--;
			}
			i--;
		}
		//se la variabile ok è ancora a true significa che true puo essere assegnato alla posizione matriceSpawn[row][col]
		//rispettando comunque il vincolo della distanza
		if (ok) {
			matrice_spawn_[row][col] = true;
			numPianeti--;
		}
	}

	lista_Pianeti = generaPianeti(p);
}

Universo::Universo() :Universo(1280, 720) {}

listaPianeti Universo::distruggiPianeta(listaPianeti p)
{
	return listaPianeti();
}

listaPianeti Universo::getPianeti() {
	return lista_Pianeti;
}

listaPianeti Universo::getPianetaAttuale() {
	return pianetaAttuale;
}

coordinate Universo::getDimensioniCelle() {
	return dimensioni_celle_;
}

void Universo::setDimensioniCelle(int x, int y) {
	dimensioni_celle_.x = x;
	dimensioni_celle_.y = y;
}

bool Universo::getMatriceSpawn(int i, int j) {
	return matrice_spawn_[i][j];
}

int Universo::getNumeroPianeti() {
	return numero_pianeti_;
}

bool Universo::getVisitato() {
	return visitato_;
}

void Universo::setVisitato() {
	visitato_ = true;
}

bool Universo::pianetaAttualeRicerca(int x_astronave, int y_astronave) {
	listaPianeti lista_pianeti_tmp = lista_Pianeti;
	pianetaAttuale = nullptr;
	bool found = false;

	while (lista_pianeti_tmp != nullptr && !found) {
		int x_pianeta = (*lista_pianeti_tmp->pianeta_).getPosizione().x;
		int y_pianeta = (*lista_pianeti_tmp->pianeta_).getPosizione().y;
		int radius_pianeta = (*lista_pianeti_tmp->pianeta_).getRaggio();


		if ((x_pianeta <= x_astronave && x_astronave <= x_pianeta + radius_pianeta * 2) && (y_pianeta <= y_astronave && y_astronave <= y_pianeta + radius_pianeta * 2)) {
			pianetaAttuale = lista_pianeti_tmp;
			found = true;
		}
		lista_pianeti_tmp = lista_pianeti_tmp->next;
	}
	return found;
}

bool Universo::distrutto() {
	bool ritorno = true;
	listaPianeti lista_pianeti_tmp = lista_Pianeti;

	while (lista_pianeti_tmp != nullptr && ritorno)
		if (!((*lista_pianeti_tmp->pianeta_).isDistrutto())) ritorno = false;

	return ritorno;
}

int Universo::controlloPassaggioSuperficie(sf::Vector2f pos)
{
	int direzione = -1;
	if (pianetaAttuale != nullptr) {
		direzione = (*pianetaAttuale->pianeta_).controlloPassaggioSuperficie(pos);
	}
	return direzione;
}

bool Universo::controlloCollisioneSuperficie(sf::Vector2f pos) {
	bool ritorno = false;
	if (pianetaAttuale != nullptr) {
		ritorno = (*pianetaAttuale->pianeta_).controlloCollisioneSuperficie(pos);
	}
	return ritorno;
}

proiettile_ptr Universo::getProiettili()
{
	if (pianetaAttuale != nullptr) {
		return (*pianetaAttuale->pianeta_).getProiettili();
	}
	else return nullptr;
}

void Universo::uscitaPianeta() {
	pianetaAttuale = nullptr;
}

void Universo::controlloProiettili(proiettile_ptr lista_proiettili)
{
	if (pianetaAttuale != nullptr) {
		(*pianetaAttuale->pianeta_).controlloProiettili(lista_proiettili);
	}
}