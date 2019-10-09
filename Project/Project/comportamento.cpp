#include "comportamento.h"

void Comportamento::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(entita_);

	proiettile_ptr p = proiettili_;
	int i = 0;
	while (p != NULL)	// Aggiorna la li posizione della lista dei proiettili, forse da spostare in funzione a parte!!
	{
		target.draw((*p->proiettile).getProiettile());
		(*p->proiettile).muovi();
		p = p->next;
		//i++;
		//if (i >= 10 && p != NULL && p->next!=NULL) eliminaProiettile(p);
	}
}

Comportamento::Comportamento(unsigned int width, unsigned int height, float vita, const char nomeFile[], sf::Vector2f pos, sf::Vector2f size, float angolo_rotazione) : clock_() {
	larghezza_finestra = width;
	altezza_finestra = height;

	entita_.setPosition(pos); // posizione dell'oggetto
	entita_.setSize(size); // dimensione dell'oggetto
	entita_.setRotation(angolo_rotazione); // angolo di rotazione dell'oggetto
	entita_.setFillColor(sf::Color::White); // colore dell'oggetto

	//entita_.setOutlineColor(sf::Color::White);
	//entita_.setOutlineThickness(.5f);

	int i = 0;
	while (nomeFile[i] != '\0')
	{
		nomeFile_[i] = nomeFile[i];
		i++;
	}

	texture_.loadFromFile(nomeFile_); // texture dell'oggetto
	entita_.setTexture(&texture_); // impostata la texture
}
Comportamento::Comportamento() : Comportamento(1280, 720, 50, "Texture/default.png", sf::Vector2f(), sf::Vector2f(), 0) {}

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

float Comportamento::getRotation()
{
	return entita_.getRotation();
}

void Comportamento::setRotation(float rot)
{
	entita_.setRotation(rot);
}

sf::FloatRect Comportamento::getGlobalBounds()
{
	return entita_.getGlobalBounds();
}

void Comportamento::spara(float angolo)
{
	if (clock_.getElapsedTime().asMilliseconds() > 800) {
		clock_.restart();

		proiettile_ptr p = new ProiettileNode;
		p->proiettile = new Proiettile(sf::Vector2f(5.f, 5.f), entita_.getPosition(), angolo, .6f); //crea una nuovo proiettile e lo mette in cima alla lista
		p->next = proiettili_;
		proiettili_ = p;
	}
}

void Comportamento::controlloProiettili(proiettile_ptr lista_proiettili)
{
	while (lista_proiettili != nullptr)
	{
		sf::FloatRect rect_proiettile = (*lista_proiettili->proiettile).getGlobalBounds();

		if (entita_.getGlobalBounds().intersects(rect_proiettile)) {
			(*lista_proiettili->proiettile).setColor(sf::Color::Red);
		}
		lista_proiettili = lista_proiettili->next;
	}
}

void Comportamento::eliminaProiettile(proiettile_ptr p)
{
	proiettile_ptr i = proiettili_;
	if (i != NULL && p != proiettili_) {
		while (i->next != NULL) {
			if (i->next == p) {
				i->next = p->next;
				delete p;
			}
			if (i->next != NULL)	i = i->next;
		}
	}
	if (p == proiettili_) {
		proiettili_ = proiettili_->next;
		delete p;
	}
}