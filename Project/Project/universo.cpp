#include "universo.hpp";

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

listaPianeti Universo::generaPianeti(listaPianeti p) {
	int spawn_x = dimensioniCelle.x;
	int spawn_y = dimensioniCelle.y;
	int i = 1, j = 1; 
	while (i<17)
	{
		while (j<23)
		{
			if (matriceSpawn[i][j])
			{
				Pianeta* pi = new Pianeta(idPianeta, spawn_x, spawn_y, width, height);//25 è il radius del pianeta
				idPianeta++;

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
			spawn_x += dimensioniCelle.x;
			j++;
		}
		spawn_x = 0;
		spawn_y += dimensioniCelle.y;
		j = 0;
		i++;
	}
	return p;
}

Universo::Universo(int width_, int height_) {
	width = width_;
	height = height_;
	entita_.setSize(sf::Vector2f(width_, height_));
	texture_.loadFromFile("Texture/universo.png"); // texture dell'oggetto
	entita_.setTexture(&texture_);
	dimensioniCelle.x = width_ / 24;
	dimensioniCelle.y = height_ / 18;
	listaPianeti p = nullptr;
	numeroPianeti = rand() % 2 + 4; //Pianeti da 4 a 5
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
	std::cout << numeroPianeti;
}

Universo::Universo() :Universo(1280, 720)
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

listaPianeti Universo::getPianetaAttuale() {
	return pianetaAttuale;
}
bool Universo::distrutto() {
	bool ritorno = true;
	listaPianeti app = lista_Pianeti;
	while (app!=nullptr && ritorno){
		if (!((*app->pianeta_).getDistrutto())) ritorno = false;
	}
	return ritorno;
}
bool Universo::controlloCollisioneSuperficie(sf::VertexArray Bordo) {
	bool ritorno = false;
	if (pianetaAttuale != nullptr) {
		ritorno = (*pianetaAttuale->pianeta_).controlloCollisioneSuperficie(Bordo);
	}
	return ritorno;
}
void Universo::uscitaPianeta() {
	pianetaAttuale = nullptr;
}
bool Universo::pianetaAttualeRicerca(int x_astronave, int y_astronave) {
	listaPianeti app = lista_Pianeti;
	pianetaAttuale = nullptr;
	bool found = false;

	while (app != nullptr && !found) {
		int x_pianeta = (*app->pianeta_).getPosizione().x;
		int y_pianeta = (*app->pianeta_).getPosizione().y;
		int radius_pianeta = (*app->pianeta_).getRaggio();
		

		if ((x_pianeta <= x_astronave && x_astronave <= x_pianeta + radius_pianeta*2) && (y_pianeta <= y_astronave && y_astronave <= y_pianeta + radius_pianeta*2)) {
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
	target.draw(entita_);

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
