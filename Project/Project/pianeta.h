#ifndef PIANETA_H
#define PIANETA_H

// includes
#include "bunker.h"
#include "superficie_pianeta.h"

class Pianeta : public sf::Drawable, public sf::Transformable {
protected: 
	int larghezza_finestra;
	int altezza_finestra;
	int id_;
	sf::CircleShape shape_;

	struct SuperficieNode {
		SuperficiePianeta *superficie_item;
		SuperficieNode *prev;
		SuperficieNode *next;
	};
	// typedef del puntatore del BunkerNode
	typedef SuperficieNode* superficie_ptr;

	superficie_ptr superficie_head;
	superficie_ptr superficie_tail;
	superficie_ptr superficie_attuale_;

	int numero_superfici_;
	int bunker_precedenti;

	void generaSuperficie();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	int bunker_rimanenti();
public: 
	Pianeta(int id, float cord_x, float cord_y, unsigned int width, unsigned int height);
	int getRaggio();
	sf::Vector2f getPosizione();
	void cambiaColore();
	bool distrutto();
	bool distruzioneSingoloBunker();
	int controlloPassaggioSuperficie(sf::Vector2f pos);
	bool controlloCollisioneSuperficie(sf::Vector2f pos);
	proiettile_ptr getProiettili();
	void controlloProiettili(proiettile_ptr lista_proiettili);
	void drawSuperficie(sf::RenderTarget& target, sf::RenderStates states);
};
#endif // !PIANETA_H
