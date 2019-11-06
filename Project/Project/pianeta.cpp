#include "pianeta.h"
#include <iostream>

void Pianeta::generaSuperficie()
{
	/* Viene assegnato un colore alle superfici in base
	alla tipologia del pianeta (acqua, fuoco, erba) */
	sf::Color colore_superficie;
	switch (tipo_pianeta_)
	{
	case ACQUA: colore_superficie = sf::Color(66, 191, 232);
		break;
	case FUOCO: colore_superficie = sf::Color(232, 138, 54);
		break;
	case ERBA: colore_superficie = sf::Color(66, 164, 89);
		break;
	default:
		colore_superficie == sf::Color::Magenta;
		break;
	}
	int superfici_generate = 0;

	while (superfici_generate < numero_superfici_)
	{
		SuperficiePianeta *new_sup;

		if (superfici_generate == 0) {
			new_sup = new SuperficiePianeta(larghezza_finestra_, altezza_finestra_, colore_superficie);
		}
		else if (superfici_generate == numero_superfici_ - 1) {
			sf::Vector2f last_vertex = (*superficie_head_->superficie_item).getLastVertex();
			sf::Vector2f first_vertex = (*superficie_tail_->superficie_item).getFirstVertex();

			new_sup = new SuperficiePianeta(larghezza_finestra_, altezza_finestra_, last_vertex, first_vertex, colore_superficie);
		}
		else {
			sf::Vector2f last_vertex = (*superficie_head_->superficie_item).getLastVertex();
			new_sup = new SuperficiePianeta(larghezza_finestra_, altezza_finestra_, last_vertex, sf::Vector2f(), colore_superficie);
		}

		if (superficie_head_ == nullptr) {
			superficie_head_ = new SuperficieNode();
			superficie_head_->superficie_item = new_sup;
			superficie_head_->prev = nullptr;
			superficie_head_->next = nullptr;

			superficie_tail_ = superficie_head_;
		}
		else {
			superficie_ptr tmp_sup = new SuperficieNode();
			tmp_sup->superficie_item = new_sup;
			tmp_sup->next = superficie_head_;
			tmp_sup->prev = nullptr;


			superficie_head_->prev = tmp_sup;

			superficie_head_ = tmp_sup;
		}

		superfici_generate++;
	}
}

int Pianeta::bunkerRimanenti() {
	int bunker_rimanenti = 0;
	superficie_ptr tmp_superficie = superficie_head_;

	while (tmp_superficie != nullptr)
	{
		bunker_rimanenti += (*tmp_superficie->superficie_item).getNumeroBunker();

		tmp_superficie = tmp_superficie->next;
	}

	return bunker_rimanenti;
}

Pianeta::Pianeta(float raggio, int id, sf::Vector2f posizione, unsigned int larghezza_finestra, unsigned int altezza_finestra, const char tipologia[], const char texture[], const char texture_distrutto[]) {
	id_ = id; // id pianeta
	distrutto_ = false;
	pianeta_.setRadius(raggio); // raggio del pianeta
	pianeta_.setPointCount(100); 
	pianeta_.setOrigin(0 , 0);
	pianeta_.setPosition(posizione);

	// Viene impostato il tipo del pianeta tra i tre disponibili
	if (strcmp(tipologia, "ACQUA") == 0) {
		tipo_pianeta_ = ACQUA;
	}
	else if (strcmp(tipologia, "FUOCO") == 0) {
		tipo_pianeta_ = FUOCO;
	}
	else {
		tipo_pianeta_ = ERBA;
	}
	
	// Caricamento della texture
	texture_.loadFromFile(texture);
	pianeta_.setTexture(&texture_);

	texture_distrutto_.loadFromFile(texture_distrutto);

	larghezza_finestra_ = larghezza_finestra;
	altezza_finestra_ = altezza_finestra;

	// Vengono impostato a nulli i due puntatore per gestire le superfici
	superficie_head_ = nullptr;
	superficie_tail_ = nullptr;

	// Vengono generate le superfici
	numero_superfici_ = 3;
	generaSuperficie();

	/* Viene impostato il numero totale dei bunker */
	superficie_ptr superficie_tmp = superficie_head_;

	while (superficie_tmp != nullptr) {

		numero_bunker_precedenti += (*superficie_tmp->superficie_item).getNumeroBunker();
		superficie_tmp = superficie_tmp->next;
	}

	superficie_attuale_ = superficie_tail_;
}

