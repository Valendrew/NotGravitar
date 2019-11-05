#ifndef MAPPA_H
#define MAPPA_H

#include "universo.hpp";

class Mappa : public sf::Drawable, public sf::Transformable  {
protected:

	/*Le coordinate sono utilizzare per mappare i vari sistemi solari nell'universo come in un piano cartesiano.*/
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
	listaUniversi sistema_solare_di_gioco_;  //puntatore all'universo dove attualmente si devono distruggere i pianeti

	listaUniversi aggiungiSistemaSolare(int x, int y); //aggiungiUniverso aggiunge un universo con coordinate (x, y) alla lista di universi
	
	//cercaSistemaSolore cerca un universo con coordinate x,y all'interno della lista e lo resistuisce (ritorna NULL se non lo trova)
	listaUniversi cercaSistemaSolare(int x, int y);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Mappa(int larghezza_finestra, int altezza_finestra);
	Mappa();

	int controlloPassaggioSuperficie(sf::Vector2f pos);
	bool controlloCollisioneSuperficie(sf::Vector2f pos);

	void uscitaPianeta();
	/*spostamento gestisce lo spostamento della navicella, modificando il puntatore posizioneAttuale ed eventualmente crea un nuovo sistema solare
	adiacenti a quello attuale */
	bool spostamentoSistemaSolare(int direzione);
	bool ricercaPianeta(sf::Vector2f posizione);

	proiettile_ptr getProiettili();
	int controlloProiettili(proiettile_ptr lista_proiettili);

	Tipologia controlloRaggio(sf::ConvexShape raggio);

	bool aggiornaPunteggioBunker();
	bool aggiornaPunteggioPianeta();
	bool aggiornaPunteggioSistemaSolare();
	void restart(int width_, int height_);
};

#endif