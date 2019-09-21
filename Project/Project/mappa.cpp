#include "mappa.hpp";

Mappa::Mappa() : Mappa(1280, 720) {}

Mappa::Mappa(int width_, int height_) {

	/*
	quando inizializzo la mappa creo 5 universi: quello di spawn associato alle coordinate (0,0)
	e quelli nelle 4 direzioni possibili che l'astronave potrà visitare
	*/
	width = width_;
	height = height_; 
	distanza = 2;
	srand(time(0));
	list_universi = new nodoMappa;
	list_universi->c.x = -1;
	list_universi->c.y = 0;
	list_universi->u = new Universo(distanza, width_, height_);
	
	list_universi->next = NULL;
	list_universi = addUniverso(0, 1);
	list_universi = addUniverso(1, 0);
	list_universi = addUniverso(0, -1);
	list_universi = addUniverso(0, 0);
	//setto a true il "visitato" dell' universo 0,0 dato che è quello di spawn 
	(*findUniverso(0, 0)->u).setVisitato();
	universoDiGioco = list_universi;
	posizioneAttuale = list_universi;
}
listaUniversi Mappa::addUniverso(int coordinata_universo_x, int coordinata_universo_y) {
	//quando creo un nuovo universo lo aggiungo in testa alla lista cosi da avere l'inserimento in O(1)
	listaUniversi tmp = new nodoMappa;
	tmp->c.x = coordinata_universo_x;
	tmp->c.y = coordinata_universo_y;
	tmp->u = new Universo(distanza, width, height);
	tmp->next = list_universi;
	list_universi = tmp;
	return list_universi;
}
listaUniversi Mappa::findUniverso(int x, int y) {
	//Dato che ogni universo è associato ad una coppia di coordinate cosi da distinguelo in modo univoco per sapere se un
	//universo è gia presente in lista o meno cerco all'interno della lista un universo con le coordinate di interesse
	listaUniversi appoggio = list_universi;
	listaUniversi ritorno = NULL;
	bool found = false;
	while (appoggio != NULL && !found)
	{
		if (appoggio->c.x == x && appoggio->c.y == y) {
			ritorno = appoggio;
			found = true;
		}
		appoggio = appoggio->next;
	}
	return ritorno;
}

void Mappa::spostamento(int direzione) {
	/*
		0 = nord
		1 = est
		2 = sud
		3 = ovest

		In base alla posizione in cui la navicella si sposta creo (se non gia presenti) gli universi vicini a quello nel quale
		mi sono appena spostato
	*/
	switch (direzione) {
	case 0:
		posizioneAttuale = findUniverso(posizioneAttuale->c.x, posizioneAttuale->c.y + 1);

		if (!(*(posizioneAttuale->u)).getVisitato())
		{
			if (findUniverso(posizioneAttuale->c.x - 1, posizioneAttuale->c.y) == NULL)
				list_universi = addUniverso(posizioneAttuale->c.x - 1, posizioneAttuale->c.y);

			if (findUniverso(posizioneAttuale->c.x + 1, posizioneAttuale->c.y) == NULL)
				list_universi = addUniverso(posizioneAttuale->c.x + 1, posizioneAttuale->c.y);

			if (findUniverso(posizioneAttuale->c.x, posizioneAttuale->c.y + 1) == NULL)
				list_universi = addUniverso(posizioneAttuale->c.x, posizioneAttuale->c.y + 1);
		}

		(*posizioneAttuale->u).setVisitato();
		break;
	case 1:
		posizioneAttuale = findUniverso(posizioneAttuale->c.x + 1, posizioneAttuale->c.y);

		if (!(*(posizioneAttuale->u)).getVisitato())
		{
			if (findUniverso(posizioneAttuale->c.x, posizioneAttuale->c.y + 1) == NULL)
				list_universi = addUniverso(posizioneAttuale->c.x, posizioneAttuale->c.y + 1);

			if (findUniverso(posizioneAttuale->c.x + 1, posizioneAttuale->c.y) == NULL)
				list_universi = addUniverso(posizioneAttuale->c.x + 1, posizioneAttuale->c.y);

			if (findUniverso(posizioneAttuale->c.x, posizioneAttuale->c.y - 1) == NULL)
				list_universi = addUniverso(posizioneAttuale->c.x, posizioneAttuale->c.y - 1);
		}

		(*posizioneAttuale->u).setVisitato();
		break;
	case 2:
		posizioneAttuale = findUniverso(posizioneAttuale->c.x, posizioneAttuale->c.y - 1);

		if (!(*(posizioneAttuale->u)).getVisitato())
		{
			if (findUniverso(posizioneAttuale->c.x - 1, posizioneAttuale->c.y) == NULL)
				list_universi = addUniverso(posizioneAttuale->c.x - 1, posizioneAttuale->c.y);

			if (findUniverso(posizioneAttuale->c.x + 1, posizioneAttuale->c.y) == NULL)
				list_universi = addUniverso(posizioneAttuale->c.x + 1, posizioneAttuale->c.y);

			if (findUniverso(posizioneAttuale->c.x, posizioneAttuale->c.y - 1) == NULL)
				list_universi = addUniverso(posizioneAttuale->c.x, posizioneAttuale->c.y - 1);
		}

		(*posizioneAttuale->u).setVisitato();
		break;
	case 3:
		posizioneAttuale = findUniverso(posizioneAttuale->c.x - 1, posizioneAttuale->c.y);

		if (!(*(posizioneAttuale->u)).getVisitato())
		{
			if (findUniverso(posizioneAttuale->c.x, posizioneAttuale->c.y + 1) == NULL)
				list_universi = addUniverso(posizioneAttuale->c.x, posizioneAttuale->c.y + 1);

			if (findUniverso(posizioneAttuale->c.x - 1, posizioneAttuale->c.y) == NULL)
				list_universi = addUniverso(posizioneAttuale->c.x - 1, posizioneAttuale->c.y);

			if (findUniverso(posizioneAttuale->c.x, posizioneAttuale->c.y - 1) == NULL)
				list_universi = addUniverso(posizioneAttuale->c.x, posizioneAttuale->c.y - 1);
		}

		(*posizioneAttuale->u).setVisitato();
		break;
	default:
		break;
	}
}

listaUniversi Mappa::getPosizioneAttuale() {
	return posizioneAttuale;
}

bool Mappa::ricercaPianeta(int x_astronave, int y_astronave) {
	return (posizioneAttuale->u)->pianetaAttualeRicerca(x_astronave, y_astronave);
}

void Mappa::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(*posizioneAttuale->u);
}