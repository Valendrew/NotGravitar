#ifndef GIOCO_H
#define GIOCO_H

#include <SFML\Graphics.hpp>
#include "mappa.hpp"
#include "nave.hpp"
#include "schermata_scritte.h"

const int LARGHEZZA = 1280;
const int ALTEZZA = 720;

class Gioco {
protected: 
	sf::RenderWindow window_;

	sf::Time time_frame_;
	sf::Clock clock_;

	sf::RectangleShape pausa_;
	sf::Texture texture_;

	schermata_scritte schermataScritte;

	Nave nave_;
	Mappa mappa_;

	bool nave_movimento_;
	bool nave_rotazioneL_;
	bool nave_rotazioneR_;
	bool nave_spara_;
	bool nave_raggiotraente_;
	bool restart_;

	int punteggio_;
	sf::Vector2f posizione_entrata_pianeta_;

	enum Stato
	{
		UNIVERSO,
		PIANETA,
		GAMEOVER,
		START,
		PAUSA
	};
	Stato stato_;
	Stato salva_stato_;//serve per la pausa, cosi se ero nel pianeta ci sono di nuovo e se ero nell'universo ci sono di nuovo

	void processaEventi();
	void gestisciMovimentoNave(sf::Keyboard::Key key, bool isPressed);
	void movimentoNavicella();
	void controlloSparo();
	void controlloPassaggioUniverso();
	void controlloPassaggioPianeta();
	void controlloUscitaPianeta();
	void controlloPassaggioSuperficie();
	void controlloCollisioneSuperficie();
	void controlloCollisioneProiettili();
	void controlloCollisioneProiettiliSuperficie();

	void update();
	void render();
	int gestisciMouse();
	void mouseClick(sf::Mouse::Button b);
	void controlloAggiornamentoPunteggio();
	void controlloGameOver();
public:
	Gioco();
	void avviaGioco();
};
#endif // !GIOCO_H
