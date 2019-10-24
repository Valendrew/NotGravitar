#include "mappa.hpp";
#include <iostream>;

Mappa::listaUniversi Mappa::addUniverso(int coordinata_universo_x, int coordinata_universo_y) {
	//quando creo un nuovo universo lo aggiungo in testa alla lista cosi da avere l'inserimento in O(1)
	listaUniversi tmp = new nodoMappa;
	tmp->posizione.x = coordinata_universo_x;
	tmp->posizione.y = coordinata_universo_y;
	tmp->universo = new Universo(larghezza_finestra_, altezza_finestra_);
	tmp->next = list_universi_;
	list_universi_ = tmp;
	return list_universi_;
}

Mappa::listaUniversi Mappa::findUniverso(int x, int y) {
	//Dato che ogni universo è associato ad una coppia di coordinate cosi da distinguelo in modo univoco per sapere se un
	//universo è gia presente in lista o meno cerco all'interno della lista un universo con le coordinate di interesse
	listaUniversi list_universi_tmp = list_universi_;
	listaUniversi ritorno = nullptr;
	bool found = false;
	while (list_universi_tmp != nullptr && !found)
	{
		if (list_universi_tmp->posizione.x == x && list_universi_tmp->posizione.y == y) {
			ritorno = list_universi_tmp;
			found = true;
		}
		list_universi_tmp = list_universi_tmp->next;
	}
	return ritorno;
}

void Mappa::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sfondo_);
	target.draw((*posizione_attuale_->universo));
}

Mappa::Mappa(int larghezza_finestra, int altezza_finestra) {

	
	statoAttacco = new bool();
	*statoAttacco = true;
	larghezza_finestra_ = larghezza_finestra;
	altezza_finestra_ = altezza_finestra;

	//entita_.setSize(sf::Vector2f(width_, height_));

	// texture dell'oggetto
	if (!texture_.loadFromFile("Texture/universo.jpg")) {

	}
	texture_.setRepeated(true);
	sfondo_ = sf::Sprite(texture_, sf::IntRect(0, 0, larghezza_finestra, altezza_finestra));

	srand(time(0));

	list_universi_ = new nodoMappa;
	list_universi_->posizione.x = 0;
	list_universi_->posizione.y = 0;
	list_universi_->universo = new Universo(larghezza_finestra, altezza_finestra);
	list_universi_->next = nullptr;

	universo_di_gioco_ = list_universi_;
	posizione_attuale_ = list_universi_;
}

Mappa::Mappa() : Mappa(1280, 720) {}

int Mappa::controlloPassaggioSuperficie(sf::Vector2f pos)
{
	int direzione = -1;
	if (posizione_attuale_ != nullptr) {
		direzione = (*posizione_attuale_->universo).controlloPassaggioSuperficie(pos);
	}
	return direzione;
}

bool Mappa::aggiornaPunteggioBunker()
{
	return (*posizione_attuale_->universo).aggiornaPunteggioBunker();
}

bool Mappa::aggiornaPunteggioPianeta()
{
	if (!(*posizione_attuale_->universo).restaUnSoloPianeta() && (*posizione_attuale_->universo).distruzionePianetaAttuale()) {

		(*posizione_attuale_->universo).cambiaColorePianeta();
		return true;
	}
	else return false;
}

bool Mappa::aggiornaPunteggioUniverso()
{
	if ((*posizione_attuale_->universo).distrutto()) {
		
		(*posizione_attuale_->universo).cambiaColorePianeta();
		return true;
	}
	else return false;
}

bool Mappa::controlloCollisioneSuperficie(sf::Vector2f pos) {
	bool ritorno = false;
	if (posizione_attuale_ != nullptr) {
		ritorno = (*posizione_attuale_->universo).controlloCollisioneSuperficie(pos);
	}
	return ritorno;
}

