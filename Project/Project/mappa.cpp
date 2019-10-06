#include "mappa.hpp";

Mappa::Mappa() : Mappa(1280, 720) {}

Mappa::Mappa(int width_, int height_) {

	/*
	qu
ando inizializzo la mappa creo 5 universi: quello di spawn associato alle coordinate (0,0)
	e quelli nelle 4 direzioni possibili che l'astronave potrà visitare
	*/

	statoAttacco = true;
	width = width_;
	height = height_;

	entita_.setSize(sf::Vector2f(width_, height_));
	texture_.loadFromFile("Texture/universo.jpg"); // texture dell'oggetto
	entita_.setTexture(&texture_);
	srand(time(0));
	/*list_universi = new nodoMappa;
	list_universi->c.x = -1;
	list_universi->c.y = 0;
	list_universi->u = new Universo(width_, height_);
	
	list_universi->next = nullptr;
	list_universi = addUniverso(0, 1);
	list_universi = addUniverso(1, 0);
	list_universi = addUniverso(0, -1);
	list_universi = addUniverso(0, 0);*/

	list_universi = new nodoMappa;
	list_universi->c.x = 0;
	list_universi->c.y = 0;
	list_universi->u = new Universo(width_, height_);
	list_universi->next = nullptr;

	//setto a true il "visitato" dell' universo 0,0 dato che è quello di spawn 
	(*findUniverso(0, 0)->u).setVisitato();
	universoDiGioco = list_universi;
	posizioneAttuale = list_universi;
}

int Mappa::controlloPassaggioSuperficie(sf::Vector2f pos)
{
	int direzione = -1;
	if (posizioneAttuale != nullptr) {
		direzione = (*posizioneAttuale->u).controlloPassaggioSuperficie(pos);
	}
	return direzione;
}

listaUniversi Mappa::addUniverso(int coordinata_universo_x, int coordinata_universo_y) {
	//quando creo un nuovo universo lo aggiungo in testa alla lista cosi da avere l'inserimento in O(1)
	listaUniversi tmp = new nodoMappa;
	tmp->c.x = coordinata_universo_x;
	tmp->c.y = coordinata_universo_y;
	tmp->u = new Universo(width, height);
	tmp->next = list_universi;
	list_universi = tmp;
	return list_universi;
}
bool Mappa::controlloCollisioneSuperficie(sf::Vector2f pos) {
	bool ritorno = false;
	if (posizioneAttuale != nullptr) {
		ritorno = (*posizioneAttuale->u).controlloCollisioneSuperficie(pos);
	}
	return ritorno;
}
void Mappa::uscitaPianeta() {
	(*posizioneAttuale->u).uscitaPianeta();
}
listaUniversi Mappa::findUniverso(int x, int y) {
	//Dato che ogni universo è associato ad una coppia di coordinate cosi da distinguelo in modo univoco per sapere se un
	//universo è gia presente in lista o meno cerco all'interno della lista un universo con le coordinate di interesse
	listaUniversi appoggio = list_universi;
	listaUniversi ritorno = nullptr;
	bool found = false;
	while (appoggio != nullptr && !found)
	{
		if (appoggio->c.x == x && appoggio->c.y == y) {
			ritorno = appoggio;
			found = true;
		}
		appoggio = appoggio->next;
	}
	return ritorno;
}

bool Mappa::spostamento(int direzione) {
	/*
		0 = nord
		1 = est
		2 = sud
		3 = ovest

		In base alla posizione in cui la navicella si sposta creo (se non gia presenti) gli universi vicini a quello nel quale
		mi sono appena spostato
	*/
	bool ritorno = true, setStato = false;
	//Se nell'universo attuale ho distrutto tutti i pianeti setto lo statoAttacco a false
	if ((*universoDiGioco->u).distrutto()) statoAttacco = false;
		
		listaUniversi app = posizioneAttuale;
		switch (direzione) {
		case 0:
			posizioneAttuale = findUniverso(posizioneAttuale->c.x, posizioneAttuale->c.y + 1);
			//Se lo statoAttacco è false e la posizione cercata è nulla (ovvero sto cercando di andare in un uiverso nuovo) aggiorno la list_universi mettendo in testa il
			//nuovo universo e setto un bool a true
			if (posizioneAttuale == nullptr && !statoAttacco) {
				list_universi = addUniverso(app->c.x, app->c.y + 1);
				setStato = true;
			}
			break;
		case 1:
			posizioneAttuale = findUniverso(posizioneAttuale->c.x + 1, posizioneAttuale->c.y);
			if (posizioneAttuale == nullptr && !statoAttacco) {
				list_universi = addUniverso(app->c.x + 1, app->c.y);
				setStato = true;
			}
			break;
		case 2:
			posizioneAttuale = findUniverso(posizioneAttuale->c.x, posizioneAttuale->c.y - 1);
			if (posizioneAttuale == nullptr && !statoAttacco) {
				list_universi = addUniverso(app->c.x, app->c.y - 1);
				setStato = true;
			}
			break;
		case 3:
			posizioneAttuale = findUniverso(posizioneAttuale->c.x - 1, posizioneAttuale->c.y);
			if (posizioneAttuale == nullptr && !statoAttacco) {
				list_universi = addUniverso(app->c.x - 1, app->c.y);
				setStato = true;
			}
			break;
		}
		//Se setStato è true significa che mi muovero verso un universo nuovo mai visitato e quindi setto statoAttacco a true, e aggiorno sia l'universo di gioco
		//sia la posizione attuale
		if (setStato) {
			statoAttacco = true;
			universoDiGioco = posizioneAttuale;
			posizioneAttuale = list_universi;
		}
		//Se setStato è false significa che non mi muoverso verso un universo nuovo
		//se non mi ci muovo perche tanto di andare verso un universo gia es
		else if (statoAttacco) {
			if (posizioneAttuale == nullptr) {
				posizioneAttuale = app;
				ritorno = false;
			}
		}
	
	return ritorno;
}

bool Mappa::ricercaPianeta(int x_astronave, int y_astronave) {
	return (posizioneAttuale->u)->pianetaAttualeRicerca(x_astronave, y_astronave);
}

proiettile_ptr Mappa::getProiettili()
{
	return (posizioneAttuale->u)->getProiettili();
}

void Mappa::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(entita_);
	target.draw(*posizioneAttuale->u);
}