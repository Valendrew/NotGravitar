#include "gioco.hpp"
#include <iostream>
#include <stdlib.h>

void Gioco::inserisciEvento(char stato_, char tipo[], sf::Int32 time)
{
	if (eventi_H == nullptr) {
		eventi_H = new Eventi;
		eventi_H->time = time;
		eventi_H->e.stato = stato_;
	
		int i = 0;
		while (tipo[i] != '\0' && i < 100) {
			eventi_H->e.tipo[i] = tipo[i];
			i++;
		}

		eventi_H->prev = nullptr;
		eventi_H->next = nullptr;

		eventi_T = eventi_H;
	}
	else {
		eventi_ptr tmp_e = new Eventi;
		tmp_e->time = time;
		tmp_e->e.stato = stato_;

		int i = 0;
		while (tipo[i] != '\0' && i < 100) {
			tmp_e->e.tipo[i] = tipo[i];
			i++;
		}

		tmp_e->next = eventi_H;
		tmp_e->prev = nullptr;
		eventi_H->prev = tmp_e;
		eventi_H = tmp_e;
		//delete tmp_e;
	}
}

Gioco::eventi_ptr Gioco::eliminaEvento()
{
	if (eventi_T != nullptr) {
		eventi_ptr e = eventi_T;
		eventi_T = eventi_T->prev;
		return e;
	}
	else {
		return nullptr;
	}
}

void Gioco::aggiornaEvento(eventi_ptr evento)
{
	switch (evento->e.stato)
	{
	default:
		break;
	}
}

void Gioco::processaEventi()
{
	sf::Event event;
	while (window_.pollEvent(event)) {

		switch (event.type) {
		case sf::Event::Closed: window_.close();
			break;
		case sf::Event::KeyPressed: {
			gestisciMovimentoNave(event.key.code, true);
		}
			break;
		case sf::Event::KeyReleased:
			gestisciMovimentoNave(event.key.code, false);
			break;

		case sf::Event::MouseMoved: {

			sf::Vector2i v;
			v.x = sf::Mouse::getPosition(window_).x;
			v.y = sf::Mouse::getPosition(window_).y;
			gestisciMouse(v);
		}
			break;
		case sf::Event::MouseButtonPressed:
			mouseClick(sf::Mouse::Button::Left);
			break;
		}
	}
}

void Gioco::mouseClick(sf::Mouse::Button b) {
	
	sf::Vector2i v;
	v.x = sf::Mouse::getPosition(window_).x;
	v.y = sf::Mouse::getPosition(window_).y;
	int gestioneMouse = gestisciMouse(v);
	if (b == sf::Mouse::Button::Left && gestioneMouse == 1) {
		window_.close();
		schermata_scritte = false;
	}
	else if (b == sf::Mouse::Button::Left && gestioneMouse == 0) {

		std::string app = start_.getString();
		//compare torna 0 se le due stringhe sono uguali
		if (!app.compare("RESTART")) {
			restart_ = true;
			window_.close();
		}
		else if (!app.compare("START")) {
			stato_ = UNIVERSO;
		}
		else if (!app.compare("RESUME")) {
			stato_ = salva_stato;
		}
		schermata_scritte = false;
	}
	else if (gestioneMouse == 2) { 
		stato_ = PAUSA;
	}
	
	
}

int Gioco::gestisciMouse(sf::Vector2i v) {

	int pulsantePremuto = -1;

	/*Grazie a questo booleano posso verificare che l'astronave non stia compiando azioni. Senza di esso se tengo premuto un pulsante di movimento
	mentre premo pausa, l'astronave continuerà comunque a muoversi*/
	bool nave_ferma = !(nave_movimento || nave_rotazioneL || nave_rotazioneR || nave_spara);

	if (schermata_scritte) {
		float start_x = start_.getPosition().x;
		float start_y = start_.getPosition().y;
		float exit_x = exit_.getPosition().x;
		float exit_y = exit_.getPosition().y;
		if (v.x >= start_x && v.x <= start_x + start_.getGlobalBounds().width && v.y >= start_y && v.y <= start_y + start_.getGlobalBounds().height) {
			start_.setCharacterSize(60);
			pulsantePremuto = 0;
		}
		else {
			start_.setCharacterSize(55);
			if (v.x >= exit_x && v.x <= exit_x + exit_.getGlobalBounds().width && v.y >= exit_y && v.y <= exit_y + exit_.getGlobalBounds().height) {
				exit_.setCharacterSize(60);
				pulsantePremuto = 1;
			}
			else exit_.setCharacterSize(55);
		}
		start_.setPosition(LARGHEZZA / 2 - start_.getGlobalBounds().width / 2, ALTEZZA / 2);
		exit_.setPosition(LARGHEZZA / 2 - exit_.getGlobalBounds().width / 2, ALTEZZA / 2 + 100);
	}
	else {
		float pausa_x = pausa_.getPosition().x;
		float pausa_y = pausa_.getPosition().y;
		if (v.x >= pausa_x && v.x <= pausa_x + pausa_.getSize().x && v.y >= pausa_y && v.y <= pausa_y + pausa_.getSize().y && nave_ferma) {
			pulsantePremuto = 2;
			pausa_.setFillColor(sf::Color::Color(255, 255, 255, 255));
		}
		else 
			pausa_.setFillColor(sf::Color::Color(255, 255, 255, 160));
	}
	return pulsantePremuto;
	 
}

