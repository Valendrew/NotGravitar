#ifndef TESTO_H
#define TESTO_H

#include <SFML/Graphics.hpp>

class Testo : public sf::Drawable, public sf::Transformable {
private:
	sf::Text testo_;
	sf::Font font_;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Testo();
	Testo(std::string testo ,int CharacterSize, sf::Color FillColor, sf::Color OutlineColor, double LetterSpacing, float pos_x, float pos_y, int OutlineThickness);
	
	void setString(std::string s);
	sf::FloatRect getGlobalBounds();
	std::string getString();
	void setCharacterSize(int size);
	void setPosition(float x, float y);
};


#endif