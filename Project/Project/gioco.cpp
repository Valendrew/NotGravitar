#include "gioco.hpp"
#include <stdlib.h>

void Gioco::processaEventi()
{
	sf::Event event;

	while (window_.pollEvent(event)) {

		switch (event.type) {
			case sf::Event::Closed: window_.close();
				break;
			case sf::Event::KeyPressed: 
				gestisciMovimentoNave(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				gestisciMovimentoNave(event.key.code, false);
				break;
			case sf::Event::MouseMoved: {
				sf::Vector2i posizioneMouse;
				posizioneMouse.x = sf::Mouse::getPosition(window_).x;
				posizioneMouse.y = sf::Mouse::getPosition(window_).y;
				gestisciMouse(posizioneMouse);
			} break;
			case sf::Event::MouseButtonPressed:
				mouseClick(sf::Mouse::Button::Left);
				break;
			}
	}
}

void Gioco::gestisciMovimentoNave(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W) {
		nave_movimento_ = isPressed;
	}
	else if (key == sf::Keyboard::A) {
		nave_rotazioneL_ = isPressed;
	}
	else if (key == sf::Keyboard::D) {
		nave_rotazioneR_ = isPressed;
	}
	else if (key == sf::Keyboard::Space) {
		nave_spara_ = isPressed;
	}
	else if (key == sf::Keyboard::Q) {
		nave_raggio_ = isPressed;
	}
}

void Gioco::movimentoNavicella()
{
	if (nave_movimento_) {
		nave_.muovi(time_frame_);
	}
	if (nave_rotazioneL_) {
		nave_.ruotaSinistra();
	}
	if (nave_rotazioneR_) {
		nave_.ruotaDestra();
	}
}

void Gioco::controlloSparo()
{
	if (nave_spara_) {
		nave_.spara();
	}
}

void Gioco::controlloRaggio()
{
	nave_.attivaRaggio(nave_raggio_);
}

