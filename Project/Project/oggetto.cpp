#include "oggetto.h"


oggetto::oggetto(const char tipo[], const char nomeFile[],sf::Vector2f pos, float angolo_rotazione, sf::Vector2f size) {
	tipologia tipo_oggetto;

	if (strcmp(tipo, "BENZINA_BEST") == 0)
		tipo_oggetto = BENZINA_BEST;
	else if (strcmp(tipo, "BENZINA") == 0)
		tipo_oggetto = BENZINA;
	else
		tipo_oggetto = CUORE;
	
	tipo_ = tipo_oggetto;
	capacita_ = tipo_oggetto;

	texture_.loadFromFile(nomeFile);
	entita_.setTexture(&texture_);
	entita_.setPosition(pos);
	entita_.setRotation(angolo_rotazione);
	entita_.setSize(size);

	entita_.setOrigin(0, 0 + size.y);
}
oggetto::tipologia oggetto::getTipologia()
{
	return tipo_;
}
float oggetto::getCapacita()
{
	return capacita_;
}
void oggetto::draw(sf::RenderTarget & target, sf::RenderStates states) const {

		target.draw(entita_);
}
oggetto::oggetto() {}