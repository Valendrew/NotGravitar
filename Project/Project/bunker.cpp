#include "bunker.h"

void Bunker::spara()
{
	/* Vengono generati due proiettili ogni 1200 millisecondi, solamente se il bunker è ancora in vita.
	I due proiettili avranno rispettivamente un angolo di -angolo_sparo (rispetto all'angolo dell'entità) e angolo_sparo*/
	if (clock_.getElapsedTime().asMilliseconds() > 1200 && !distrutto_) {
		clock_.restart();
		
		sf::Vector2f posizione_1;
		posizione_1.x = entita_.getPosition().x;
		posizione_1.y = entita_.getPosition().y - entita_.getSize().y;

		//crea una nuovo proiettile e lo mette in cima alla lista
		proiettile_ptr p = new ProiettileNode;
		p->proiettile = new Proiettile(sf::Vector2f(5.f, 5.f), posizione_1, entita_.getRotation() - angolo_sparo_, velocita_sparo_, danno_, colore_proiettile_);
		p->next = proiettili_;
		proiettili_ = p;

		//crea una nuovo proiettile e lo mette in cima alla lista
		proiettile_ptr p2 = new ProiettileNode;
		p2->proiettile = new Proiettile(sf::Vector2f(5.f, 5.f), posizione_1, entita_.getRotation() + angolo_sparo_, velocita_sparo_, danno_, colore_proiettile_);
		p2->next = proiettili_;
		proiettili_ = p2;
	}
}

void Bunker::aggiornaBarraVita()
{
	/* Viene aggiornato il rettangolo della vita (sotto al bunker), in modo da regolare la parte
	di vita rimanente (blu) e quella eliminata (rossa) correttamente */
	vita_rimanente_.setSize(sf::Vector2f(vita_ * entita_.getSize().x / vita_massima_, 10));
	vita_eliminta_.setSize(sf::Vector2f(entita_.getSize().x - vita_rimanente_.getSize().x, 10));

	sf::Vector2f posizione(entita_.getPosition().x, altezza_finestra_ * 0.90);

	vita_rimanente_.setPosition(posizione);
	vita_eliminta_.setPosition(posizione.x + vita_rimanente_.getSize().x, posizione.y);
}

proiettile_ptr Bunker::getProiettili()
{
	/* Viene restituita una lista che equivale alla lista dei proiettili del bunker */
	proiettile_ptr list_proiettili = nullptr;
	proiettile_ptr tmp_list = proiettili_;

	while (tmp_list != nullptr)
	{
		Proiettile p = (*tmp_list->proiettile);

		if (list_proiettili == nullptr) {
			list_proiettili = new ProiettileNode();
			list_proiettili->proiettile = tmp_list->proiettile;
			list_proiettili->next = nullptr;
		}
		else {
			proiettile_ptr tmp_list_proiettili = new ProiettileNode();
			tmp_list_proiettili->proiettile = tmp_list->proiettile;
			tmp_list_proiettili->next = list_proiettili;

			list_proiettili = tmp_list_proiettili;
		}
		tmp_list = tmp_list->next;
	}

	return list_proiettili;
}

void Bunker::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (distrutto_ && !mostra_esplosione_) {
		target.draw(esplosione_);
	}

	target.draw(vita_rimanente_);
	target.draw(vita_eliminta_);
}

Bunker::Bunker(unsigned int larghezza_finestra, unsigned int altezza_finestra, float vita, float danno,
	const char nomeFile[], const char nomeFileDistrutto[], sf::Vector2f posizione, sf::Vector2f dimensione, float angolo_rotazione)
: Comportamento(larghezza_finestra, altezza_finestra, vita, danno, nomeFile, 
	nomeFileDistrutto, posizione, dimensione, angolo_rotazione) {
	angolo_sparo_ = 25;
	entita_.setOrigin(0, 0 + dimensione.y);
	vita_massima_ = vita;
	colore_proiettile_ = sf::Color(0, 153, 219, 255); // viene impostato il colore dei proiettili del bunker
	
	// Viene creato un rettangolo sottostante il bunker per indicare la vita rimanente
	vita_rimanente_.setFillColor(sf::Color::Blue);
	vita_eliminta_.setFillColor(sf::Color::Red);
	aggiornaBarraVita();
}

Bunker::Bunker() : Comportamento() {
	angolo_sparo_ = 25;
	entita_.setOrigin(0, 0 + 25);
	colore_proiettile_ = sf::Color(0, 153, 219, 255);
}