void Mappa::uscitaPianeta() {
	(*posizione_attuale_->universo).uscitaPianeta();
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
	if ((*universo_di_gioco_->universo).getDistrutto()) 
		*statoAttacco = false;
		
		listaUniversi posizione_attuale_tmp = posizione_attuale_;

		switch (direzione) {
		case 0:
			posizione_attuale_ = findUniverso(posizione_attuale_->posizione.x, posizione_attuale_->posizione.y + 1);
			//Se lo statoAttacco è false e la posizione cercata è nulla (ovvero sto cercando di andare in un uiverso nuovo) aggiorno la list_universi mettendo in testa il
			//nuovo universo e setto un bool a true
			if (posizione_attuale_ == nullptr && !(*statoAttacco)) {
				list_universi_ = addUniverso(posizione_attuale_tmp->posizione.x, posizione_attuale_tmp->posizione.y + 1);
				setStato = true;
			}
			break;
		case 1:
			posizione_attuale_ = findUniverso(posizione_attuale_->posizione.x + 1, posizione_attuale_->posizione.y);
			if (posizione_attuale_ == nullptr && !(*statoAttacco)) {
				list_universi_ = addUniverso(posizione_attuale_tmp->posizione.x + 1, posizione_attuale_tmp->posizione.y);
				setStato = true;
			}
			break;
		case 2:
			posizione_attuale_ = findUniverso(posizione_attuale_->posizione.x, posizione_attuale_->posizione.y - 1);
			if (posizione_attuale_ == nullptr && !(*statoAttacco)) {
				list_universi_ = addUniverso(posizione_attuale_tmp->posizione.x, posizione_attuale_tmp->posizione.y - 1);
				setStato = true;
			}
			break;
		case 3:
			posizione_attuale_ = findUniverso(posizione_attuale_->posizione.x - 1, posizione_attuale_->posizione.y);
			if (posizione_attuale_ == nullptr && !(*statoAttacco)) {
				list_universi_ = addUniverso(posizione_attuale_tmp->posizione.x - 1, posizione_attuale_tmp->posizione.y);
				setStato = true;
			}
			break;
		}
		//Se setStato è true significa che mi muovero verso un universo nuovo mai visitato e quindi setto statoAttacco a true, e aggiorno sia l'universo di gioco
		//sia la posizione attuale
		if (setStato) {
			*statoAttacco = true;
			posizione_attuale_ = list_universi_;
			universo_di_gioco_ = posizione_attuale_;
		}

		//Se setStato è false significa che non mi muoverso verso un universo nuovo
		//se non mi ci muovo perche tanto di andare verso un universo gia visitato

		else if (*statoAttacco) {

			//caso in cui l'universo in cui voglio andare non sia ancora stato sbloccato
			if (posizione_attuale_ == nullptr) {
				posizione_attuale_ = posizione_attuale_tmp;
				ritorno = false;
			}
			//Il caso in cui torno a visitare un universo gia distrutto è già gestito
		}
	return ritorno;
}

bool Mappa::ricercaPianeta(sf::Vector2f posizione) {
	return (*posizione_attuale_->universo).pianetaAttualeRicerca(posizione);
}

proiettile_ptr Mappa::getProiettili()
{
	return (*posizione_attuale_->universo).getProiettili();
}

int Mappa::controlloProiettili(proiettile_ptr lista_proiettili)
{
	return (*posizione_attuale_->universo).controlloProiettili(lista_proiettili);
}


void Mappa::restart(int width_, int height_) {

	*statoAttacco = true;
	universo_di_gioco_ = nullptr;
	posizione_attuale_ = nullptr;
	delete list_universi_;
	list_universi_ = new nodoMappa;
	list_universi_->posizione.x = 0;
	list_universi_->posizione.y = 0;
	list_universi_->universo = new Universo(width_, height_);
	list_universi_->next = nullptr;

	universo_di_gioco_ = list_universi_;
	posizione_attuale_ = list_universi_;
}