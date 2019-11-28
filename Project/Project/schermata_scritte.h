#ifndef SCHERMATA_SCRITTE_H
#define SCHERMATA_SCRITTE_H

#include <SFML\Graphics.hpp>
/*La classe serve a gestire le scritte presenti nel gioco*/
class SchermataScritte {
private:

	sf::Font font_;
	sf::Text exit_;
	sf::Text start_;
	sf::Text titolo_;
	sf::Text subtitle_;
	sf::Text punteggio_text_;
	sf::Text vita_text_;
	sf::Text carburante_text_;
	int LARGHEZZA_;
	int ALTEZZA_;
public:
	SchermataScritte(int LARGHEZZA, int ALTEZZA);
	void aggiornaTesto(const char stringa[], float valore);
	void setGameOver();
	void setPausa();
	void setStart();
	void setPunteggio();
	sf::Text getExit();
	sf::Text getStart();
	sf::Text getTitolo();
	sf::Text getSubtitle();
	sf::Text getPunteggio();
	sf::Text getVita();
	sf::Text getCarburante();
	int gestioneMouse(sf::Vector2i pos);
	

};

#endif