void Gioco::gestisciMovimentoNave(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W) {
		nave_movimento = isPressed;
	}
	else if (key == sf::Keyboard::A) {
		nave_rotazioneL = isPressed;
	}
	else if (key == sf::Keyboard::D) {
		nave_rotazioneR = isPressed;
	}
	else if (key == sf::Keyboard::Space) {
		nave_spara = isPressed;
	}
	else if (key == sf::Keyboard::G) {
		debug = isPressed;
	}
}

void Gioco::movimentoNavicella()
{
	if (nave_movimento && !collisione_nave) {
		nave_.muovi(time_frame_);
	}
	if (nave_rotazioneL) {
		nave_.ruotaL();
	}
	if (nave_rotazioneR) {
		nave_.ruotaR();
	}
	if (nave_spara) {
		//if (clock_.getElapsedTime().asMilliseconds() > 200) {
			nave_.spara();
			//clock_.restart();
		//}
	}
}

void Gioco::controlloPassaggioUniverso()
{
	sf::VertexArray punti = nave_.getPosizioneFrontale();

	int direzione = -1;
	for (int i = 0; i < punti.getVertexCount(); i++)
	{
		if (punti[i].position.x >= LARGHEZZA) direzione = 1;
		else if (punti[i].position.x <= 0) direzione = 3;
		else if (punti[i].position.y >= ALTEZZA) direzione = 2;
		else if (punti[i].position.y <= 0) direzione = 0;
	}

	if (direzione != -1) {
		if (mappa_.spostamento(direzione)) {

			//se sposto mi sposto in un altro sistema solare ed è nuovo (non ci sono mai stato) allora setto nuovo_universo a true cosi da aggiornare
			//correttamente il punteggio quando lo avro distrutto
			if (mappa_.getPosizioneAttuale().x == mappa_.getPosizioneDiGioco().x && mappa_.getPosizioneAttuale().y == mappa_.getPosizioneDiGioco().y)
				nuovo_universo = true;

			switch (direzione)
			{
			case 0: nave_.setPosition(sf::Vector2f(nave_.getPosition().x, ALTEZZA - nave_.getDimensione().y));
				break;
			case 1: nave_.setPosition(sf::Vector2f(nave_.getDimensione().x, nave_.getPosition().y));
				break;
			case 2: nave_.setPosition(sf::Vector2f(nave_.getPosition().x, nave_.getDimensione().y));
				break;
			case 3: nave_.setPosition(sf::Vector2f(LARGHEZZA - nave_.getDimensione().x, nave_.getPosition().y));
			default:
				break;
			}
		}
		else {
			float deg_angolo = nave_.getRotation();
			float angolo = nave_.getRotation() * PI / 180;
			float s_x = cos(angolo);
			float s_y = sin(angolo);

			float new_angolo;
			if (direzione == 1 || direzione == 3) {
				new_angolo = asin(s_y * -1) * 180 / PI;
				if (s_x < 0) {
					new_angolo = 180 - (new_angolo);
				}
			}
			else {
				new_angolo = acos(s_x * -1) * 180 / PI;
				if (s_y < 0) {
					new_angolo = 270 - (new_angolo - 90);
				}
				
			}
			nave_.setRotation(new_angolo);
		}
	}
}

