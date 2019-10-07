#include "proiettile.hpp"

void Proiettile::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(proiettile_);
}

sf::RectangleShape Proiettile::getProiettile()
{
	return proiettile_;
}

Proiettile::Proiettile() : Proiettile(sf::Vector2f(0, 0), sf::Vector2f(0, 0), 0.f, 0.f) {}

Proiettile::Proiettile(sf::Vector2f dim, sf::Vector2f pos, float angolo, float velocita)
{
	proiettile_.setSize(dim);
	proiettile_.setPosition(pos);
	proiettile_.setRotation(angolo);
	proiettile_.setFillColor(sf::Color::Green);

	double radianti = angolo * PI_G / 180.0;

	velocita_ = velocita;
	x = velocita_ * sin(radianti);
	y = -1 * velocita_ * cos(radianti);
}

void Proiettile::setVelocita(float velocita)
{
	velocita_ = velocita;
}

float Proiettile::getVelocita()
{
	return velocita_;
}

void Proiettile::muovi()
{
	proiettile_.move(x, y);
}

sf::FloatRect Proiettile::getGlobalBounds()
{
	return proiettile_.getGlobalBounds();
}
