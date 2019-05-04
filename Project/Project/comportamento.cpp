#include "comportamento.h"

void Comportamento::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(entita_);
}

Comportamento::Comportamento(float vita,const char nomeFile[], sf::IntRect dimensione_texture, float cord_x, float cord_y, float larghezza_e, float altezza_e, float angolo_rotazione) {
	entita_.setPosition(cord_x, cord_y);
	entita_.setSize(sf::Vector2f(larghezza_e, altezza_e));
	entita_.setRotation(angolo_rotazione);
	entita_.setFillColor(sf::Color::White);

	texture_.loadFromFile(nomeFile, dimensione_texture);
	entita_.setTexture(&texture_);

}
Comportamento::Comportamento() : Comportamento(50, "default.png", sf::IntRect(0, 0, 20, 20), 0, 0, 25, 25, 0) {}
