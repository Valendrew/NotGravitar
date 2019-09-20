#ifndef GIOCO_H
#define GIOCO_H

#include <SFML\Graphics.hpp>
#include "mappa.hpp"
#include "nave.hpp"

const int LARGHEZZA = 1280;
const int ALTEZZA = 720;


class Gioco {
private: 
	struct Eventi {
		char stato;
		char tipo[100];
		Eventi* next;
	};
	typedef Eventi* eventi_ptr;

	eventi_ptr eventi_H;
	eventi_ptr eventi_T;
	static void gestioneEventi(Nave nave, Mappa mappa);
public:
	Gioco();
	static void avviaGioco();
};
#endif // !GIOCO_H
