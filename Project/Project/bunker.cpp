#include "bunker.h"

void Bunker::spara()
{
	if (clock_.getElapsedTime().asMilliseconds() > 500) {
		clock_.restart();

		proiettile_ptr p = new ProiettileNode;
		p->proiettile = new Proiettile(sf::Vector2f(5.f, 5.f), entita_.getPosition(), entita_.getRotation() + angolo_sparo, .6f); //crea una nuovo proiettile e lo mette in cima alla lista
		p->next = proiettili_;
		proiettili_ = p;

		proiettile_ptr p2 = new ProiettileNode;
		p2->proiettile = new Proiettile(sf::Vector2f(5.f, 5.f), entita_.getPosition(), entita_.getRotation() - angolo_sparo, .6f); //crea una nuovo proiettile e lo mette in cima alla lista
		p2->next = proiettili_;
		proiettili_ = p2;
	}
}

proiettile_ptr Bunker::getProiettili()
{
	proiettile_ptr list_proiettili = proiettili_;
	return list_proiettili;
}

Bunker::Bunker(unsigned int width, unsigned int height, float vita, const char nomeFile[], sf::Vector2f pos, sf::Vector2f size, float angolo_rotazione)
: Comportamento(width, height, vita, nomeFile, pos, size, angolo_rotazione) {
	distrutto = false;
	angolo_sparo = 25;
	entita_.setOrigin(0, 0 + size.y);
}

Bunker::Bunker() : Comportamento() {
	distrutto = false;
	angolo_sparo = 45;
	entita_.setOrigin(0, 0 + 25);
}
