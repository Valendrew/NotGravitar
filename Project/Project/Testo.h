#ifndef TESTO_H
#define TESTO_H

#include <SFML/Graphics.hpp>
/*Classe per gestire facilmente i testi nel gioco con relativo font*/
class Testo : public sf::Drawable, public sf::Transformable {
private:
	sf::Text testo_;
	sf::Font font_;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Testo();
	Testo(std::string testo ,int CharacterSize, sf::Color FillColor, sf::Color OutlineColor, double LetterSpacing, int OutlineThickness, sf::Vector2f posizione);
	
	void setString(std::string s);
	sf::FloatRect getGlobalBounds();
	std::string getString();
	void setCharacterSize(int size);
	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition();
};


#endif