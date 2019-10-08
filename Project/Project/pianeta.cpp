#include "pianeta.h"

Pianeta::Pianeta(int id, float cord_x, float cord_y, unsigned int width, unsigned int height) {
	id_ = id;
	shape_.setRadius(25.0);
	shape_.setPointCount(100);
	numero_superfici_ = 3;
	shape_.setOrigin(0 , 0);
	shape_.setPosition(cord_x, cord_y);
	shape_.setFillColor(sf::Color(255, 0, 0, 255));

	larghezza_finestra = width;
	altezza_finestra = height;

	numero_superfici_ = 3;
	generaSuperficie();

	superficie_attuale_ = superficie_tail;
	distrutto_ = false;
}

int Pianeta::getRaggio() {
	return (int) shape_.getRadius();
}

sf::Vector2f Pianeta::getPosizione()
{
	return shape_.getPosition();
}

void Pianeta::cambiaColore() {
	shape_.setFillColor(sf::Color(255, 0, 0, shape_.getFillColor().a - 25));
}

bool Pianeta::getDistrutto() {
	return distrutto_;
}

int Pianeta::controlloPassaggioSuperficie(sf::Vector2f pos)
{
	int direzione = -1;

	if (pos.x <= 0) {
		direzione = 0;

		if (superficie_attuale_->next == nullptr) {
			superficie_attuale_ = superficie_head;
		}
		else {
			superficie_attuale_ = superficie_attuale_->next;
		}
	}
	else if (pos.x >= larghezza_finestra) {
		direzione = 1;
		
		if (superficie_attuale_->prev == nullptr) {
			superficie_attuale_ = superficie_tail;
		}
		else {
			superficie_attuale_ = superficie_attuale_->prev;
		}
	}
	return direzione;
}

bool Pianeta::controlloCollisioneSuperficie(sf::Vector2f pos)
{
	if (superficie_attuale_ != nullptr) {
		return (*superficie_attuale_->superficie_item).controlloCollisioneSuperficie(pos);
	}
	else return false;
}

proiettile_ptr Pianeta::getProiettili()
{
	return (*superficie_attuale_->superficie_item).getProiettili();
}

void Pianeta::controlloProiettili(proiettile_ptr lista_proiettili)
{
	(*superficie_attuale_->superficie_item).controlloProiettili(lista_proiettili);
}

void Pianeta::drawSuperficie(sf::RenderTarget & target, sf::RenderStates states)
{
	//target.draw(superficie_1_);
	if (superficie_attuale_ != nullptr)	
		target.draw((*superficie_attuale_->superficie_item));
}

void Pianeta::generaSuperficie()
{
	int superfici_generate = 0;

	while (superfici_generate < numero_superfici_)
	{
		SuperficiePianeta *new_sup;

		if (superfici_generate == 0) {
			new_sup = new SuperficiePianeta(larghezza_finestra, altezza_finestra);
		}
		else if (superfici_generate == numero_superfici_ - 1) {
			sf::Vector2f last_vertex = (*superficie_head->superficie_item).getLastVertex();
			sf::Vector2f first_vertex = (*superficie_tail->superficie_item).getFirstVertex();

			new_sup = new SuperficiePianeta(larghezza_finestra, altezza_finestra, last_vertex, first_vertex);
		}
		else {
			sf::Vector2f last_vertex = (*superficie_head->superficie_item).getLastVertex();
			new_sup = new SuperficiePianeta(larghezza_finestra, altezza_finestra, last_vertex, sf::Vector2f());
		}
		
		if (superficie_head == nullptr) {
			superficie_head = new SuperficieNode();
			superficie_head->superficie_item = new_sup;
			superficie_head->prev = nullptr;
			superficie_head->next = nullptr;

			superficie_tail = superficie_head;
		}
		else {
			superficie_ptr tmp_sup = new SuperficieNode();
			tmp_sup->superficie_item = new_sup;
			tmp_sup->next = superficie_head;
			tmp_sup->prev = nullptr;


			superficie_head->prev = tmp_sup;

			superficie_head = tmp_sup;
		}

		superfici_generate++;
	}
}

void Pianeta::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(shape_);
}