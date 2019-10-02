#include "comportamento.h"

void Comportamento::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(entita_);

	proiettile_ptr p = proiettili_;
	while (p != NULL)	// Aggiorna la li posizione della lista dei proiettili,		forse da spostare in funzione a parte!!
	{
		target.draw((*p->proiettile).getProiettile());
		(*p->proiettile).muovi();
		p = p->next;
	}
}

Comportamento::Comportamento(float vita, const char nomeFile[], float cord_x, float cord_y, float larghezza_e, float altezza_e, float angolo_rotazione) {
	entita_.setPosition(cord_x, cord_y); // posizione dell'oggetto
	entita_.setSize(sf::Vector2f(larghezza_e, altezza_e)); // dimensione dell'oggetto
	entita_.setRotation(angolo_rotazione); // angolo di rotazione dell'oggetto
	entita_.setFillColor(sf::Color::White); // colore dell'oggetto
	entita_.setOutlineColor(sf::Color::White);
	entita_.setOutlineThickness(1);

	texture_.loadFromFile(nomeFile); // texture dell'oggetto
	entita_.setTexture(&texture_); // impostata la texture
}
Comportamento::Comportamento() : Comportamento(50, "Texture/default.png", 200, 200, 25, 25, 0) {}

sf::Vector2f Comportamento::getPosizione()
{
	return entita_.getPosition();
}

void Comportamento::setPosizione(sf::Vector2f pos)
{
	entita_.setPosition(pos);
}

sf::Vector2f Comportamento::getDimensione()
{
	return entita_.getSize();
}

float Comportamento::getRotazione()
{
	return entita_.getRotation();
}

void Comportamento::setRotazione(float rot)
{
	entita_.setRotation(rot);
}

sf::FloatRect Comportamento::getBordi()
{
	return entita_.getGlobalBounds();
}

void Comportamento::spara(float angolo)
{
	proiettile_ptr p = new ProiettileNode;
	p->proiettile = new Proiettile(sf::Vector2f(5.f, 5.f), entita_.getPosition(), angolo, .6f); //crea una nuovo proiettile e lo mette in cima alla lista
	p->next = this->proiettili_;
	proiettili_ = p;
}

void Comportamento::eliminaProiettile(proiettile_ptr p)
{
	if (p->next != NULL) {
		proiettile_ptr tmp = p->next;
		p->proiettile = p->next->proiettile;
		p->next = p->next->next;
		delete tmp;
	}
	else
		delete p;
}