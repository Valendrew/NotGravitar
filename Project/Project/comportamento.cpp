#include "comportamento.h"

void Comportamento::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(entita_);
}

Comportamento::Comportamento(float vita,const char nomeFile[], sf::IntRect dimensione_texture, float cord_x, float cord_y, float larghezza_e, float altezza_e, float angolo_rotazione) {
	entita_.setPosition(cord_x, cord_y); // posizione dell'oggetto
	entita_.setSize(sf::Vector2f(larghezza_e, altezza_e)); // dimensione dell'oggetto
	entita_.setRotation(angolo_rotazione); // angolo di rotazione dell'oggetto
	entita_.setFillColor(sf::Color::White); // colore dell'oggetto

	texture_.loadFromFile(nomeFile, dimensione_texture); // texture dell'oggetto
	entita_.setTexture(&texture_); // impostata la texture*/
}
Comportamento::Comportamento() : Comportamento(50, "Texture/ship3.png", sf::IntRect(), 0, 0, 25, 25, 0) {}
