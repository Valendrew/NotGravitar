#include "oggetto.h"


Oggetto::Oggetto(Tipologia tipo, const char nomeFile[],sf::Vector2f pos, float angolo_rotazione, sf::Vector2f size)
{
	
	tipo_ = tipo;
	capacita_ = tipo;

	texture_.loadFromFile(nomeFile);
	entita_.setTexture(&texture_);
	entita_.setPosition(pos);
	entita_.setRotation(angolo_rotazione);
	entita_.setSize(size);

	entita_.setOrigin(0, 0 + size.y);
}

Oggetto::Oggetto() {
	tipo_ = BENZINA_BEST;
	capacita_ = 10;
}
Tipologia Oggetto::getTipologia()
{
	return tipo_;
}

sf::Vector2f Oggetto::getPosition()
{
	return entita_.getPosition();
}

void Oggetto::draw(sf::RenderTarget & target, sf::RenderStates states) const {

		target.draw(entita_);
}