#ifndef PIANETA_H
#define PIANETA_H

// includes
#include "bunker.h"
#include "superficie_pianeta.h"

class Pianeta : public sf::Drawable, public sf::Transformable {
protected: 
	int larghezza_finestra_;
	int altezza_finestra_;
	bool distrutto_;
	int id_;
	sf::CircleShape pianeta_;

	int numero_superfici_;
	int bunker_precedenti_;

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

	void distrutto();
	bool distruzioneSingoloBunker();
	bool isDistrutto();

	int controlloPassaggioSuperficie(sf::Vector2f posizione);
	bool controlloCollisioneSuperficie(sf::Vector2f posizione);
	sf::VertexArray getPosizioneLineaSuperficie(sf::Vector2f posizione);
	proiettile_ptr getProiettili();
	void controlloProiettili(proiettile_ptr lista_proiettili);
	void drawSuperficie(sf::RenderTarget& target, sf::RenderStates states);
};
#endif // !PIANETA_H
