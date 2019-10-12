#include "bunker.h"

void Bunker::spara()
{
	if (clock_.getElapsedTime().asMilliseconds() > 2000) {
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
	}
}

void Bunker::setDistrutto()
{
	distrutto_ = true;
	
	texture_.loadFromFile(nomeFileDistrutto_); // texture dell'oggetto
	entita_.setTexture(&texture_); // impostata la texture
}

proiettile_ptr Bunker::getProiettili()
{
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

Bunker::Bunker(unsigned int larghezza_finestra, unsigned int altezza_finestra, float vita, float danno, 
	const char nomeFile[], const char nomeFileDistrutto[], sf::Vector2f posizione, sf::Vector2f dimensione, float angolo_rotazione)
: Comportamento(larghezza_finestra, altezza_finestra, vita, danno, nomeFile, 
	nomeFileDistrutto, posizione, dimensione, angolo_rotazione) {
	distrutto_ = false;
	angolo_sparo_ = 25;

	entita_.setOrigin(0, 0 + dimensione.y);
}

Bunker::Bunker() : Comportamento() {
	distrutto_ = false;
	angolo_sparo_ = 25;
	entita_.setOrigin(0, 0 + 25);
}
