#include "bunker.h"
#include "bunker_stronger.h"

void BunkerStronger::spara()
{
	if (clock_.getElapsedTime().asMilliseconds() > 1000) {
		clock_.restart();

		//crea una nuovo proiettile e lo mette in cima alla lista
		proiettile_ptr p = new ProiettileNode;
		p->proiettile = new Proiettile(sf::Vector2f(5.f, 5.f), entita_.getPosition(), entita_.getRotation() + angolo_sparo_, .2f, danno_);
		p->next = proiettili_;
		proiettili_ = p;

		//crea una nuovo proiettile e lo mette in cima alla lista
		proiettile_ptr p2 = new ProiettileNode;
		p2->proiettile = new Proiettile(sf::Vector2f(5.f, 5.f), entita_.getPosition(), entita_.getRotation() - angolo_sparo_, .2f, danno_);
		p2->next = proiettili_;
		proiettili_ = p2;

		//crea una nuovo proiettile e lo mette in cima alla lista
		proiettile_ptr p3 = new ProiettileNode;
		p3->proiettile = new Proiettile(sf::Vector2f(5.f, 5.f), entita_.getPosition(), entita_.getRotation(), .2f, danno_);
		p3->next = proiettili_;
		proiettili_ = p3;
	}
}

BunkerStronger::BunkerStronger(unsigned int larghezza_finestra, unsigned int altezza_finestra, float vita, float danno, 
	const char nomeFile[], const char nomeFileDistrutto[], sf::Vector2f posizione, sf::Vector2f dimensione, float angolo_rotazione)
	: Bunker(larghezza_finestra, altezza_finestra, vita, danno, nomeFile, nomeFileDistrutto, posizione, dimensione, angolo_rotazione) {}

BunkerStronger::BunkerStronger() : Bunker() {}
