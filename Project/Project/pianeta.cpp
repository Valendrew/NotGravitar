#include "pianeta.h"

void Pianeta::generaSuperficie()
{
	int superfici_generate = 0;

	while (superfici_generate < numero_superfici_)
	{
		SuperficiePianeta *new_sup;

		if (superfici_generate == 0) {
			new_sup = new SuperficiePianeta(larghezza_finestra_, altezza_finestra_);
		}
		else if (superfici_generate == numero_superfici_ - 1) {
			sf::Vector2f last_vertex = (*superficie_head_->superficie_item).getLastVertex();
			sf::Vector2f first_vertex = (*superficie_tail_->superficie_item).getFirstVertex();

			new_sup = new SuperficiePianeta(larghezza_finestra_, altezza_finestra_, last_vertex, first_vertex);
		}
		else {
			sf::Vector2f last_vertex = (*superficie_head_->superficie_item).getLastVertex();
			new_sup = new SuperficiePianeta(larghezza_finestra_, altezza_finestra_, last_vertex, sf::Vector2f());
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

		//all'inizio bunker_precedenti conterra il valore dei bunker totali
		bunker_precedenti_ += (*superficie_head_->superficie_item).getNumeroBunker();
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

Pianeta::Pianeta(int id, sf::Vector2f posizione, unsigned int larghezza_finestra, unsigned int altezza_finestra) {
	bunker_precedenti_ = 0;

	id_ = id;
	distrutto_ = false;
	pianeta_.setRadius(25.0);
	pianeta_.setPointCount(100);
	numero_superfici_ = 3;
	pianeta_.setOrigin(0 , 0);
	pianeta_.setPosition(posizione);
	pianeta_.setFillColor(sf::Color(255, 0, 0, 255));

	larghezza_finestra_ = larghezza_finestra;
	altezza_finestra_ = altezza_finestra;

	superficie_head_ = nullptr;
	superficie_tail_ = nullptr;

	numero_superfici_ = 3;
	generaSuperficie();

	superficie_attuale_ = superficie_tail_;
}

Pianeta::Pianeta() :Pianeta(0, sf::Vector2f(), 1280, 720) {}

float Pianeta::getRaggio() {
	return pianeta_.getRadius();
}

sf::Vector2f Pianeta::getPosizione()
{
	return pianeta_.getPosition();
}

//void Pianeta::cambiaColore() {
//	pianeta_.setFillColor(sf::Color(255, 0, 0, pianeta_.getFillColor().a - 25));
//}

void Pianeta::distrutto() {
	if (bunkerRimanenti() == 0)
		distrutto_ = true;
}

bool Pianeta::distruzioneSingoloBunker()
{
	bool ritorno = false;
	//il controllo != 0 è presente poiche se il numero di bunker rimanenti è 0 siamo nel caso in cui l'intero pianeta è distrutto
	if (bunkerRimanenti() != 0 && bunkerRimanenti() < bunker_precedenti_) {
		ritorno = true;
		bunker_precedenti_--;
	}
	return ritorno;
}

bool Pianeta::isDistrutto()
{
	return distrutto_;
}

int Pianeta::controlloPassaggioSuperficie(sf::Vector2f posizione)
{
	int direzione = -1;

	if (posizione.x <= 0) {
		direzione = 0;

		if (superficie_attuale_->next == nullptr) {
			superficie_attuale_ = superficie_head_;
		}
		else {
			superficie_attuale_ = superficie_attuale_->next;
		}
	}
	else if (posizione.x >= larghezza_finestra_) {
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
	if (superficie_attuale_ != nullptr) {
		return (*superficie_attuale_->superficie_item).controlloCollisioneSuperficie(posizione);
	}
	else return false;
}

proiettile_ptr Pianeta::getProiettili()
{
	if (superficie_attuale_ != nullptr)
		return (*superficie_attuale_->superficie_item).getProiettili();
	else
		return nullptr;
}

void Pianeta::controlloProiettili(proiettile_ptr lista_proiettili)
{
	if (superficie_attuale_ != nullptr)
		(*superficie_attuale_->superficie_item).controlloProiettili(lista_proiettili);
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