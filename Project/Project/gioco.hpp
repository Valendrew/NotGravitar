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
	Nave nave_;
	Mappa mappa_;
	bool nave_movimento;
	bool nave_rotazioneL;
	bool nave_rotazioneR;
	bool nave_spara;

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
	char stato_;
	void inserisciEvento(char stato_, char tipo[], sf::Int32 time);
	eventi_ptr eliminaEvento();
	void gestioneEventi(sf::Int32 time);
	void aggiornaEvento(eventi_ptr evento);

	void processaEventi();
	void gestisciMovimentoNave(sf::Keyboard::Key key, bool isPressed);
	void update();
	void render();
public:
	Gioco();
	void avviaGioco();
};
#endif // !GIOCO_H
