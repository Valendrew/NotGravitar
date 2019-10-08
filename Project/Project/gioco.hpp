#ifndef GIOCO_H
#define GIOCO_H

#include <SFML\Graphics.hpp>
#include "mappa.hpp"
#include "nave.hpp"
#include "Testo.h"

const int LARGHEZZA = 1280;
const int ALTEZZA = 720;


class Gioco {
private: 
	sf::RectangleShape pausa_;
	sf::Texture texture_;
	sf::RenderWindow window_;
	sf::Clock clock_;
	Testo exit_;
	Testo start_;
	Testo titolo_;
	Testo subtitle_;
	Testo punteggio_text;

	Nave nave_;
	Mappa mappa_;
	bool nave_movimento;
	bool nave_rotazioneL;
	bool nave_rotazioneR;
	bool nave_spara;
	bool debug;
	bool collisione_nave;
	bool nuovo_universo;

	int punteggio_;
	sf::Vector2f posizione_entrata_pianeta_;

	struct Evento {
		char stato;
		char tipo[100];
	};

	struct Eventi {
		Evento e;
		sf::Int32 time;
		Eventi* prev;
		Eventi* next;
	};
	typedef Eventi* eventi_ptr;

	eventi_ptr eventi_H;
	eventi_ptr eventi_T;

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

	void inserisciEvento(char stato_, char tipo[], sf::Int32 time);
	eventi_ptr eliminaEvento();
	void aggiornaEvento(eventi_ptr evento);

	void processaEventi();
	void gestisciMovimentoNave(sf::Keyboard::Key key, bool isPressed);
	void movimentoNavicella();
	void controlloPassaggioUniverso();
	void controlloPassaggioPianeta();
	void controlloUscitaPianeta();
	void controlloCollisioneSuperficie();
	void controlloCollisioneProiettili();
	void update();
	void render();
	int gestisciMouse(sf::Vector2i v);
	void mouseClick(sf::Mouse::Button b);
	void controlloDistruzioneBunker();
	void controlloDistruzioneSistemaSolare();
	void aggiornaPunteggio();
public:
	Gioco();
	void avviaGioco();
};
#endif // !GIOCO_H