void Gioco::controlloPassaggioUniverso()
{	
	int direzione = -1;

	sf::VertexArray punti = nave_.getPosizioneFrontale();

	int i = 0;
	while (i < punti.getVertexCount() && direzione == -1)
	{
		if (punti[i].position.x >= LARGHEZZA) direzione = 1;
		else if (punti[i].position.x <= 0) direzione = 3;
		else if (punti[i].position.y >= ALTEZZA) direzione = 2;
		else if (punti[i].position.y <= 0) direzione = 0;

		i++;
	}

	if (direzione != -1) {
		if (mappa_.spostamento(direzione)) {
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

	bool controllo_passaggio = mappa_.ricercaPianeta(punti[0].position.x, punti[0].position.y);
	if (!controllo_passaggio) controllo_passaggio = mappa_.ricercaPianeta(punti[1].position.x, punti[1].position.y);

	if (controllo_passaggio) {
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

	sf::VertexArray punti = nave_.getPosizioneFrontale();

	int i = 0;
	while (i < punti.getVertexCount() && direzione == -1)
	{
		direzione = mappa_.controlloPassaggioSuperficie(punti[i].position);
		i++;
	}

	if (direzione != -1) {
		if (direzione == 0) {
			nave_.setPosition(sf::Vector2f(LARGHEZZA - 2 * nave_.getDimensione().x, nave_.getPosition().y));
		}
		else {
			nave_.setPosition(sf::Vector2f(2 * nave_.getDimensione().x, nave_.getPosition().y));
		}
	}
}

void Gioco::controlloCollisioneSuperficie()
{
	bool collisione_superficie = false;

	sf::VertexArray punti = nave_.getPosizioneFrontale();

	int i = 0;
	while (i < punti.getVertexCount() && !collisione_superficie)
	{
		collisione_superficie = mappa_.controlloCollisioneSuperficie(punti[i].position);
		i++;
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

void Gioco::update()
{
	if (stato_ == UNIVERSO) {
		controlloPassaggioUniverso();
		controlloPassaggioPianeta();

		movimentoNavicella();
	}
	else if (stato_ == PIANETA) {
		controlloAggiornamentoPunteggio();
		controlloUscitaPianeta();

		controlloPassaggioSuperficie();
		controlloCollisioneSuperficie();
		controlloCollisioneProiettili();

		movimentoNavicella();
		controlloSparo();

		controlloRaggio();
	}
	else if (stato_ == GAMEOVER) {
		start_.setString("RESTART");
		subtitle_.setString("GAME OVER");
		subtitle_.setPosition(LARGHEZZA / 2 - subtitle_.getGlobalBounds().width / 2, 140);
		punteggio_text_.setPosition(LARGHEZZA / 2 - punteggio_text_.getGlobalBounds().width / 2, 210);
	}
	else if (stato_ == PAUSA) {
		start_.setString("RESUME");
	}
	else if (stato_ == START) {
		start_.setString("START");
	}
	if (stato_ == START || stato_ == PAUSA || stato_ == GAMEOVER) {
		start_.setPosition(LARGHEZZA / 2 - start_.getGlobalBounds().width / 2, ALTEZZA / 2);
	}
}

void Gioco::render()
{
	window_.clear(sf::Color::Black);

	if (stato_ == UNIVERSO || stato_ == PIANETA) {
		aggiornaTestoNumeri("VITA: ", nave_.getVita(), vita_text_);
		aggiornaTestoNumeri("CARBURANTE: ", nave_.getCarburante(), carburante_text_);

		window_.draw(mappa_);
		nave_.drawComportamento(window_, sf::RenderStates());

		window_.draw(pausa_);
		window_.draw(punteggio_text_);
		window_.draw(vita_text_);
		window_.draw(carburante_text_);
	}
	else {
		window_.draw(titolo_);
		window_.draw(start_);
		window_.draw(exit_);
		window_.draw(subtitle_);

		if (stato_ == GAMEOVER)
			window_.draw(punteggio_text_);
	}
	window_.display();
}

void Gioco::mouseClick(sf::Mouse::Button bottoneMouse) {

	sf::Vector2i posizioneMouse;
	posizioneMouse.x = sf::Mouse::getPosition(window_).x;
	posizioneMouse.y = sf::Mouse::getPosition(window_).y;

	int gestioneMouse = gestisciMouse(posizioneMouse);
	if (bottoneMouse == sf::Mouse::Button::Left && gestioneMouse == 1) {
		window_.close();
	}
	else if (bottoneMouse == sf::Mouse::Button::Left && gestioneMouse == 0) {

		std::string app = start_.getString();
		//compare torna 0 se le due stringhe sono uguali
		if (!app.compare("RESTART")) {
			mappa_.restart(LARGHEZZA, ALTEZZA);
			nave_.restart(100, LARGHEZZA / 2, ALTEZZA / 2, 0, 10);
			stato_ = UNIVERSO;
			punteggio_text_.setPosition(5, 0);
		}
		else if (!app.compare("START")) {
			stato_ = UNIVERSO;
		}
		else if (!app.compare("RESUME")) {
			stato_ = salva_stato_;
		}
		//Le due linee seguenti servono per ridimensionare subito lo start, altrimenti una volata premuta la pausa si visualizzerebbe "RESUME" a dimensione 60
		//invece che 55 per un istante
		start_.setCharacterSize(55);
		start_.setPosition(LARGHEZZA / 2 - start_.getGlobalBounds().width / 2, ALTEZZA / 2);

	}
	else if (gestioneMouse == 2) {
		salva_stato_ = stato_;
		stato_ = PAUSA;
	}
}

int Gioco::gestisciMouse(sf::Vector2i posizioneMouse) {

	int pulsantePremuto = -1;

	if (stato_ == GAMEOVER || stato_ == PAUSA || stato_ == START) {
		if (start_.getGlobalBounds().contains(posizioneMouse.x, posizioneMouse.y)) {
			start_.setCharacterSize(60);
			pulsantePremuto = 0;
		}
		else {
			start_.setCharacterSize(55);
			if (exit_.getGlobalBounds().contains(posizioneMouse.x, posizioneMouse.y)) {
				exit_.setCharacterSize(60);
				pulsantePremuto = 1;
			}
			else exit_.setCharacterSize(55);
		}
		start_.setPosition(LARGHEZZA / 2 - start_.getGlobalBounds().width / 2, ALTEZZA / 2);
		exit_.setPosition(LARGHEZZA / 2 - exit_.getGlobalBounds().width / 2, ALTEZZA / 2 + 100);
	}
	else {
		if (pausa_.getGlobalBounds().contains(posizioneMouse.x, posizioneMouse.y)) {
			pulsantePremuto = 2;
			pausa_.setFillColor(sf::Color::Color(255, 255, 255, 255));
		}
		else
			pausa_.setFillColor(sf::Color::Color(255, 255, 255, 160));
	}
	return pulsantePremuto;

}

void Gioco::aggiornaTestoNumeri(const char stringa[], int valore, Testo &t) {

	char valoreToString[10];
	char stringaCompleta[100];
	_itoa_s(valore, valoreToString, 10, 10);
	strcpy_s(stringaCompleta, stringa);
	strcat_s(stringaCompleta, valoreToString);
	t.setString(stringaCompleta);
}

void Gioco::controlloAggiornamentoPunteggio() {

	listaPianeti p_attuale = mappa_.getUniversoDiGioco().getPianetaAttuale();

	//Il controllo mappa_.isNuovoUniverso() serve per far aumentare il punteggio di 100 una sola volta per ugni sistema solare
	if (mappa_.getUniversoDiGioco().distrutto() && mappa_.isNuovoUniverso()) {
		punteggio_ += 100;
		mappa_.setVecchioUniverso();
	}
	else if ((*p_attuale->pianeta_).distrutto()) {
		punteggio_ += 50;
	}
	else if ((*p_attuale->pianeta_).distruzioneSingoloBunker()) {
		punteggio_ += 10;
	}

	aggiornaTestoNumeri("PUNTEGGIO: ", punteggio_, punteggio_text_);

}

Gioco::Gioco() :
	window_(sf::VideoMode(LARGHEZZA, ALTEZZA), "Not-Gravitar")
	, nave_(LARGHEZZA, ALTEZZA, 100, 10, "Texture/ship_3.png", "Texture/ship_3d.png",
		sf::Vector2f(40, 40), sf::Vector2f(60, 60), 0, 350, 2.f, 10)
	, mappa_(LARGHEZZA, ALTEZZA)
	, clock_()
	, punteggio_text_("PUNTEGGIO: 100",32, sf::Color::Blue, sf::Color::Magenta, 1.5, 1, sf::Vector2f(5, 0))
	,titolo_("NON GRAVITAR", 120, sf::Color::Red, sf::Color::Yellow, 1.5, 4, sf::Vector2f(LARGHEZZA / 2 - titolo_.getGlobalBounds().width / 2, 10))
	,subtitle_("",60, sf::Color::Red, sf::Color::Transparent, 1.5, 0, sf::Vector2f(0, 0))
	,start_("",55, sf::Color::Green, sf::Color::Transparent, 1.5, 0, sf::Vector2f(LARGHEZZA / 2 - start_.getGlobalBounds().width / 2, ALTEZZA / 2))
	,exit_("EXIT", 55, sf::Color::Magenta, sf::Color::Transparent, 1.5, 0, sf::Vector2f(LARGHEZZA / 2 - exit_.getGlobalBounds().width / 2, ALTEZZA / 2 + 100))
	,vita_text_("VITA: 100", 32, sf::Color::Red, sf::Color::Blue, 1.5, 1, sf::Vector2f(LARGHEZZA / 2 - 300, 0))
	,carburante_text_("", 32, sf::Color::Red, sf::Color::Blue, 1.5, 1, sf::Vector2f(0, 0))
{
	titolo_.setPosition(LARGHEZZA / 2 - titolo_.getGlobalBounds().width / 2,10);
	exit_.setPosition(LARGHEZZA / 2 - exit_.getGlobalBounds().width / 2, ALTEZZA / 2 + 100);
	start_.setPosition(LARGHEZZA / 2 - start_.getGlobalBounds().width / 2, ALTEZZA / 2);

	float distanzaPunteggioVita = vita_text_.getPosition().x - (punteggio_text_.getPosition().x + punteggio_text_.getGlobalBounds().width);
	carburante_text_.setPosition(vita_text_.getPosition().x + vita_text_.getGlobalBounds().width + distanzaPunteggioVita, 0);

	pausa_.setSize(sf::Vector2f(61.8, 64.0));
	texture_.loadFromFile("Texture/pausa2.png");
	texture_.setSmooth(true);
	pausa_.setFillColor(sf::Color::Color(255,255,255,160));
	pausa_.setTexture(&texture_);

	punteggio_ = 0;
	aggiornaTestoNumeri("PUNTEGGIO: ", punteggio_, punteggio_text_);

	float pausa_size = punteggio_text_.getGlobalBounds().height + 15;
	pausa_.setSize(sf::Vector2f(pausa_size, pausa_size));
	pausa_.setPosition(LARGHEZZA - pausa_.getSize().x, 0);

	nave_movimento_ = false;
	nave_rotazioneL_ = false;
	nave_rotazioneR_ = false;
	nave_spara_ = false;
	nave_raggio_ = false;

	posizione_entrata_pianeta_ = sf::Vector2f(0, 0); // posizione della nave prima di entrare nel pianeta

	time_frame_ = sf::seconds(1.f / 144.f);

	stato_ = UNIVERSO;
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
				processaEventi();
				update();
			}
			
			render();
	}
}
