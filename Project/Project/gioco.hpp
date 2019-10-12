#ifndef GIOCO_H
#define GIOCO_H

#include <SFML\Graphics.hpp>
#include "mappa.hpp"
#include "nave.hpp"
#include "Testo.h"

const int LARGHEZZA = 1280;
const int ALTEZZA = 720;

class Gioco {
protected: 
	sf::RenderWindow window_;

	sf::Time time_frame_;
	sf::Clock clock_;

	sf::RectangleShape pausa_;
	sf::Texture texture_;

	Testo exit_;
	Testo start_;
	Testo titolo_;
	Testo subtitle_;
	Testo punteggio_text;
	Testo vita_text;
	Testo carburante_text;

	Nave nave_;
	Mappa mappa_;
	bool nave_movimento;
	bool nave_rotazioneL;
	bool nave_rotazioneR;
	bool nave_spara;
	bool collisione_nave;

	int punteggio_;
	sf::Vector2f posizione_entrata_pianeta_;

	enum Stato
	{
		UNIVERSO,
		PIANETA,
		GAMEOVER,
		START,
		PAUSA
	};
	Stato stato_;
	Stato salva_stato;//serve per la pausa, cosi se ero nel pianeta ci sono di nuovo e se ero nell'universo ci sono di nuovo

	void processaEventi();
	void gestisciMovimentoNave(sf::Keyboard::Key key, bool isPressed);
	void movimentoNavicella();
	void controlloSparo();
	void controlloPassaggioUniverso();
	void controlloPassaggioPianeta();
	void controlloUscitaPianeta();
	void controlloPassaggioSuperficie();
	void controlloCollisioneSuperficie();
	void controlloCollisioneProiettili();
	bool debug;
	void update();
	void render();
	int gestisciMouse(sf::Vector2i v);
	void mouseClick(sf::Mouse::Button b);
	void aggiornaTestoNumeri(const char stringa[], int valore, Testo &t);
	void controlloAggiornamentoPunteggio();
public:
	Gioco();
	void avviaGioco();
};
#endif // !GIOCO_H
