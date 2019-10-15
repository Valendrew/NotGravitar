#ifndef SUPERFICIE_PIANETA_H
#define SUPERFICIE_PIANETA_H

// includes
#include "bunker.h"
#include "bunker_stronger.h"
#include "oggetto.h"

// Pi greco
const double PI = 3.14159265;
// numero di linee
const int NUMERO_DI_LINEE = 18;

class SuperficiePianeta : public sf::Drawable {
protected:	
	// larghezza e altezza della finestra
	int larghezza_finestra_;
	int altezza_finestra_;
	int altezza_massima_; // altezza massima di generazione della superficie
	int altezza_minima_;
	oggetto *benzina_;

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

	struct BunkerStrongerNode {
		BunkerStronger *bunker_item;
		BunkerStrongerNode *next;
	};
	// typedef del puntatore del BunkerNode
	typedef BunkerStrongerNode* bunker_stronger_ptr;

	bunker_ptr bunker_;
	bunker_stronger_ptr bunker_stronger_;
	bool bunker_presenti_[NUMERO_DI_LINEE];

	void generaBunker();
	void generaBenzina();
	bool controllaBunkerVicinanze(int posizione);
	void aggiungiBunker(int index, bool bunker_stronger_);
	void inserisciNodoBunker(sf::Vector2f coordinate, float angolo);
	void inserisciNodoBunkerStronger(sf::Vector2f coordinate, float angolo);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:	
	
	SuperficiePianeta(unsigned int larghezza_finestra, unsigned altezza_finestra, sf::Vector2f primo_punto, sf::Vector2f ultimo_punto);
	SuperficiePianeta(unsigned int larghezza_finestra, unsigned int altezza_finestra);
	SuperficiePianeta();

	sf::Vector2f getFirstVertex();
	sf::Vector2f getLastVertex();

	proiettile_ptr getProiettili();

	bool controlloCollisioneSuperficie(sf::Vector2f pos);
	void controlloProiettili(proiettile_ptr lista_proiettili);
	int getNumeroBunker();
};
#endif // !SUPERFICIE_PIANETA_H
