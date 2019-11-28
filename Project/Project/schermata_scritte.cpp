#include "schermata_scritte.h"
#include <iostream>



SchermataScritte::SchermataScritte(int LARGHEZZA, int ALTEZZA) {
	ALTEZZA_ = ALTEZZA;
	LARGHEZZA_ = LARGHEZZA;
	font_.loadFromFile("Font/edunline.ttf");

	punteggio_text_.setString("PUNTEGGIO: 0");
	punteggio_text_.setCharacterSize(32);
	punteggio_text_.setFillColor(sf::Color::Blue);
	punteggio_text_.setOutlineColor(sf::Color::Magenta);
	punteggio_text_.setLetterSpacing(1.5);
	punteggio_text_.setOutlineThickness(1);
	punteggio_text_.setFont(font_);
	punteggio_text_.setPosition(sf::Vector2f(5, 0));

	titolo_.setString("NON GRAVITAR");
	titolo_.setCharacterSize(120);
	titolo_.setFillColor(sf::Color::Red);
	titolo_.setOutlineColor(sf::Color::Yellow);
	titolo_.setLetterSpacing(1.5);
	titolo_.setOutlineThickness(4);
	titolo_.setFont(font_);
	titolo_.setPosition(sf::Vector2f(sf::Vector2f(LARGHEZZA / 2 - titolo_.getGlobalBounds().width / 2, 10)));

	subtitle_.setString("");
	subtitle_.setCharacterSize(60);
	subtitle_.setFillColor(sf::Color::Red);
	subtitle_.setOutlineColor(sf::Color::Transparent);
	subtitle_.setLetterSpacing(1.5);
	subtitle_.setOutlineThickness(0);
	subtitle_.setFont(font_);
	subtitle_.setPosition(sf::Vector2f(0, 0));

	start_.setString("START");
	start_.setCharacterSize(55);
	start_.setFillColor(sf::Color::Green);
	start_.setOutlineColor(sf::Color::Transparent);
	start_.setLetterSpacing(1.5);
	start_.setOutlineThickness(0);
	start_.setFont(font_);
	start_.setPosition(sf::Vector2f(LARGHEZZA / 2 - start_.getGlobalBounds().width / 2, ALTEZZA / 2));

	exit_.setString("EXIT");
	exit_.setCharacterSize(55);
	exit_.setFillColor(sf::Color::Magenta);
	exit_.setOutlineColor(sf::Color::Transparent);
	exit_.setLetterSpacing(1.5);
	exit_.setOutlineThickness(0);
	exit_.setFont(font_);
	exit_.setPosition(sf::Vector2f(LARGHEZZA / 2 - exit_.getGlobalBounds().width / 2, ALTEZZA / 2 + 100));

	vita_text_.setString("VITA: 100");
	vita_text_.setCharacterSize(32);
	vita_text_.setFillColor(sf::Color::Red);
	vita_text_.setOutlineColor(sf::Color::Blue);
	vita_text_.setLetterSpacing(1.5);
	vita_text_.setOutlineThickness(1);
	vita_text_.setFont(font_);
	vita_text_.setPosition(sf::Vector2f(LARGHEZZA / 2 - 300, 0));

	carburante_text_.setString("");
	carburante_text_.setCharacterSize(32);
	carburante_text_.setFillColor(sf::Color::Red);
	carburante_text_.setOutlineColor(sf::Color::Blue);
	carburante_text_.setLetterSpacing(1.5);
	carburante_text_.setOutlineThickness(1);
	carburante_text_.setFont(font_);
	float distanzaPunteggioVita = vita_text_.getPosition().x - (punteggio_text_.getPosition().x + punteggio_text_.getGlobalBounds().width);
	carburante_text_.setPosition(sf::Vector2f(vita_text_.getPosition().x + vita_text_.getGlobalBounds().width + distanzaPunteggioVita, 0));

}


void SchermataScritte::aggiornaTesto(const char stringa[], float valore) {
	/*Metodo per aggiornare le scritte con valori numerici come vita, carburante e punteggio*/
	char valoreToString[10];
	char parteDecimaleToString[10];
	char stringaCompleta[100];
	

	_itoa_s(valore, valoreToString, 10, 10);
	

	strcpy_s(stringaCompleta, stringa);
	strcat_s(stringaCompleta, valoreToString);

	
	if (strcmp(stringa, "VITA: ") == 0) {
		vita_text_.setString(stringaCompleta);
	}
	else if (strcmp(stringa, "PUNTEGGIO: ") == 0) {
		punteggio_text_.setString(stringaCompleta);
	}
	else if (strcmp(stringa, "CARBURANTE: ") == 0) {

		int parteDecimale = (valore - (int)valore) * 100;
		_itoa_s(parteDecimale, parteDecimaleToString, 10, 10);
		strcat_s(stringaCompleta, ".");
		strcat_s(stringaCompleta, parteDecimaleToString);
		carburante_text_.setString(stringaCompleta);
	}

}

void SchermataScritte::setGameOver()
{
	start_.setString("RESTART");
	subtitle_.setString("GAME OVER");
	subtitle_.setPosition(sf::Vector2f(LARGHEZZA_ / 2 - subtitle_.getGlobalBounds().width / 2, 140));
	punteggio_text_.setPosition(sf::Vector2f(LARGHEZZA_ / 2 - punteggio_text_.getGlobalBounds().width / 2, 210));
	start_.setPosition(sf::Vector2f(LARGHEZZA_ / 2 - start_.getGlobalBounds().width / 2, ALTEZZA_ / 2));
}

void SchermataScritte::setPausa() {
	start_.setString("RESUME");
	start_.setPosition(sf::Vector2f(LARGHEZZA_ / 2 - start_.getGlobalBounds().width / 2, ALTEZZA_ / 2));
	punteggio_text_.setPosition(sf::Vector2f(LARGHEZZA_ / 2 - punteggio_text_.getGlobalBounds().width / 2, 210));
}

sf::Text SchermataScritte::getExit()
{
	return exit_;
}

sf::Text SchermataScritte::getStart()
{
	return start_;
}

sf::Text SchermataScritte::getTitolo()
{
	return titolo_;
}

sf::Text SchermataScritte::getSubtitle()
{
	return subtitle_;
}

sf::Text SchermataScritte::getPunteggio()
{
	return punteggio_text_;
}

sf::Text SchermataScritte::getVita()
{
	return vita_text_;
}

sf::Text SchermataScritte::getCarburante()
{
	return carburante_text_;
}

int SchermataScritte::gestioneMouse(sf::Vector2i posizioneMouse) {
	int pulsantePremuto = -1;
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
	start_.setPosition(sf::Vector2f(LARGHEZZA_ / 2 - start_.getGlobalBounds().width / 2, ALTEZZA_ / 2));
	exit_.setPosition(sf::Vector2f(LARGHEZZA_ / 2 - exit_.getGlobalBounds().width / 2, ALTEZZA_ / 2 + 100));

	return pulsantePremuto;
}

void SchermataScritte::setStart() {

	start_.setCharacterSize(55);
	start_.setPosition(sf::Vector2f(LARGHEZZA_ / 2 - start_.getGlobalBounds().width / 2, ALTEZZA_ / 2));
}

void SchermataScritte::setPunteggio() {
	punteggio_text_.setPosition(sf::Vector2f(5, 0));
}
