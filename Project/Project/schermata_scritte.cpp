#include "schermata_scritte.h"




schermata_scritte::schermata_scritte(int LARGHEZZA, int ALTEZZA) :
	punteggio_text_("PUNTEGGIO: 100", 32, sf::Color::Blue, sf::Color::Magenta, 1.5, 1, sf::Vector2f(5, 0))
	, titolo_("NON GRAVITAR", 120, sf::Color::Red, sf::Color::Yellow, 1.5, 4, sf::Vector2f(0, 0))
	, subtitle_("", 60, sf::Color::Red, sf::Color::Transparent, 1.5, 0, sf::Vector2f(0, 0))
	, start_("START", 55, sf::Color::Green, sf::Color::Transparent, 1.5, 0, sf::Vector2f(LARGHEZZA / 2 - start_.getGlobalBounds().width / 2, ALTEZZA / 2))
	, exit_("EXIT", 55, sf::Color::Magenta, sf::Color::Transparent, 1.5, 0, sf::Vector2f(LARGHEZZA / 2 - exit_.getGlobalBounds().width / 2, ALTEZZA / 2 + 100))
	, vita_text_("VITA: 100", 32, sf::Color::Red, sf::Color::Blue, 1.5, 1, sf::Vector2f(LARGHEZZA / 2 - 300, 0))
	, carburante_text_("", 32, sf::Color::Red, sf::Color::Blue, 1.5, 1, sf::Vector2f(0, 0)) {

	ALTEZZA_ = ALTEZZA;
	LARGHEZZA_ = LARGHEZZA;
	titolo_.setPosition(sf::Vector2f(LARGHEZZA / 2 - titolo_.getGlobalBounds().width / 2, 10));
	exit_.setPosition(sf::Vector2f(LARGHEZZA / 2 - exit_.getGlobalBounds().width / 2, ALTEZZA / 2 + 100));
	start_.setPosition(sf::Vector2f(LARGHEZZA / 2 - start_.getGlobalBounds().width / 2, ALTEZZA / 2));

	float distanzaPunteggioVita = vita_text_.getPosition().x - (punteggio_text_.getPosition().x + punteggio_text_.getGlobalBounds().width);
	carburante_text_.setPosition(sf::Vector2f(vita_text_.getPosition().x + vita_text_.getGlobalBounds().width + distanzaPunteggioVita, 0));
}

void schermata_scritte::aggiornaTesto(const char stringa[], int valore) {

	char valoreToString[10];
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
		carburante_text_.setString(stringaCompleta);
	}

}

void schermata_scritte::SetGameOver()
{
	start_.setString("RESTART");
	subtitle_.setString("GAME OVER");
	subtitle_.setPosition(sf::Vector2f(LARGHEZZA_ / 2 - subtitle_.getGlobalBounds().width / 2, 140));
	punteggio_text_.setPosition(sf::Vector2f(LARGHEZZA_ / 2 - punteggio_text_.getGlobalBounds().width / 2, 210));
	start_.setPosition(sf::Vector2f(LARGHEZZA_ / 2 - start_.getGlobalBounds().width / 2, ALTEZZA_ / 2));
}

void schermata_scritte::SetPausa() {
	start_.setString("RESUME");
	start_.setPosition(sf::Vector2f(LARGHEZZA_ / 2 - start_.getGlobalBounds().width / 2, ALTEZZA_ / 2));
	punteggio_text_.setPosition(sf::Vector2f(LARGHEZZA_ / 2 - punteggio_text_.getGlobalBounds().width / 2, 210));
}

Testo schermata_scritte::getExit()
{
	return exit_;
}

Testo schermata_scritte::getStart()
{
	return start_;
}

Testo schermata_scritte::getTitolo()
{
	return titolo_;
}

Testo schermata_scritte::getSubtitle()
{
	return subtitle_;
}

Testo schermata_scritte::getPunteggio()
{
	return punteggio_text_;
}

Testo schermata_scritte::getVita()
{
	return vita_text_;
}

Testo schermata_scritte::getCarburante()
{
	return carburante_text_;
}

int schermata_scritte::gestioneMouse(sf::Vector2i posizioneMouse) {
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

void schermata_scritte::setStart() {

	start_.setCharacterSize(55);
	start_.setPosition(sf::Vector2f(LARGHEZZA_ / 2 - start_.getGlobalBounds().width / 2, ALTEZZA_ / 2));
}

void schermata_scritte::setPunteggio() {
	punteggio_text_.setPosition(sf::Vector2f(5, 0));
}
