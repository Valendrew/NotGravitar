#ifndef SUPERFICIE_PIANETA_H
#define SUPERFICIE_PIANETA_H

// includes
#include "bunker.h"

// Pi greco
const double PI = 3.14159265;
// numero di linee
const int NUMERO_DI_LINEE = 20;

class SuperficiePianeta : public sf::Drawable {
private:	
	// larghezza e altezza della finestra
	int larghezza_finestra_;
	int altezza_finestra_;

	int altezza_massima_; // altezza massima di generazione della superficie

	sf::VertexArray vertici_superficie_;
	sf::ConvexShape superficie_[NUMERO_DI_LINEE];
	void generaVertici(sf::Vector2f first_point, sf::Vector2f last_point);
	void generaSuperficie();

	// lista dei Bunker presenti nel pianeta
	struct BunkerNode {
		Bunker *bunker_item;
		BunkerNode *next;
	};
	// typedef del puntatore del BunkerNode
	typedef BunkerNode* bunker_ptr;

	bunker_ptr bunker_;
	bool bunker_presenti_[NUMERO_DI_LINEE];
	void generaBunker();
	bool controllaBunkerVicinanze(int posizione);
	void aggiungiBunker(int index);
	void inserisciNodoBunker(sf::Vector2f coordinate, float angolo, sf::Vector2f grandezza);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:	
	SuperficiePianeta(unsigned int width, unsigned height, sf::Vector2f first_point, sf::Vector2f last_point);
	SuperficiePianeta(unsigned int width, unsigned int height);
	SuperficiePianeta();
	sf::Vector2f getLastVertex();
	sf::Vector2f getFirstVertex();
	proiettile_ptr getProiettili();
	bool controlloCollisioneSuperficie(sf::Vector2f pos);
};
#endif // !SUPERFICIE_PIANETA_H
