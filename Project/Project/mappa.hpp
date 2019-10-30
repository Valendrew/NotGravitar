#ifndef MAPPA_H
#define MAPPA_H

#include "universo.hpp";

class Mappa : public sf::Drawable, public sf::Transformable  {
protected:

	struct coordinate {
		int x;
		int y;
	};

	sf::Sprite sfondo_;
	sf::Texture texture_;
	int larghezza_finestra_;
	int altezza_finestra_;
	bool stato_attacco_;
	struct nodoMappa {
		Universo *universo;
		coordinate posizione;
		nodoMappa *next;
	};

	typedef nodoMappa *listaUniversi;

	listaUniversi list_universi_;
	listaUniversi posizione_attuale_; //puntatore  dove si trova l'astronave
	listaUniversi universo_di_gioco_;  //puntatore all'universo dove attualmente si devono distruggere i pianeti

	listaUniversi aggiungiUniverso(int x, int y); //addUniveso aggiunge un universo con coordinate x,y alla lista di universi
	
	//findUniversi cerca un universo con coordinate x,y all'interno della lista e lo resistuisce (ritorna NULL se non lo trova)
	listaUniversi cercaUniverso(int x, int y);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Mappa(int larghezza_finestra, int altezza_finestra);
	Mappa();

	int controlloPassaggioSuperficie(sf::Vector2f pos);
	bool controlloCollisioneSuperficie(sf::Vector2f pos);

	void uscitaPianeta();
	/*spostamento gestisce lo spostamento della navicella, modificando il puntatore posizioneAttuale ed eventualmente crea nuovi universi
	adiacenti a quello attuale */
	bool spostamentoUniverso(int direzione);
	bool ricercaPianeta(sf::Vector2f posizione);

	proiettile_ptr getProiettili();
	int controlloProiettili(proiettile_ptr lista_proiettili);

	Tipologia controlloRaggio(sf::ConvexShape raggio);

	bool aggiornaPunteggioBunker();
	bool aggiornaPunteggioPianeta();
	bool aggiornaPunteggioUniverso();
	void restart(int width_, int height_);
};

#endif