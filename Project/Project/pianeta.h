#ifndef PIANETA_H
#define PIANETA_H

// includes
#include "bunker.h"
#include "superficie_pianeta.h"

class Pianeta : public sf::Drawable, public sf::Transformable {
protected: 
	int larghezza_finestra_;
	int altezza_finestra_;
	int id_;
	int* numero_bunker_precedenti;
	sf::CircleShape pianeta_;

	bool* distrutto_;
	int numero_superfici_;

	struct SuperficieNode {
		SuperficiePianeta *superficie_item;
		SuperficieNode *prev;
		SuperficieNode *next;
	};
	// typedef del puntatore del BunkerNode
	typedef SuperficieNode* superficie_ptr;

	superficie_ptr superficie_head_;
	superficie_ptr superficie_tail_;
	superficie_ptr superficie_attuale_;

	void generaSuperficie();
	int bunkerRimanenti();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public: 
	Pianeta(int id, sf::Vector2f posizione, unsigned int larghezza_finestra, unsigned int altezza_finestra);
	Pianeta();
	float getRaggio();
	sf::Vector2f getPosizione();

	//void cambiaColore();
	bool distruzioneSingoloBunker();
	bool isDistrutto();
	bool getDistrutto();

	int controlloPassaggioSuperficie(sf::Vector2f posizione);
	bool controlloCollisioneSuperficie(sf::Vector2f posizione);
	void resetProiettiliBunker();
	proiettile_ptr getProiettili();
	void controlloProiettili(proiettile_ptr lista_proiettili);
	void drawSuperficie(sf::RenderTarget& target, sf::RenderStates states);
};
#endif // !PIANETA_H
