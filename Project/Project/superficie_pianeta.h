#ifndef SUPERFICIE_PIANETA_H
#define SUPERFICIE_PIANETA_H

// includes
#include <SFML/Graphics.hpp>
#include "bunker.h"

// lista dei Bunker presenti nel pianeta
struct BunkerNode {
	Bunker *bunker_item;
	BunkerNode *next;
};
// typedef del puntatore del BunkerNode
typedef BunkerNode* bunker_ptr;

// Pi greco
const double PI = 3.14159265;
// numero di linee
const int NUMERO_DI_LINEE = 16;

class SuperficiePianeta : public sf::Drawable {
private:	
	// larghezza e altezza della finestra
	int larghezza_finestra_;
	int altezza_finestra_;

	int altezza_massima_; // altezza massima di generazione della superficie
	sf::VertexArray linee_;
	sf::ConvexShape superficie_[NUMERO_DI_LINEE];
	void generaVertici();
	void generaSuperficie();

	bunker_ptr bunker_;
	bool bunker_presenti_[NUMERO_DI_LINEE];
	void generaBunker();
	bool controllaBunkerVicinanze(int posizione);
	void aggiungiBunker(int index);
	void inserisciNodoBunker(float puntiMedi[], float angolo, int grandezza);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:	
	SuperficiePianeta(unsigned int width, unsigned int height);
	SuperficiePianeta();
};
#endif // !SUPERFICIE_PIANETA_H
