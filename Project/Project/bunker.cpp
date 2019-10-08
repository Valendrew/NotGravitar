#include "bunker.h"

void Bunker::spara()
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
	}
}

void Bunker::setDistrutto()
{
	distrutto = true;
	
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

Bunker::Bunker(unsigned int width, unsigned int height, float vita, const char nomeFile[], const char nomeFileDistrutto[], sf::Vector2f pos, sf::Vector2f size, float angolo_rotazione)
: Comportamento(width, height, vita, nomeFile, pos, size, angolo_rotazione) {
	int i = 0;
	while (nomeFileDistrutto[i] != '\0')
	{
		nomeFileDistrutto_[i] = nomeFileDistrutto[i];
		i++;
	}

	distrutto = false;
	angolo_sparo = 25;
	entita_.setOrigin(0, 0 + size.y);
}

Bunker::Bunker() : Comportamento() {
	distrutto = false;
	angolo_sparo = 45;
	entita_.setOrigin(0, 0 + 25);
}
