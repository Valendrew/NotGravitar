#include "Proiettile.hpp"

Proiettile::Proiettile()
{
	Proiettile::Proiettile(sf::Vector2f(0, 0), sf::Vector2f(0, 0), 0.f, 0.f);
}

Proiettile::Proiettile(sf::Vector2f dim, sf::Vector2f pos, float angolo, float velocita_)
{
	this->setSize(dim);
	this->setPosition(pos);
	this->setRotation(angolo);
	this->setFillColor(sf::Color::Green);
	velocita = velocita_;
	double radianti = this->getRotation()*PI / 180.f;
	x = this->velocita*sin(radianti);
	y = -1 * this->velocita*cos(radianti);
}

void Proiettile::setVelocita(float velocita_)
{
	velocita = velocita_;
}

float Proiettile::getVelocita()
{
	return velocita;
}

void Proiettile::muovi()
{
	this->move(x, y);
}
