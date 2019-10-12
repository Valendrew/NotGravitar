#include "mappa.hpp";

Mappa::listaUniversi Mappa::addUniverso(int coordinata_universo_x, int coordinata_universo_y) {
	//quando creo un nuovo universo lo aggiungo in testa alla lista cosi da avere l'inserimento in O(1)
	listaUniversi tmp = new nodoMappa;
	tmp->c.x = coordinata_universo_x;
	tmp->c.y = coordinata_universo_y;
	tmp->u = new Universo(larghezza_finestra_, altezza_finestra_);
	tmp->next = list_universi_;
	list_universi_ = tmp;
	return list_universi_;
}

Mappa::listaUniversi Mappa::findUniverso(int x, int y) {
	//Dato che ogni universo è associato ad una coppia di coordinate cosi da distinguelo in modo univoco per sapere se un
	//universo è gia presente in lista o meno cerco all'interno della lista un universo con le coordinate di interesse
	listaUniversi appoggio = list_universi_;
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

void Mappa::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(entita_);
	target.draw((*posizioneAttuale_->u));
}

Mappa::Mappa(int larghezza_finestra, int altezza_finestra) {

	/*
	qu
ando inizializzo la mappa creo 5 universi: quello di spawn associato alle coordinate (0,0)
	e quelli nelle 4 direzioni possibili che l'astronave potrà visitare
	*/

	statoAttacco = true;
	larghezza_finestra_ = larghezza_finestra;
	altezza_finestra_ = altezza_finestra;

	//entita_.setSize(sf::Vector2f(width_, height_));

	// texture dell'oggetto
	if (!texture_.loadFromFile("Texture/universo.png")) {

	}
	texture_.setRepeated(true);
	entita_ = sf::Sprite(texture_, sf::IntRect(0, 0, larghezza_finestra, altezza_finestra));

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

	list_universi_ = new nodoMappa;
	list_universi_->c.x = 0;
	list_universi_->c.y = 0;
	list_universi_->u = new Universo(larghezza_finestra, altezza_finestra);
	list_universi_->next = nullptr;

	//setto a true il "visitato" dell' universo 0,0 dato che è quello di spawn 
	(*findUniverso(0, 0)->u).setVisitato();
	universoDiGioco_ = list_universi_;
	posizioneAttuale_ = list_universi_;
}

Mappa::Mappa() : Mappa(1280, 720) {}

int Mappa::controlloPassaggioSuperficie(sf::Vector2f pos)
{
	int direzione = -1;
	if (posizioneAttuale_ != nullptr) {
		direzione = (*posizioneAttuale_->u).controlloPassaggioSuperficie(pos);
	}
	return direzione;
}

bool Mappa::controlloCollisioneSuperficie(sf::Vector2f pos) {
	bool ritorno = false;
	if (posizioneAttuale_ != nullptr) {
		ritorno = (*posizioneAttuale_->u).controlloCollisioneSuperficie(pos);
	}
	return ritorno;
}

void Mappa::uscitaPianeta() {
	(*posizioneAttuale_->u).uscitaPianeta();
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
	if ((*universoDiGioco_->u).distrutto()) statoAttacco = false;
		
		listaUniversi app = posizioneAttuale_;
		switch (direzione) {
		case 0:
			posizioneAttuale_ = findUniverso(posizioneAttuale_->c.x, posizioneAttuale_->c.y + 1);
			//Se lo statoAttacco è false e la posizione cercata è nulla (ovvero sto cercando di andare in un uiverso nuovo) aggiorno la list_universi mettendo in testa il
			//nuovo universo e setto un bool a true
			if (posizioneAttuale_ == nullptr && !statoAttacco) {
				list_universi_ = addUniverso(app->c.x, app->c.y + 1);
				setStato = true;
			}
			break;
		case 1:
			posizioneAttuale_ = findUniverso(posizioneAttuale_->c.x + 1, posizioneAttuale_->c.y);
			if (posizioneAttuale_ == nullptr && !statoAttacco) {
				list_universi_ = addUniverso(app->c.x + 1, app->c.y);
				setStato = true;
			}
			break;
		case 2:
			posizioneAttuale_ = findUniverso(posizioneAttuale_->c.x, posizioneAttuale_->c.y - 1);
			if (posizioneAttuale_ == nullptr && !statoAttacco) {
				list_universi_ = addUniverso(app->c.x, app->c.y - 1);
				setStato = true;
			}
			break;
		case 3:
			posizioneAttuale_ = findUniverso(posizioneAttuale_->c.x - 1, posizioneAttuale_->c.y);
			if (posizioneAttuale_ == nullptr && !statoAttacco) {
				list_universi_ = addUniverso(app->c.x - 1, app->c.y);
				setStato = true;
			}
			break;
		}
		//Se setStato è true significa che mi muovero verso un universo nuovo mai visitato e quindi setto statoAttacco a true, e aggiorno sia l'universo di gioco
		//sia la posizione attuale
		if (setStato) {
			statoAttacco = true;
			universoDiGioco_ = posizioneAttuale_;
			posizioneAttuale_ = list_universi_;
		}
		//Se setStato è false significa che non mi muoverso verso un universo nuovo
		//se non mi ci muovo perche tanto di andare verso un universo gia es
		else if (statoAttacco) {
			if (posizioneAttuale_ == nullptr) {
				posizioneAttuale_ = app;
				ritorno = false;
			}
		}
	
	return ritorno;
}

bool Mappa::ricercaPianeta(int x_astronave, int y_astronave) {
	return (posizioneAttuale_->u)->pianetaAttualeRicerca(x_astronave, y_astronave);
}

proiettile_ptr Mappa::getProiettili()
{
	return (*posizioneAttuale_->u).getProiettili();
}

void Mappa::controlloProiettili(proiettile_ptr lista_proiettili)
{
	(*posizioneAttuale_->u).controlloProiettili(lista_proiettili);
}

Universo Mappa::getUniversoDiGioco() {
	return *(universoDiGioco_->u);
}

coordinate Mappa::getPosizioneAttuale() {
	return (posizioneAttuale_->c);
}

coordinate Mappa::getPosizioneDiGioco() {
	return universoDiGioco_->c;
}

void Mappa::restart(int width_, int height_) {

	statoAttacco = true;
	universoDiGioco_ = nullptr;
	posizioneAttuale_ = nullptr;
	delete list_universi_;
	list_universi_ = new nodoMappa;
	list_universi_->c.x = 0;
	list_universi_->c.y = 0;
	list_universi_->u = new Universo(width_, height_);
	list_universi_->next = nullptr;

	//setto a true il "visitato" dell' universo 0,0 dato che è quello di spawn 
	(*findUniverso(0, 0)->u).setVisitato();
	universoDiGioco_ = list_universi_;
	posizioneAttuale_ = list_universi_;
}