void Gioco::controlloPassaggioPianeta()
{
	sf::VertexArray punti = nave_.getPosizioneFrontale();

	bool check = mappa_.ricercaPianeta(punti[0].position.x, punti[0].position.y);
	if (!check) check = mappa_.ricercaPianeta(punti[1].position.x, punti[1].position.y);

	if (check) {
		stato_ = PIANETA;
		posizione_entrata_pianeta_ = sf::Vector2f(punti[0].position.x - 50, punti[0].position.y - 50);
		
		nave_.setRotation(180);
		nave_.setPosition(sf::Vector2f(LARGHEZZA / 2, 40));
	}
}

void Gioco::controlloUscitaPianeta()
{
	sf::VertexArray punti = nave_.getPosizioneFrontale();

	int direzione = -1;
	bool cambia_stato = false;

	for (int i = 0; i < punti.getVertexCount(); i++)
	{
		if (punti[i].position.y <= 0) cambia_stato = true;
	}

	if (cambia_stato) {
		stato_ = UNIVERSO;

		nave_.setPosition(posizione_entrata_pianeta_);
		posizione_entrata_pianeta_ = sf::Vector2f(0, 0);

		mappa_.uscitaPianeta();
	}
}

void Gioco::controlloPassaggioSuperficie()
{
	int direzione = -1;
	sf::VertexArray bordo = nave_.getPosizioneFrontale();

	int i = 0;
	while (i < bordo.getVertexCount() && direzione == -1)
	{
		direzione = mappa_.controlloPassaggioSuperficie(bordo[i].position);
		i++;
	}

	if (direzione != -1) {
		if (direzione == 0) {
			nave_.setPosition(sf::Vector2f(LARGHEZZA - nave_.getDimensione().x, nave_.getPosition().y));
		}
		else {
			nave_.setPosition(sf::Vector2f(nave_.getDimensione().x, nave_.getPosition().y));
		}
	}
}

void Gioco::controlloCollisioneSuperficie()
{
	bool collisione_superficie = false;
	sf::VertexArray bordo = nave_.getPosizioneFrontale();

	if (mappa_.controlloCollisioneSuperficie(bordo[0].position)) {
		collisione_superficie = true;
	}
	else if (mappa_.controlloCollisioneSuperficie(bordo[1].position)) {
		collisione_superficie = true;
	}

	if (collisione_superficie) {
		float deg_angolo = nave_.getRotation();
		float angolo = nave_.getRotation() * PI / 180;
		float s_x = cos(angolo);
		float s_y = sin(angolo);

		float new_angolo = acos(s_x * -1) * 180 / PI;

		if (s_y < 0) {
			new_angolo = 270 - (new_angolo - 90);
		}

		nave_.setRotation(new_angolo);
	}
}

void Gioco::controlloCollisioneProiettili()
{
	nave_.controlloProiettili(mappa_.getProiettili());

	mappa_.controlloProiettili(nave_.getProiettili());
}

void Gioco::controlloDistruzioneBunker() {
	//quando un singolo bunker verra distrutto +10 punti, quando distruggo l'ultimo bunker +50 punti
}

void Gioco::controlloDistruzioneSistemaSolare() {
	if (mappa_.getUniversoDiGioco().distrutto() && nuovo_universo) {
		punteggio_ += 100;
		nuovo_universo = false;
	}
}

void Gioco::update()
{
	if (stato_ == UNIVERSO) {
		controlloDistruzioneSistemaSolare();
		controlloPassaggioUniverso();
		controlloPassaggioPianeta();
		movimentoNavicella();
	}
	else if (stato_ == PIANETA) {
		controlloUscitaPianeta();
		controlloPassaggioSuperficie();
		controlloCollisioneSuperficie();

		controlloCollisioneProiettili();
		controlloDistruzioneBunker();
		movimentoNavicella();
	}
	else if (stato_ == GAMEOVER) {
		schermata_scritte = true;
		start_.setString("RESTART");
		subtitle_.setString("GAME OVER");
		subtitle_.setPosition(LARGHEZZA / 2 - subtitle_.getGlobalBounds().width / 2, 140);
		start_.setPosition(LARGHEZZA / 2 - start_.getGlobalBounds().width / 2, ALTEZZA / 2);
		punteggio_text.setPosition(LARGHEZZA / 2 - punteggio_text.getGlobalBounds().width / 2, 210);
	}
	else if (stato_ == PAUSA) {
		schermata_scritte = true;
		start_.setString("RESUME");
		subtitle_.setString("");
		start_.setPosition(LARGHEZZA / 2 - start_.getGlobalBounds().width / 2, ALTEZZA / 2);
	}
	else if (stato_ == START) {
		schermata_scritte = true;
		start_.setString("START");
		subtitle_.setString("");
		start_.setPosition(LARGHEZZA / 2 - start_.getGlobalBounds().width / 2, ALTEZZA / 2);
	}
}

