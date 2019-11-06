#include "bunker.h"
#include "bunker_stronger.h"

void BunkerStronger::spara()
{
	/* Vengono generati 3 proiettili ogni 1500 millisecondi, solamente se il bunker � ancora in vita.
	I tre proiettili avranno rispettivamente un angolo di -angolo_sparo (rispetto all'angolo dell'entit�), 0 gradi
	e poi angolo_sparo*/
	if (clock_.getElapsedTime().asMilliseconds() > 1500 && !distrutto_) {
		clock_.restart();

		sf::Vector2f posizione_1;
		posizione_1.x = entita_.getPosition().x;
		posizione_1.y = entita_.getPosition().y - entita_.getSize().y;

		//crea una nuovo proiettile e lo mette in cima alla lista
		proiettile_ptr p = new ProiettileNode;
		p->proiettile = new Proiettile(sf::Vector2f(5.f, 5.f), posizione_1, entita_.getRotation() + angolo_sparo_, velocita_sparo_, danno_, colore_proiettile_);
		p->next = proiettili_;
		proiettili_ = p;

		//crea una nuovo proiettile e lo mette in cima alla lista
		proiettile_ptr p2 = new ProiettileNode;
		p2->proiettile = new Proiettile(sf::Vector2f(5.f, 5.f), posizione_1, entita_.getRotation() - angolo_sparo_, velocita_sparo_, danno_, colore_proiettile_);
		p2->next = proiettili_;
		proiettili_ = p2;

		//crea una nuovo proiettile e lo mette in cima alla lista
		proiettile_ptr p3 = new ProiettileNode;
		p3->proiettile = new Proiettile(sf::Vector2f(5.f, 5.f), posizione_1, entita_.getRotation(), velocita_sparo_, danno_, colore_proiettile_);
		p3->next = proiettili_;
		proiettili_ = p3;
	}
}

BunkerStronger::BunkerStronger(unsigned int larghezza_finestra, unsigned int altezza_finestra, float vita, float danno, 
	const char nomeFile[], const char nomeFileDistrutto[], sf::Vector2f posizione, sf::Vector2f dimensione, float angolo_rotazione)
	: Bunker(larghezza_finestra, altezza_finestra, vita, danno, nomeFile, nomeFileDistrutto, posizione, dimensione, angolo_rotazione) {
	colore_proiettile_ = sf::Color(195, 0, 0, 255); // viene impostato il colore dei proiettili del bunker
}

BunkerStronger::BunkerStronger() : Bunker() {
	colore_proiettile_ = sf::Color(195, 0, 0, 255);
}
