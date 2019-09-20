#include "pianeta.h"

Pianeta::Pianeta(int id, float cord_x, float cord_y, unsigned int width, unsigned int height) : superficie_(width, height){
	id_ = id;
	shape_.setRadius(25.0);
	shape_.setPointCount(100);
	shape_.setOrigin(0 + 25, 0 + 25);
	shape_.setPosition(cord_x, cord_y);
	shape_.setFillColor(sf::Color(255, 0, 0, 255));
}

sf::Vector2f Pianeta::getCoordinate()
{
	return shape_.getPosition();
}

int Pianeta::getRadius() {
	return shape_.getRadius();
}

void Pianeta::cambiaColore() {
	shape_.setFillColor(sf::Color(255, 0, 0, shape_.getFillColor().a - 25));
}

void Pianeta::drawSuperficie(sf::RenderTarget & target, sf::RenderStates states)
{
	target.draw(superficie_);
}

void Pianeta::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(shape_);
}
