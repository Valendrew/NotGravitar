#include "oggetto.h"


Oggetto::Oggetto(const char tipo[], const char nomeFile[],sf::Vector2f pos, float angolo_rotazione, sf::Vector2f size)
{
	tipologia tipo_oggetto;

	
	if (strcmp(tipo, "BENZINA_BEST") == 0)
		tipo_oggetto = BENZINA_BEST;
	else if (strcmp(tipo, "BENZINA") == 0)
		tipo_oggetto = BENZINA;
	else
		tipo_oggetto = CUORE;
	
	tipo_ = tipo_oggetto;
	capacita_ = tipo_oggetto;

	texture_.loadFromFile(nomeFile);
	entita_.setTexture(&texture_);
	entita_.setPosition(pos);
	entita_.setRotation(angolo_rotazione);
	entita_.setSize(size);

	entita_.setOrigin(0, 0 + size.y);
}

Oggetto::Oggetto() {
	tipo_ = BENZINA_BEST;
	capacita_ = 10;
}

void Oggetto::copiaStringa(char stringa[], int lunghezza, char stringa_da_copiare[])
{
	int i = 0;
	while (stringa_da_copiare[i] != '\0')
	{
		stringa[i] = stringa_da_copiare[i];
		i++;
	}
	stringa[i] = '\0';
}

void Oggetto::getTipologia(char tipologia_[])
{
	
	if (tipo_ == CUORE) {
		char stringa_oggetto[] = "CUORE";
		copiaStringa(tipologia_, 50, stringa_oggetto);
	}
	else if (tipo_ == BENZINA) {
		char stringa_oggetto[] = "BENZINA";
		copiaStringa(tipologia_, 50, stringa_oggetto);
	}
	else if (tipo_ == BENZINA_BEST) {
		char stringa_oggetto[] = "BENZINA_BEST";
		copiaStringa(tipologia_, 50, stringa_oggetto);
	}
		
}

float Oggetto::getCapacita()
{
	return capacita_;
}

sf::Vector2f Oggetto::getPosition()
{
	return entita_.getPosition();
}

void Oggetto::draw(sf::RenderTarget & target, sf::RenderStates states) const {

		target.draw(entita_);
}