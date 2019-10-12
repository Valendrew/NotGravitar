#include "proiettile.hpp"

void Proiettile::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(proiettile_);
}

Proiettile::Proiettile(sf::Vector2f dimensione, sf::Vector2f posizione, float angolo, float velocita, float danno)
{
	proiettile_.setSize(dimensione);
	proiettile_.setPosition(posizione);
	proiettile_.setRotation(angolo);
	proiettile_.setFillColor(sf::Color::Green);

	double radianti = angolo * PI_G / 180.0;

	velocita_ = velocita;
	x_ = velocita_ * sin(radianti);
	y_ = -1 * velocita_ * cos(radianti);

	danno_ = danno;
}

Proiettile::Proiettile() : Proiettile(sf::Vector2f(), sf::Vector2f(), 0.f, 0.f, 0.f) {}

sf::RectangleShape Proiettile::getProiettile()
{
	return proiettile_;
}

float Proiettile::getVelocita()
{
	return velocita_;
}

void Proiettile::setVelocita(float velocita)
{
	velocita_ = velocita;
}

sf::FloatRect Proiettile::getGlobalBounds()
{
	return proiettile_.getGlobalBounds();
}

sf::Vector2f Proiettile::getPosition()
{
	return proiettile_.getPosition();
}

void Proiettile::setColor(sf::Color color)
{
	proiettile_.setFillColor(color);
}

void Proiettile::muovi()
{
	proiettile_.move(x_, y_);
}