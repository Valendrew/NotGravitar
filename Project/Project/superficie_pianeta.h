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
	bool distrutta_;
	int altezza_massima_; // altezza massima di generazione della superficie
	int altezza_minima_;
	Oggetto *oggetto_bonus;

	enum TipologiaOggetto{
		BUNKER_STRONGER,
		BUNKER,
		OGGETTO_BONUS
	};

	sf::VertexArray vertici_superficie_;
	sf::ConvexShape superficie_[NUMERO_DI_LINEE];
	sf::Color colore_superficie_;

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
	bool oggetti_presenti_[NUMERO_DI_LINEE];

	void generaBunker();
	bool controllaOggettiVicinanze(int posizione, int distanza);
	void aggiungiOggetto(int index, TipologiaOggetto tipoOggetto, sf::Vector2f dimensione);
	void inserisciNodoBunker(sf::Vector2f coordinate, float angolo, sf::Vector2f dimensione);
	void inserisciNodoBunkerStronger(sf::Vector2f coordinate, float angolo, sf::Vector2f dimensione);
	void inserisciOggettoBonus(sf::Vector2f coordinate, float angolo, sf::Vector2f dimensione);
	void generaOggettoBonus();
	void copiaStringa(char stringa[], int lunghezza, char stringa_da_copiare[]);
	bool intersezione(sf::Vector2f a1, sf::Vector2f b1, sf::Vector2f a2, sf::Vector2f b2);
	void isDistrutta();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:	
	
	SuperficiePianeta(unsigned int larghezza_finestra, unsigned altezza_finestra, sf::Vector2f primo_punto, sf::Vector2f ultimo_punto, sf::Color colore);
	SuperficiePianeta(unsigned int larghezza_finestra, unsigned int altezza_finestra, sf::Color colore);
	SuperficiePianeta();

	sf::Vector2f getFirstVertex();
	sf::Vector2f getLastVertex();

	proiettile_ptr getProiettili();
	void resetProiettiliBunker();

	sf::VertexArray getPosizioneLineaSuperficie(sf::Vector2f posizione);
	bool controlloCollisioneSuperficie(sf::Vector2f pos);
	int controlloProiettili(proiettile_ptr lista_proiettili);
	Tipologia controlloRaggio(sf::ConvexShape raggio);
	bool getDistrutta();
	int getNumeroBunker();
};
#endif // !SUPERFICIE_PIANETA_H
