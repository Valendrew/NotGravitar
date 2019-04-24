#include "pianeta.h"

Pianeta::Pianeta(int id, float cord_x, float cord_y, unsigned int width, unsigned int height) : superficie_(width, height){
	id_ = id;
	shape_.setRadius(25.0);
	shape_.setPointCount(100);
	shape_.setPosition(cord_x, cord_y);
}
SuperficiePianeta Pianeta::getSuperficie()
{
	return superficie_;
}

void Pianeta::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(shape_);
}
