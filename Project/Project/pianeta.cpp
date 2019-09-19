#include "pianeta.h"

Pianeta::Pianeta(int id, float cord_x, float cord_y, unsigned int width, unsigned int height) : superficie_(width, height){
	id_ = id;
	shape_.setRadius(25.0);
	shape_.setPointCount(100);
	shape_.setOrigin(0 + 25, 0 + 25);
	shape_.setPosition(cord_x, cord_y);
}
SuperficiePianeta Pianeta::getSuperficie()
{
	return superficie_;
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
