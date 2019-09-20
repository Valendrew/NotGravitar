#ifndef GIOCO_H
#define GIOCO_H

#include <SFML\Graphics.hpp>
#include "mappa.hpp"
#include "nave.hpp"

const int LARGHEZZA = 1280;
const int ALTEZZA = 720;

struct Eventi {
	char stato;
	char tipo[100];
	Eventi* next;
};
class Gioco {
private: 
	static void gestioneEventi(Nave nave, Mappa mappa);
public:
	static void avviaGioco();
};
#endif // !GIOCO_H
