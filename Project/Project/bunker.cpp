#include "bunker.h"

void Bunker::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(shape_);
}

Bunker::Bunker(float cord_x, float cord_y, float size, float angolo_rotazione, sf::Texture texture)
{
	shape_.setOrigin(0, 0 + size); // viene aumentata di size per permettere che giacia sulla linea
	shape_.setPosition(cord_x, cord_y);
	shape_.setSize(sf::Vector2f(size, size));
	shape_.setRotation(angolo_rotazione);

	texture_ = texture;
	shape_.setTexture(&texture_);
	shape_.setFillColor(sf::Color::White);

}

Bunker::Bunker() : Bunker(0, 0, 32, 0, sf::Texture()) {}
