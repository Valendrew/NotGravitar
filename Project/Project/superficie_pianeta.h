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

// numero di linee
const int NUMERO_DI_LINEE = 20;

class SuperficiePianeta : public sf::Drawable {
private:	
	
	int altezza_massima_;
	int larghezza_finestra_;
	int altezza_finestra_;
	bool bunker_presenti_[NUMERO_DI_LINEE];
	sf::VertexArray linee_;
	bunker_ptr bunker_;

	void generaVertici();
	void generaBunker();
	void aggiungiBunker(int index);
	void inserisciNodoBunker(float puntiMedi[], float angolo);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:	
	SuperficiePianeta(unsigned int width, unsigned int height);
	SuperficiePianeta();
};
#endif // !SUPERFICIE_PIANETA_H
