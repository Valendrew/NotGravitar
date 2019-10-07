#include "gioco.hpp"

int main() {

	bool restart = false;
	do{   
		Gioco g;
		g.avviaGioco();
		restart = g.restart();
	} while (restart);
	return 0;
}