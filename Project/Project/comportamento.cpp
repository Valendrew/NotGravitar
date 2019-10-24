#include "comportamento.h"

void Comportamento::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	//target.draw(entita_);
}

Comportamento::Comportamento(unsigned int larghezza_finestra, unsigned int altezza_finestra, float vita, float danno, 
	const char nomeFile[], const char nomeFileDistrutto[], sf::Vector2f posizione, sf::Vector2f dimensione, float angolo_rotazione) :
	clock_() 
{
	larghezza_finestra_ = larghezza_finestra;
	altezza_finestra_ = altezza_finestra;

	entita_.setPosition(posizione); // posizione dell'oggetto
	entita_.setSize(dimensione); // dimensione dell'oggetto
	entita_.setRotation(angolo_rotazione); // angolo di rotazione dell'oggetto
	entita_.setFillColor(sf::Color::White); // colore dell'oggetto

	texture_.loadFromFile(nomeFile); // texture dell'oggetto
	texture_distrutto_.loadFromFile(nomeFileDistrutto);

	entita_.setTexture(&texture_); // impostata la texture

	vita_ = vita;
	danno_ = danno;
	distrutto_ = false;

	proiettili_ = nullptr;

	
	int i = 0;
	while (nomeFileDistrutto[i] != '\0')
	{
		nomeFileDistrutto_[i] = nomeFileDistrutto[i];
		i++;
	}
	i = 0;
	while (nomeFile[i] != '\0')
	{
		nomeFile_[i] = nomeFile[i];
		i++;
	}
}

Comportamento::Comportamento() : Comportamento(1280, 720, 50, 10, 
	"Texture/default.png", "Texture/default_d.png", sf::Vector2f(), sf::Vector2f(), 0) {}

void Comportamento::restart(float vita, float cord_x, float cord_y, float angolo_rotazione, bool distrutto){
	vita_ = vita;
	entita_.setPosition(cord_x, cord_y);
	entita_.setRotation(angolo_rotazione);
	distrutto_ = distrutto;
}

sf::Vector2f Comportamento::getPosition()
{
	return entita_.getPosition();
}

void Comportamento::setPosition(sf::Vector2f pos)
{
	entita_.setPosition(pos);
}

sf::FloatRect Comportamento::getGlobalBounds()
{
	return entita_.getGlobalBounds();
}

sf::Vector2f Comportamento::getSize()
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

int Comportamento::controlloProiettili(proiettile_ptr lista_proiettili)
{
	int numerobunkerColpiti = 0;
	while (lista_proiettili != nullptr && !distrutto_)
	{
		sf::FloatRect rect_proiettile = (*lista_proiettili->proiettile).getGlobalBounds();

		if (entita_.getGlobalBounds().intersects(rect_proiettile)) {
			diminuisciVita((*lista_proiettili->proiettile).getDanno());
			numerobunkerColpiti++;
			(*lista_proiettili->proiettile).setDistrutto();
		}
		lista_proiettili = lista_proiettili->next;
	}
	return numerobunkerColpiti;
}

proiettile_ptr Comportamento::eliminaProiettile(proiettile_ptr p)
{
	proiettile_ptr i = proiettili_;
	if (i != NULL && p != proiettili_) {
		while (i->next != NULL) {
			if (i->next == p) {
				i->next = p->next;
				delete p;
			}
			if (i->next != NULL)	
				i = i->next;
		}
	}
	if (p == proiettili_) {
		proiettili_ = proiettili_->next;
		i = proiettili_;
		delete p;
	}

	return i;
}

void Comportamento::eliminaProiettiliBordo()
{
	proiettile_ptr tmp_proiettili = proiettili_;

	while (tmp_proiettili != nullptr)
	{
		sf::Vector2f pos_proiettile = (*tmp_proiettili->proiettile).getPosition();

		if (pos_proiettile.x > larghezza_finestra_) {
			tmp_proiettili = eliminaProiettile(tmp_proiettili);
		}
		else if (pos_proiettile.x < 0)
		{
			tmp_proiettili = eliminaProiettile(tmp_proiettili);
		}
		else if (pos_proiettile.y > altezza_finestra_) {
			tmp_proiettili = eliminaProiettile(tmp_proiettili);
		}
		else if (pos_proiettile.y < 0) {
			tmp_proiettili = eliminaProiettile(tmp_proiettili);
		}
		else tmp_proiettili = tmp_proiettili->next;
	}
}

void Comportamento::resetProiettili()
{
	proiettile_ptr del_ptr = proiettili_;

	while (del_ptr != nullptr)
	{
		proiettili_ = proiettili_->next;
		delete del_ptr;
		del_ptr = proiettili_;
	}
	proiettili_ = nullptr;
}

float Comportamento::getVita()
{
	return vita_;
}

bool Comportamento::getDistrutto()
{
	return distrutto_;
}

void Comportamento::setDistrutto()
{
	distrutto_ = true;
	entita_.setTexture(&texture_distrutto_); // impostata la texture
}

void Comportamento::diminuisciVita(float danno)
{
	if (vita_ > danno) {
		vita_ -= danno;
	}
	else {
		vita_ = 0;
		setDistrutto();
	}
}

void Comportamento::drawComportamento(sf::RenderTarget & target, sf::RenderStates states)
{
	target.draw(entita_);
	
	eliminaProiettiliBordo();

	proiettile_ptr p = proiettili_;
	while (p != NULL)	// Aggiorna la li posizione della lista dei proiettili, forse da spostare in funzione a parte!!
	{
		//target.draw((*p->proiettile).getProiettile());
		target.draw(*p->proiettile);
		(*p->proiettile).muovi();
		p = p->next;
	}
}
