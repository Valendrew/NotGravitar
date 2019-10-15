#include "oggetto.h"


oggetto::oggetto(tipologia tipo, const char nomeFile[],sf::Vector2f pos, float angolo_rotazione, sf::Vector2f size) {
	tipo_ = tipo;
	capacita_ = tipo;
	texture_.loadFromFile(nomeFile);
	entita_.setTexture(&texture_);
	entita_.setPosition(pos);
	entita_.setRotation(angolo_rotazione);
	entita_.setSize(size);
}
tipologia oggetto::getTipologia()
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
oggetto::oggetto(){}