Pianeta::Pianeta() :Pianeta(0, 0, sf::Vector2f(), 1280, 720, "ACQUA", "/Texture/acqua.png", "/Texture/acqua_d.png") {}

float Pianeta::getRaggio() {
	return pianeta_.getRadius();
}

sf::Vector2f Pianeta::getPosition()
{
	return pianeta_.getPosition();
}

sf::FloatRect Pianeta::getGlobalBounds()
{
	return pianeta_.getGlobalBounds();
}

bool Pianeta::distruzioneSingoloBunker()
{
	bool distrutto = false;
	int bunker_rimanenti_ = bunkerRimanenti();
	//il controllo != 0 è presente poiche se il numero di bunker rimanenti è 0 siamo nel caso in cui l'intero pianeta è distrutto

	if (bunker_rimanenti_ != 0 && bunker_rimanenti_ < numero_bunker_precedenti) {
		distrutto = true;
        numero_bunker_precedenti = bunker_rimanenti_;
	}

	return distrutto;
}

void Pianeta::isDistrutto()
{
	bool distrutto = true;

		superficie_ptr superficie_head_tmp = superficie_head_;

		while (superficie_head_tmp != nullptr && distrutto) {

			if (!(*superficie_head_tmp->superficie_item).getDistrutta())
				distrutto = false;

			superficie_head_tmp = superficie_head_tmp->next;
		}
		if (distrutto) {
			distrutto_ = true;
			pianeta_.setTexture(&texture_distrutto_);
		}

}

bool Pianeta::getDistrutto()
{  
	if (!distrutto_) 
		isDistrutto();

	return distrutto_;
}

int Pianeta::controlloPassaggioSuperficie(sf::Vector2f posizione)
{
	/* Viene effettuato un controllo per verificare se la posizione è oltre il bordo, in
	modo tale da cambiare schermata per mostrare la superficie corretta. Se la posizione è
	minore di 0, allora si dovrà spostare il puntatore delle superfici verso destra (->next),
	in caso contrario verso sinistra (->prev). Viene effettuato un controllo nel caso si esca dalla lista*/

	int direzione = -1;
	int offset = 0;

	if (posizione.x <= 0 + offset) {
		(*superficie_attuale_->superficie_item).resetProiettiliBunker();

		direzione = 0;

		if (superficie_attuale_->next == nullptr) {
			superficie_attuale_ = superficie_head_;
		}
		else {
			superficie_attuale_ = superficie_attuale_->next;
		}
	}
	else if (posizione.x >= larghezza_finestra_ - offset) {
		(*superficie_attuale_->superficie_item).resetProiettiliBunker();
		direzione = 1;
		
		if (superficie_attuale_->prev == nullptr) {
			superficie_attuale_ = superficie_tail_;
		}
		else {
			superficie_attuale_ = superficie_attuale_->prev;
		}
	}
	return direzione;
}

bool Pianeta::controlloCollisioneSuperficie(sf::Vector2f posizione)
{
	/* Richiama il metodo per controllare la collisione dell'entità con la superficie*/
	bool collisione_superficie = false;
	if (superficie_attuale_ != nullptr) {
		collisione_superficie = (*superficie_attuale_->superficie_item).controlloCollisioneSuperficie(posizione);
	}
	
	return collisione_superficie;
}

Tipologia Pianeta::controlloRaggio(sf::ConvexShape raggio)
{
	Tipologia aggetto_assorbito = DEFAULT;

	if (superficie_attuale_ != nullptr)
		aggetto_assorbito = (*superficie_attuale_->superficie_item).controlloRaggio(raggio);
	
	return aggetto_assorbito;
	
}

void Pianeta::resetProiettiliBunker()
{
	if (superficie_attuale_ != nullptr) {
		(*superficie_attuale_->superficie_item).resetProiettiliBunker();
	}
}

proiettile_ptr Pianeta::getProiettili()
{
	if (superficie_attuale_ != nullptr)
		return (*superficie_attuale_->superficie_item).getProiettili();
	else
		return nullptr;
}

int Pianeta::controlloProiettili(proiettile_ptr lista_proiettili)
{
	if (superficie_attuale_ != nullptr)
		return (*superficie_attuale_->superficie_item).controlloProiettili(lista_proiettili);
	else return 0;
}

void Pianeta::drawSuperficie(sf::RenderTarget & target, sf::RenderStates states)
{
	if (superficie_attuale_ != nullptr)	
		target.draw((*superficie_attuale_->superficie_item));
}

void Pianeta::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(pianeta_);
}