#ifndef SCHERMATA_SCRITTE_H
#define SCHERMATA_SCRITTE_H

#include <SFML\Graphics.hpp>
#include "Testo.h";

class schermata_scritte {
private:
	Testo exit_;
	Testo start_;
	Testo titolo_;
	Testo subtitle_;
	Testo punteggio_text_;
	Testo vita_text_;
	Testo carburante_text_;
	int LARGHEZZA_;
	int ALTEZZA_;

public:
	schermata_scritte(int LARGHEZZA, int ALTEZZA);
	void aggiornaTesto(const char stringa[], float valore);
	void SetGameOver();
	void SetPausa();
	
	Testo getExit();
	Testo getStart();
	Testo getTitolo();
	Testo getSubtitle();
	Testo getPunteggio();
	Testo getVita();
	Testo getCarburante();
	int gestioneMouse(sf::Vector2i pos);
	void setStart();
	void setPunteggio();

};

#endif