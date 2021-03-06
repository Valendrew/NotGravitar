#include "proiettile.hpp"

void Proiettile::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(proiettile_);
}

Proiettile::Proiettile(sf::Vector2f dimensione, sf::Vector2f posizione, float angolo, float velocita, float danno, sf::Color colore)
{
	proiettile_.setSize(dimensione);
	proiettile_.setPosition(posizione);
	proiettile_.setRotation(angolo);
	proiettile_.setFillColor(colore);

	double radianti = angolo * PI_G / 180.0;

	velocita_ = velocita;
	x_ = velocita_ * sin(radianti);
	y_ = -1 * velocita_ * cos(radianti);

	danno_ = danno;
}

Proiettile::Proiettile() : Proiettile(sf::Vector2f(), sf::Vector2f(), 0.f, 0.f, 0.f, sf::Color::Red) {}

void Proiettile::setDistrutto()
{
	danno_ = 0;
	proiettile_.setFillColor(sf::Color::Transparent);
}

float Proiettile::getDanno()
{
	return danno_;
}

sf::Vector2f Proiettile::getPosition()
{
	return proiettile_.getPosition();
}

sf::RectangleShape Proiettile::getProiettile()
{
	return proiettile_;
}

sf::FloatRect Proiettile::getGlobalBounds()
{
	return proiettile_.getGlobalBounds();
}

void Proiettile::muovi()
{
	proiettile_.move(x_, y_);
}