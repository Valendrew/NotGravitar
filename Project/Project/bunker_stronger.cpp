#include "bunker.h"
#include "bunker_stronger.h"

void BunkerStronger::spara()
{
	if (clock_.getElapsedTime().asMilliseconds() > 2000) {
		clock_.restart();

		proiettile_ptr p = new ProiettileNode;
		p->proiettile = new Proiettile(sf::Vector2f(5.f, 5.f), entita_.getPosition(), entita_.getRotation() + angolo_sparo, .2f); //crea una nuovo proiettile e lo mette in cima alla lista
		p->next = proiettili_;
		proiettili_ = p;

		proiettile_ptr p2 = new ProiettileNode;
		p2->proiettile = new Proiettile(sf::Vector2f(5.f, 5.f), entita_.getPosition(), entita_.getRotation() - angolo_sparo, .2f); //crea una nuovo proiettile e lo mette in cima alla lista
		p2->next = proiettili_;
		proiettili_ = p2;

		proiettile_ptr p3 = new ProiettileNode;
		p3->proiettile = new Proiettile(sf::Vector2f(5.f, 5.f), entita_.getPosition(), entita_.getRotation(), .2f); //crea una nuovo proiettile e lo mette in cima alla lista
		p3->next = proiettili_;
		proiettili_ = p3;
	}
}

BunkerStronger::BunkerStronger(unsigned int width, unsigned int height, float vita, const char nomeFile[], const char nomeFileDistrutto[50], sf::Vector2f pos, sf::Vector2f size, float angolo_rotazione)
	: Bunker(width, height, vita, nomeFile, nomeFileDistrutto, pos, size, angolo_rotazione) {}

BunkerStronger::BunkerStronger() : Bunker() {}
