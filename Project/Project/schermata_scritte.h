#ifndef SCHERMATA_SCRITTE_H
#define SCHERMATA_SCRITTE_H

#include <SFML\Graphics.hpp>
#include "Testo.h";
/*La classe serve a gestire le scritte presenti nel gioco*/
class SchermataScritte {
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
	SchermataScritte(int LARGHEZZA, int ALTEZZA);
	void aggiornaTesto(const char stringa[], float valore);
	void setGameOver();
	void setPausa();
	
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