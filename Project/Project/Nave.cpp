#include "nave.hpp"
#include <iostream>
Nave::Nave(float vita, const char nomeFile[], sf::IntRect dimensione_texture, float cord_x, float cord_y, float larghezza_e, float altezza_e, float angolo_rotazione, float velocita, int carburante)
	: Comportamento(vita, nomeFile, dimensione_texture, cord_x, cord_y, larghezza_e, altezza_e, angolo_rotazione) {
	carburante_ = carburante;
	velocita_ = velocita;
	angolodirotazione_ = 7;
	entita_.setOrigin(sf::Vector2f(larghezza_e / 2.f, altezza_e / 2.f));
}
Nave::Nave() : Comportamento() {
	carburante_ = 10;
	velocita_ = 50;
	angolodirotazione_ = 7;
	entita_.setOrigin(sf::Vector2f(12.5, 12.5));
}

void Nave::ruotaL()
{
	entita_.rotate(-angolodirotazione_);
}

void Nave::ruotaR()
{
	entita_.rotate(angolodirotazione_);
}

void Nave::spara()
{
	Comportamento::spara(this->getRotazione());
}

void Nave::setCarburante(int carburante_) {
	carburante_ = carburante_;
}
int Nave::getCarburante() {
	return carburante_;
}
void Nave::colpito() {
	if (vita_ <= 0)
		vita_--;
}
void Nave::fill(int carburante_) {
	carburante_ += carburante_;
}
void Nave::muovi(sf::Time deltaTime) {
	float velX = deltaTime.asSeconds() * velocita_ * sin(entita_.getRotation()*PI_G / 180.f); // movimento da fare sull'asse x calcolato rispetto al seno
	float velY = deltaTime.asSeconds() * (-velocita_) * cos(entita_.getRotation()*PI_G / 180.f); // movimento da fare sull'asse y calcolato rispetto al coseno

	entita_.move(velX, velY);
}
sf::Vector2f Nave::getPosizione() { //da modificare i 12.5 con altezza/2 e larghezza/2 generici
	float x1 = entita_.getPosition().x - cos(entita_.getRotation()*PI_G / 180.f)*12.5; 
	float y1 = entita_.getPosition().y - sin(entita_.getRotation()*PI_G / 180.f)*12.5;
	float x2 = x1 + sin(entita_.getRotation()*PI_G / 180.f)*12.5;
	float y2 = y1 - cos(entita_.getRotation()*PI_G / 180.f)*12.5;
	return sf::Vector2f(x2, y2);
}
void Nave::setPosizione(sf::Vector2f pos) { //non testata
	float x1 =pos.x + cos(entita_.getRotation()*PI_G / 180.f)*12.5;
	float y1 =pos.y + sin(entita_.getRotation()*PI_G / 180.f)*12.5;
	float x2 = x1 - sin(entita_.getRotation()*PI_G / 180.f)*12.5;
	float y2 = y1 + cos(entita_.getRotation()*PI_G / 180.f)*12.5;
	entita_.setPosition(x2, y2);
}