#ifndef PIANETA_H
#define PIANETA_H

// includes
#include "bunker.h"
#include "superficie_pianeta.h"

class Pianeta : public sf::Drawable, public sf::Transformable {
protected:
	enum TipologiaPianeta {
		ACQUA,
		FUOCO,
		ERBA
	};

	int larghezza_finestra_;
	int altezza_finestra_;
	int id_;
	bool distrutto_;
	int numero_bunker_precedenti;
	sf::CircleShape pianeta_;
	sf::Texture texture_;
	sf::Texture texture_distrutto_;
	TipologiaPianeta tipo_pianeta_;

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
	void isDistrutto();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public: 
	Pianeta(float raggio, int id, sf::Vector2f posizione, unsigned int larghezza_finestra, unsigned int altezza_finestra, const char tipologia[], const char texture[], const char texture_distrutto[]);
	Pianeta();
	float getRaggio();

	sf::Vector2f getPosition();
	sf::FloatRect getGlobalBounds();

	bool distruzioneSingoloBunker();
	
	bool getDistrutto();
	int controlloPassaggioSuperficie(sf::Vector2f posizione);
	bool controlloCollisioneSuperficie(sf::Vector2f posizione);
	Tipologia controlloRaggio(sf::ConvexShape raggio);
	void resetProiettiliBunker();
	proiettile_ptr getProiettili();
	int controlloProiettili(proiettile_ptr lista_proiettili);
	void drawSuperficie(sf::RenderTarget& target, sf::RenderStates states);
	
};
#endif // !PIANETA_H
