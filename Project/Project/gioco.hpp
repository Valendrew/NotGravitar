#ifndef GIOCO_H
#define GIOCO_H

#include <SFML\Graphics.hpp>
#include "mappa.hpp"
#include "nave.hpp"

const int LARGHEZZA = 1280;
const int ALTEZZA = 720;


class Gioco {
private: 
	sf::RenderWindow window_;
	sf::Clock clock_;
	sf::Font font_;
	sf::Text exit_;
	sf::Text start_;
	sf::Text titolo_;
	sf::Text subtitle_;
	Nave nave_;
	Mappa mappa_;
	bool game_over;
	bool nave_movimento;
	bool nave_rotazioneL;
	bool nave_rotazioneR;
	bool nave_spara;
	bool debug;
	bool collisione_nave;
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
		GAMEOVER
	};
	Stato stato_;

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
	bool gestisciMouse(sf::Vector2i v);
	void mouseClick(sf::Mouse::Button b);
public:
	Gioco();
	void avviaGioco();
};
#endif // !GIOCO_H
