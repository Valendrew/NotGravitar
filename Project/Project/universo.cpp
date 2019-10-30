#include "universo.hpp";
#include <iostream>

void Universo::generaPianeti() {
	int spawn_x = dimensioni_celle_.x;
	int spawn_y = dimensioni_celle_.y;
	int i = 1, j = 1;
	while (i < 17)
	{
		while (j < 23)
		{
			if (matrice_spawn_[i][j])
			{
				char tipologia_pianeta[50];
				char texture_pianeta[50];
				char texture_pianeta_distrutto[50];

				ottieniTipologiaPianeta(tipologia_pianeta, texture_pianeta, texture_pianeta_distrutto);

				Pianeta* pi = new Pianeta(id_pianeta_, sf::Vector2f(spawn_x, spawn_y), larghezza_finestra_, altezza_finestra_, tipologia_pianeta, texture_pianeta, texture_pianeta_distrutto);
				id_pianeta_++;

				inserimentoLista(pi);
			}
			spawn_x += dimensioni_celle_.x;
			j++;
		}
		spawn_x = 0;
		spawn_y += dimensioni_celle_.y;
		j = 0;
		i++;
	}
}

void Universo::ottieniTipologiaPianeta(char tipologia[], char texture[], char texture_d[])
{
	int tipo = rand() % 3;

	switch (tipo)
	{
	case 0: {
		char tipo_copy[] = "ACQUA";
		char texture_copy[] = "Texture/pianeta_acqua_1.png";
		char texture_d_copy[] = "Texture/pianeta_acqua_1d.png";

		copiaStringa(tipologia, 50, tipo_copy);
		copiaStringa(texture, 50, texture_copy);
		copiaStringa(texture_d, 50, texture_d_copy);
	} break;
	case 1: {
		char tipo_copy[] = "FUOCO";
		char texture_copy[] = "Texture/pianeta_fuoco_1.png";
		char texture_d_copy[] = "Texture/pianeta_fuoco_1d.png";

		copiaStringa(tipologia, 50, tipo_copy);
		copiaStringa(texture, 50, texture_copy);
		copiaStringa(texture_d, 50, texture_d_copy);
	} break;
	case 2: {
		char tipo_copy[] = "ERBA";
		char texture_copy[] = "Texture/pianeta_erba_1.png";
		char texture_d_copy[] = "Texture/pianeta_erba_1d.png";

		copiaStringa(tipologia, 50, tipo_copy);
		copiaStringa(texture, 50, texture_copy);
		copiaStringa(texture_d, 50, texture_d_copy);
	} break;
	default:
		break;
	}
}

void Universo::copiaStringa(char stringa[], int lunghezza, char stringa_da_copiare[])
{
	int i = 0;
	while (stringa_da_copiare[i] != '\0')
	{
		stringa[i] = stringa_da_copiare[i];
		i++;
	}
	stringa[i] = '\0';
}

void Universo::inserimentoLista(Pianeta* p) {
	if (lista_pianeti_ == nullptr) {
		lista_pianeti_ = new nodoPianeta;
		lista_pianeti_->pianeta_ = p;
		lista_pianeti_->next = nullptr;
	}
	else {
		listaPianeti tmp = new nodoPianeta;
		tmp->pianeta_ = p;
		tmp->next = lista_pianeti_;
		lista_pianeti_ = tmp;
	}
}

void Universo::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	listaPianeti pianeti_print = lista_pianeti_;

	if (pianeta_attuale_ == nullptr) {
		while (pianeti_print != nullptr) {
			target.draw(*pianeti_print->pianeta_);
			pianeti_print = pianeti_print->next;
		}
	}
	else {
		(*pianeta_attuale_->pianeta_).drawSuperficie(target, states);
	}
}

Universo::Universo(int larghezza_finestra, int altezza_finestra) {
	larghezza_finestra_ = larghezza_finestra;
	altezza_finestra_ = altezza_finestra;
	dimensioni_celle_.x = larghezza_finestra / 24;
	dimensioni_celle_.y = altezza_finestra / 18;

	numero_pianeti_ = rand() % 2 + 4; //Pianeti da 4 a 5
	//numero_pianeti_ = 1;
	visitato_ = false;
	distrutto_ = false;
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

	 generaPianeti();
	numero_pianeti_precedenti_ = numero_pianeti_;
}

