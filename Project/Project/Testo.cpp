#include "Testo.h"
#include <SFML/Graphics.hpp>


Testo::Testo(std::string testo, int CharacterSize,  
	sf::Color FillColor, sf::Color OutlineColor, double LetterSpacing, float pos_x, float pos_y, int OutlineThickness)
 
{
	font_.loadFromFile("Font/edunline.ttf");
	testo_.setFont(font_);
	testo_.setString(testo);
	testo_.setCharacterSize(CharacterSize);
	testo_.setFillColor(FillColor);
	testo_.setOutlineColor(OutlineColor);
	testo_.setLetterSpacing(LetterSpacing);
	testo_.setOutlineThickness(OutlineThickness);
	testo_.setPosition(pos_x, pos_y);
}
Testo::Testo() : Testo("404", 25, sf::Color::Red, sf::Color::Red, 20, 0, 0, 5) {}

void Testo::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(testo_);
}

void Testo::setString(std::string s) {
	testo_.setString(s);
}
sf::FloatRect Testo::getGlobalBounds() {
	return testo_.getGlobalBounds();
}
std::string Testo::getString() {
	return testo_.getString();
}
void Testo::setCharacterSize(int size) {
	testo_.setCharacterSize(size);
}
void Testo::setPosition(float x, float y) {
	testo_.setPosition(x, y);
}