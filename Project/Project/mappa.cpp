#include "mappa.hpp";
#include <iostream>;

Mappa::listaUniversi Mappa::aggiungiSistemaSolare(int coordinata_universo_x, int coordinata_universo_y) {
	//quando creo un nuovo universo lo aggiungo in testa alla lista cosi da avere l'inserimento in O(1)
	listaUniversi tmp = new nodoMappa;
	tmp->posizione.x = coordinata_universo_x;
	tmp->posizione.y = coordinata_universo_y;
	tmp->universo = new Universo(larghezza_finestra_, altezza_finestra_);
	tmp->next = list_universi_;
	list_universi_ = tmp;
	return list_universi_;
}

Mappa::listaUniversi Mappa::cercaSistemaSolare(int x, int y) {
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
	
	stato_attacco_ = true;
	larghezza_finestra_ = larghezza_finestra;
	altezza_finestra_ = altezza_finestra;

	//entita_.setSize(sf::Vector2f(width_, height_));

	// texture dell'oggetto
	texture_.loadFromFile("Texture/universo_1.png");
	texture_.setRepeated(true);
	sfondo_ = sf::Sprite(texture_, sf::IntRect(0, 0, larghezza_finestra, altezza_finestra));
	//sfondo_.setScale(sf::Vector2f(2, 2));

	srand(time(0));

	list_universi_ = new nodoMappa;
	list_universi_->posizione.x = 0;
	list_universi_->posizione.y = 0;
	list_universi_->universo = new Universo(larghezza_finestra, altezza_finestra);
	list_universi_->next = nullptr;

	sistema_solare_di_gioco_ = list_universi_;
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

bool Mappa::controlloCollisioneSuperficie(sf::Vector2f pos) {
	bool ritorno = false;
	if (posizione_attuale_ != nullptr) {
		ritorno = (*posizione_attuale_->universo).controlloCollisioneSuperficie(pos);
	}
	return ritorno;
}

void Mappa::uscitaPianeta() {
	if(posizione_attuale_ != nullptr)
	(*posizione_attuale_->universo).uscitaPianeta();
}

bool Mappa::spostamentoSistemaSolare(int direzione) {
	/*
		0 = nord
		1 = est
		2 = sud
		3 = ovest

		In base alla posizione in cui la navicella si sposta creo (se non gia presenti) gli universi vicini a quello nel quale
		mi sono appena spostato
	*/
	bool movimento_ = true, set_stato_ = false;
	//Se nel sistema solare attuale ho distrutto tutti i pianeti setto lo statoAttacco a false
	if (sistema_solare_di_gioco_ != nullptr && (*sistema_solare_di_gioco_->universo).getDistrutto())
		stato_attacco_ = false;
		
		listaUniversi posizione_attuale_tmp = posizione_attuale_;

		switch (direzione) {
		case 0:
			posizione_attuale_ = cercaSistemaSolare(posizione_attuale_->posizione.x, posizione_attuale_->posizione.y + 1);
			/*Se lo statoAttacco è false e la posizione cercata è nulla 
			(ovvero sto cercando di andare in un sistema nuovo) aggiorno la list_universi mettendo in testa il
			nuovo sistema solare e setto un bool a true*/
			if (posizione_attuale_ == nullptr && !(stato_attacco_)) {
				list_universi_ = aggiungiSistemaSolare(posizione_attuale_tmp->posizione.x, posizione_attuale_tmp->posizione.y + 1);
				set_stato_ = true;
			}
			break;
		case 1:
			posizione_attuale_ = cercaSistemaSolare(posizione_attuale_->posizione.x + 1, posizione_attuale_->posizione.y);
			if (posizione_attuale_ == nullptr && !(stato_attacco_)) {
				list_universi_ = aggiungiSistemaSolare(posizione_attuale_tmp->posizione.x + 1, posizione_attuale_tmp->posizione.y);
				set_stato_ = true;
			}
			break;
		case 2:
			posizione_attuale_ = cercaSistemaSolare(posizione_attuale_->posizione.x, posizione_attuale_->posizione.y - 1);
			if (posizione_attuale_ == nullptr && !(stato_attacco_)) {
				list_universi_ = aggiungiSistemaSolare(posizione_attuale_tmp->posizione.x, posizione_attuale_tmp->posizione.y - 1);
				set_stato_ = true;
			}
			break;
		case 3:
			posizione_attuale_ = cercaSistemaSolare(posizione_attuale_->posizione.x - 1, posizione_attuale_->posizione.y);
			if (posizione_attuale_ == nullptr && !(stato_attacco_)) {
				list_universi_ = aggiungiSistemaSolare(posizione_attuale_tmp->posizione.x - 1, posizione_attuale_tmp->posizione.y);
				set_stato_ = true;
			}
			break;
		}
		/*Se setStato è true significa che mi muovero verso un sistema 
		nuovo, mai visitato e quindi setto statoAttacco a true, aggiorno sia il sistema solare di gioco
		sia la posizione attuale*/
		if (set_stato_) {
			stato_attacco_ = true;
			posizione_attuale_ = list_universi_;
			sistema_solare_di_gioco_ = posizione_attuale_;
		}

		//Se set_stato è false significa che non mi muovero verso un sistema nuovo
		//se non mi ci muovo è perche tanto di andare verso un universo gia visitato

		else if (stato_attacco_) {

			//caso in cui il sistema in cui voglio andare non sia ancora stato sbloccato
			if (posizione_attuale_ == nullptr) {
				posizione_attuale_ = posizione_attuale_tmp;
				movimento_ = false;
			}
			//Il caso in cui torno a visitare un sistema gia distrutto è già gestito
		}
	return movimento_;
}

bool Mappa::ricercaPianeta(sf::Vector2f posizione) {

	if(posizione_attuale_ != nullptr)
	return (*posizione_attuale_->universo).ricercaPianetaAttuale(posizione);
	else return false;
}

proiettile_ptr Mappa::getProiettili()
{
	if (posizione_attuale_ != nullptr) {
		return (*posizione_attuale_->universo).getProiettili();
	}
	else return nullptr;
}

int Mappa::controlloProiettili(proiettile_ptr lista_proiettili)
{
	if (posizione_attuale_ != nullptr) {
		return (*posizione_attuale_->universo).controlloProiettili(lista_proiettili);
	}
	else return 0;
}

Tipologia Mappa::controlloRaggio(sf::ConvexShape raggio)
{
	Tipologia aggetto_assorbito = DEFAULT;

	if (posizione_attuale_ != nullptr)
		aggetto_assorbito = (*posizione_attuale_->universo).controlloRaggio(raggio);

	return aggetto_assorbito;
	
}

bool Mappa::aggiornaPunteggioBunker()
{
	if(posizione_attuale_ != nullptr)
	return (*posizione_attuale_->universo).aggiornaPunteggioBunker();
	else return false;
}

bool Mappa::aggiornaPunteggioPianeta()
{
	if (posizione_attuale_ != nullptr && (*posizione_attuale_->universo).distruzionePianetaAttuale())
		return true;
	else return false;
}

bool Mappa::aggiornaPunteggioSistemaSolare()
{
	if (posizione_attuale_ != nullptr && (*posizione_attuale_->universo).distrutto())
		return true;
	else return false;
}

void Mappa::restart(int width_, int height_) {
	/*Metodo per il restart in cui vengono reinizializzati gli attributi*/


	stato_attacco_ = true;
	sistema_solare_di_gioco_ = nullptr;
	posizione_attuale_ = nullptr;
	delete list_universi_;
	list_universi_ = new nodoMappa;
	list_universi_->posizione.x = 0;
	list_universi_->posizione.y = 0;
	list_universi_->universo = new Universo(width_, height_);
	list_universi_->next = nullptr;

	sistema_solare_di_gioco_ = list_universi_;
	posizione_attuale_ = list_universi_;
}