Universo::Universo() :Universo(1280, 720) {}

bool Universo::ricercaPianetaAttuale(sf::Vector2f posizione) {
	listaPianeti lista_pianeti_tmp = lista_pianeti_;
	pianeta_attuale_ = nullptr;
	bool found = false;
	while (lista_pianeti_tmp != nullptr && !found) {

		int x_pianeta = (*lista_pianeti_tmp->pianeta_).getPosition().x;
		int y_pianeta = (*lista_pianeti_tmp->pianeta_).getPosition().y;
		int radius_pianeta = (*lista_pianeti_tmp->pianeta_).getRaggio();

		if ((*lista_pianeti_tmp->pianeta_).getGlobalBounds().contains(posizione)) {
			pianeta_attuale_ = lista_pianeti_tmp;
			found = true;
		}
		lista_pianeti_tmp = lista_pianeti_tmp->next;
	}
	return found;
}

bool Universo::distrutto() {
	bool distrutto = true;
	listaPianeti lista_pianeti_tmp = lista_pianeti_;

	if (!(distrutto_)) {

		while (lista_pianeti_tmp != nullptr && distrutto) {
			((*lista_pianeti_tmp->pianeta_).getDistrutto());
			if (!((*lista_pianeti_tmp->pianeta_).getDistrutto()))
				distrutto = false;

			lista_pianeti_tmp = lista_pianeti_tmp->next;
		}
		if (distrutto) {
			distrutto_ = true;
		}
	}
	else {
		distrutto = false;
	}

	return distrutto;
}

bool Universo::getDistrutto()
{
	return distrutto_;
}

bool Universo::aggiornaPunteggioBunker()
{
	if (pianeta_attuale_ != nullptr && (*pianeta_attuale_->pianeta_).distruzioneSingoloBunker())
		return true;
	else return false;
}

bool Universo::distruzionePianetaAttuale()
{
	int pianeti_rimanenti = pianetiRimanenti();
	bool distrutto = false;

	if (pianeti_rimanenti != 0 && pianeti_rimanenti < numero_pianeti_precedenti_) {
		numero_pianeti_precedenti_ = pianeti_rimanenti;
		distrutto = true;
	}
	return distrutto;
}

int Universo::controlloPassaggioSuperficie(sf::Vector2f pos)
{
	int direzione = -1;

	if (pianeta_attuale_ != nullptr) {
		direzione = (*pianeta_attuale_->pianeta_).controlloPassaggioSuperficie(pos);
	}
	return direzione;
}

bool Universo::controlloCollisioneSuperficie(sf::Vector2f pos) {
	bool collisione = false;

	if (pianeta_attuale_ != nullptr) {
		collisione = (*pianeta_attuale_->pianeta_).controlloCollisioneSuperficie(pos);
	}
	return collisione;
}

proiettile_ptr Universo::getProiettili()
{
	if (pianeta_attuale_ != nullptr) {
		return (*pianeta_attuale_->pianeta_).getProiettili();
	}
	else return nullptr;
}

void Universo::uscitaPianeta() {
	if (pianeta_attuale_ != nullptr) {
		(*pianeta_attuale_->pianeta_).resetProiettiliBunker();
	}
	pianeta_attuale_ = nullptr;
}

Oggetto Universo::controlloRaggio(sf::ConvexShape raggio)
{
	if (pianeta_attuale_ != nullptr)
		return (*pianeta_attuale_->pianeta_).controlloRaggio(raggio);
	else {
		Oggetto oggetto_nullo("BENZINA", "", sf::Vector2f(), 0, sf::Vector2f());
		return oggetto_nullo;
	}
}

int Universo::controlloProiettili(proiettile_ptr lista_proiettili)
{
	if (pianeta_attuale_ != nullptr) {
		return (*pianeta_attuale_->pianeta_).controlloProiettili(lista_proiettili);
	}
	else return 0;
}

int Universo::pianetiRimanenti()
{
	int num_pianeti_rimanenti = 0;
	listaPianeti lista_pianeti_tmp = lista_pianeti_;

	while (lista_pianeti_tmp != nullptr) {

		if (!(*lista_pianeti_tmp->pianeta_).getDistrutto()) {
			num_pianeti_rimanenti++;
		 }

		lista_pianeti_tmp = lista_pianeti_tmp->next;
	}
	return num_pianeti_rimanenti;
}

