#include "Nave.hpp"

Nave::Nave(unsigned int width, unsigned int height, float vita, const char nomeFile[], sf::Vector2f pos, sf::Vector2f size, float angolo_rotazione, float velocita_movimento, float velocita_rotazione, int carburante)
	: Comportamento(width, height, vita, nomeFile, pos, size, angolo_rotazione) {
	carburante_ = carburante;
	velocita_movimento_ = velocita_movimento;
	velocita_rotazione_ = velocita_rotazione;

	entita_.setOrigin(sf::Vector2f(size.x / 2.f, size.y / 2.f)); // viene impostato il punto di origine 
}
Nave::Nave() : Comportamento() {
	carburante_ = 10;
	velocita_movimento_ = 100.f;
	velocita_rotazione_ = 10.f;

	entita_.setOrigin(sf::Vector2f(25 / 2.f, 25 / 2.f));
}

void Nave::ruotaL()
{
	entita_.rotate(-velocita_rotazione_);
}

void Nave::ruotaR()
{
	entita_.rotate(velocita_rotazione_);
}

void Nave::spara()
{
	Comportamento::spara(this->getRotation());
}

void Nave::setCarburante(int carburante_) {
	carburante_ = carburante_;
}
int Nave::getCarburante() {
	return carburante_;
}
sf::VertexArray Nave::getPosizioneFrontale()
{
	sf::VertexArray vertex(sf::Points, 2);

	float angolo = entita_.getRotation();
	angolo = angolo * PI_G / 180;

	float delta_x = getPosition().x + (entita_.getSize().x / 2) * cos(angolo);
	float delta_y = getPosition().y + (entita_.getSize().y / 2) * sin(angolo);

	//vertex[0].position = sf::Vector2f(delta_x , delta_y);
	vertex[0].position = sf::Vector2f(getPosition().x , getPosition().y);
	//vertex[0].position = sf::Vector2f(entita_.getGlobalBounds().left, entita_.getGlobalBounds().top);
	
	vertex[1].position.x = vertex[0].position.x + entita_.getSize().x * cos(angolo);
	vertex[1].position.y = vertex[0].position.y + entita_.getSize().y * sin(angolo);

	return vertex;
}
void Nave::colpito() {
	if (vita_ <= 0)
		vita_--;
}

void Nave::fill(int carburante_) {
	carburante_ += carburante_;
}

void Nave::muovi(sf::Time deltaTime) {
	float velX = deltaTime.asSeconds() * velocita_movimento_ * sin(entita_.getRotation()*PI_G / 180.f); // movimento da fare sull'asse x calcolato rispetto al seno
	float velY = deltaTime.asSeconds() * -velocita_movimento_ * cos(entita_.getRotation()*PI_G / 180.f); // movimento da fare sull'asse y calcolato rispetto al coseno

	entita_.move(velX, velY);
}

sf::Vector2f Nave::getPosition() { //da modificare i 12.5 con altezza/2 e larghezza/2 generici
	//float coeff = 12.5;
	float coeff_x = entita_.getSize().x / 2;
	float coeff_y = entita_.getSize().y / 2;


	float x1 = entita_.getPosition().x - cos(entita_.getRotation()*PI_G / 180.f)* coeff_x;
	float y1 = entita_.getPosition().y - sin(entita_.getRotation()*PI_G / 180.f)* coeff_y;
	float x2 = x1 + sin(entita_.getRotation()*PI_G / 180.f)* coeff_x;
	float y2 = y1 - cos(entita_.getRotation()*PI_G / 180.f)* coeff_y;
	return sf::Vector2f(x2, y2);
}

void Nave::setPosition(sf::Vector2f pos) { //non testata
	//float coeff = 12.5;
	float coeff_x = entita_.getSize().x / 2;
	float coeff_y = entita_.getSize().y / 2;

	float x1 = pos.x + cos(entita_.getRotation()*PI_G / 180.f)*coeff_x;
	float y1 = pos.y + sin(entita_.getRotation()*PI_G / 180.f)*coeff_y;
	float x2 = x1 - sin(entita_.getRotation()*PI_G / 180.f)*coeff_x;
	float y2 = y1 + cos(entita_.getRotation()*PI_G / 180.f)*coeff_y;
	entita_.setPosition(x2, y2);
}

proiettile_ptr Nave::getProiettili()
{
	return proiettili_;
}