void Gioco::render()
{
	window_.clear(sf::Color::Black);
	if (stato_ == PIANETA || stato_ == UNIVERSO) {
		window_.draw(mappa_);
		window_.draw(nave_);
		window_.draw(pausa_);
		aggiornaPunteggio();
		window_.draw(punteggio_text);
	}
	else {
		window_.draw(titolo_);
		window_.draw(start_);
		window_.draw(exit_);
		window_.draw(subtitle_);
		if (stato_ == GAMEOVER)
			window_.draw(punteggio_text);
	}

	window_.display();
}

bool Gioco::restart() {
	return restart_;
}

void Gioco::aggiornaPunteggio() {
	char app[30] = "Punteggio: ";
	char app2[10];
	_itoa_s(punteggio_, app2, 10, 10);
	strcat_s(app, app2);
	punteggio_text.setString(app);
}

Gioco::Gioco() : 
	window_(sf::VideoMode(LARGHEZZA, ALTEZZA), "Not-Gravitar")
	, nave_(LARGHEZZA, ALTEZZA, 100, "Texture/ship3.png", sf::Vector2f(40, 40), sf::Vector2f(40, 40), 0, 220, 2.f, 10)
	, mappa_(LARGHEZZA, ALTEZZA)
	, clock_()
{
	pausa_.setSize(sf::Vector2f(61.8, 64.0));
	texture_.loadFromFile("Texture/pausa2.png");
	texture_.setSmooth(true);
	pausa_.setFillColor(sf::Color::Color(255,255,255,160));
	pausa_.setTexture(&texture_);
	
	pausa_.setPosition(LARGHEZZA - pausa_.getSize().x, 0);

	font_.loadFromFile("Font/edunline.ttf");
	exit_.setFont(font_);
	start_.setFont(font_);
	titolo_.setFont(font_);
	subtitle_.setFont(font_);
	punteggio_text.setFont(font_);

	titolo_.setString("NON GRAVITAR");
	exit_.setString("EXIT");

	punteggio_text.setFillColor(sf::Color::Blue);
	punteggio_text.setCharacterSize(32);
	punteggio_text.setLetterSpacing(1.5);
	punteggio_ = 0;
	aggiornaPunteggio();
	punteggio_text.setPosition(5,0);
	punteggio_text.setOutlineThickness(1);
	punteggio_text.setOutlineColor(sf::Color::Magenta);

	titolo_.setFillColor(sf::Color::Red);
	titolo_.setStyle(sf::Text::Bold);
	titolo_.setCharacterSize(120);
	titolo_.setOutlineThickness(4);
	titolo_.setLetterSpacing(1.5);
	titolo_.setPosition(LARGHEZZA / 2 - titolo_.getGlobalBounds().width/2, 10);
	titolo_.setOutlineColor(sf::Color::Yellow);

	subtitle_.setFillColor(sf::Color::Red);
	subtitle_.setCharacterSize(60);
	subtitle_.setLetterSpacing(1.5);

	start_.setFillColor(sf::Color::Green);
	start_.setCharacterSize(55);
	start_.setLetterSpacing(1.5); 

	exit_.setFillColor(sf::Color::Magenta);
	exit_.setCharacterSize(55);
	exit_.setLetterSpacing(1.5);
	exit_.setPosition(LARGHEZZA / 2 - exit_.getGlobalBounds().width / 2, ALTEZZA / 2 + 100);
	
	
	nuovo_universo = true;
	restart_ = false;
	schermata_scritte = false; //usato nella class render

	time_frame_ = sf::seconds(1.f / 144.f);
	nave_movimento = false;
	nave_rotazioneL = false;
	nave_rotazioneR = false;
	nave_spara = false;
	collisione_nave = false;
	posizione_entrata_pianeta_ = sf::Vector2f(0, 0);

	//stato_ = START;
	stato_ = UNIVERSO;

	eventi_H = nullptr;
	eventi_T = nullptr;

	debug = false;
}

void Gioco::avviaGioco()
{
	sf::Clock refresh_;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (window_.isOpen()) {
			processaEventi();

			timeSinceLastUpdate += refresh_.restart();
			if (timeSinceLastUpdate > time_frame_) {
				timeSinceLastUpdate -= time_frame_;
				//processaEventi();
				update();
			}
			
			render();
	}
}
