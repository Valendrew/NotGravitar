#include "Nave.hpp"

Nave::Nave(float vita, const char nomeFile[], float cord_x, float cord_y, float larghezza_e, float altezza_e, float angolo_rotazione, float velocita_movimento, float velocita_rotazione, int carburante)
	: Comportamento(vita, nomeFile, cord_x, cord_y, larghezza_e, altezza_e, angolo_rotazione) {
	carburante_ = carburante;
	velocita_movimento_ = velocita_movimento;
	velocita_rotazione_ = velocita_rotazione;

	//entita_.setOrigin(sf::Vector2f(larghezza_e / 2.f, altezza_e / 2.f)); // viene impostato il punto di origine 
}
Nave::Nave() : Comportamento() {
	carburante_ = 10;
	velocita_movimento_ = .2f;
	velocita_rotazione_ = .1f;

	//entita_.setOrigin(sf::Vector2f(25 / 2.f, 25 / 2.f));
}

void Nave::ruotaL()
{
	entita_.rotate(-velocita_rotazione_);
}

void Nave::ruotaR()
{
	entita_.rotate(velocita_rotazione_);
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

	float delta_x = entita_.getPosition().x + (entita_.getSize().x / 2) * cos(angolo);
	float delta_y = entita_.getPosition().y + (entita_.getSize().y / 2) * sin(angolo);

	//vertex[0].position = sf::Vector2f(delta_x , delta_y);
	vertex[0].position = sf::Vector2f(entita_.getPosition().x , entita_.getPosition().y);
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
void Nave::muovi() {
	float velX = velocita_movimento_ * sin(entita_.getRotation()*PI_G / 180.f); // movimento da fare sull'asse x calcolato rispetto al seno
	float velY = -velocita_movimento_ * cos(entita_.getRotation()*PI_G / 180.f); // movimento da fare sull'asse y calcolato rispetto al coseno

	entita_.move(velX, velY);
}