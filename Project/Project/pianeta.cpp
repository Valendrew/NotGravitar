#include "pianeta.h"

sf::Vector2f Pianeta::getCoordinate()
{
	return shape_.getPosition();
}

Pianeta::Pianeta(int id, float cord_x, float cord_y, unsigned int width, unsigned int height) : superficie_(width, height){
	id_ = id;
	shape_.setRadius(25.0);
	shape_.setPointCount(100);
	shape_.setOrigin(0 + 25, 0 + 25);
	shape_.setPosition(cord_x, cord_y);
	shape_.setFillColor(sf::Color(255, 0, 0, 255));
}
int Pianeta::getRadius() {
	return shape_.getRadius();
}
{
	shape_.setFillColor(sf::Color(255, 0, 0, shape_.getFillColor().a - 25));
}

void Pianeta::drawSuperficie(sf::RenderTarget & target, sf::RenderStates states)
{
	target.draw(superficie_);
}

/*Pianeta::Pianeta(int id, float cord_x, float cord_y, unsigned int width, unsigned int height) {
	float radius = 20.0;
	id_ = id;
	shape_.setRadius(radius);
	shape_.setPointCount(100);
	shape_.setPosition(cord_x, cord_y);

}*/
void Pianeta::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(shape_);
}
