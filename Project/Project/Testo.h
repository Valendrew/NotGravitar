#ifndef TESTO_H
#define TESTO_H

#include <SFML/Graphics.hpp>
/*Classe per gestire facilmente i testi nel gioco con relativo font*/
class Testo : public sf::Drawable, public sf::Transformable {
private:
public:
	Testo();
	Testo(std::string testo ,int CharacterSize, sf::Color FillColor, sf::Color OutlineColor, double LetterSpacing, int OutlineThickness, sf::Vector2f posizione);
	
	
};


#endif