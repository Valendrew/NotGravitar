#include "Nave.hpp"


Nave::Nave(unsigned int larghezza_finestra, unsigned int altezza_finestra, float vita, float danno,
	const char nomeFile[], const char nomeFileDistrutto[], sf::Vector2f posizione, sf::Vector2f dimensione,
	float angolo_rotazione, float velocita_movimento, float velocita_rotazione, int carburante)
	: Comportamento(larghezza_finestra, altezza_finestra, vita, danno,
		nomeFile, nomeFileDistrutto, posizione, dimensione, angolo_rotazione) {
	carburante_ = carburante;
	velocita_movimento_ = velocita_movimento;
	velocita_rotazione_ = velocita_rotazione;

	raggio_.setPointCount(4);
	raggio_.setPoint(0, sf::Vector2f(-dimensione.x, 0));
	raggio_.setPoint(1, sf::Vector2f(0, 0));
	raggio_.setPoint(2, sf::Vector2f(dimensione.x/2, 90));
	raggio_.setPoint(3, sf::Vector2f(-dimensione.x*3/2, 90));
	raggio_.setPosition(getPosition());
	raggio_.setFillColor(sf::Color(0,255,255,100));

	// viene impostato il punto di origine 
	entita_.setOrigin(sf::Vector2f(dimensione.x / 2.f, dimensione.y / 2.f));
}

Nave::Nave() : Comportamento() {
	carburante_ = 10;
	velocita_movimento_ = 100.f;
	velocita_rotazione_ = 10.f;

	entita_.setOrigin(sf::Vector2f(25 / 2.f, 25 / 2.f));
}

void Nave::drawComportamento(sf::RenderTarget& target, sf::RenderStates states)
{
	Comportamento::drawComportamento(target, states);
	if (raggio_attivato_) {
		aggiornaRaggio();
		target.draw(raggio_);
	}
}

void Nave::ruotaSinistra()
{
	if (!distrutto_) 
		entita_.rotate(-velocita_rotazione_);
}

void Nave::ruotaDestra()
{
	if (!distrutto_) 
		entita_.rotate(velocita_rotazione_);
}

void Nave::spara()
{
	float angolo = getRotation();
	float velocita = 1.2f;

	if (clock_.getElapsedTime().asMilliseconds() > 400 && !distrutto_) {
		clock_.restart();

		if (proiettili_ == nullptr) {
			proiettili_ = new ProiettileNode();
			proiettili_->proiettile = new Proiettile(sf::Vector2f(5.f, 5.f), entita_.getPosition(), angolo, velocita, danno_); //crea una nuovo proiettile e lo mette in cima alla lista
			proiettili_->next = nullptr;
		}
		else {
			proiettile_ptr p = new ProiettileNode;
			p->proiettile = new Proiettile(sf::Vector2f(5.f, 5.f), entita_.getPosition(), angolo, velocita, danno_); //crea una nuovo proiettile e lo mette in cima alla lista
			p->next = proiettili_;
			proiettili_ = p;
		}

	}
}

int Nave::getCarburante() {
	return carburante_;
}

void Nave::setCarburante(int carburante_) {
	carburante_ = carburante_;
}

void Nave::riempiCarburante(int carburante) {
	carburante_ += carburante;
}

sf::Vector2f Nave::getPosizioneRaggio()
{
	return raggio_.getPosition();
}

void Nave::aggiornaRaggio()
{
	raggio_.setPosition(getPosition());
	raggio_.setRotation(getRotation()+180);
}

sf::ConvexShape Nave::getRaggio()
{
	return raggio_;
}

void Nave::attivaRaggio(bool attiva)
{
	raggio_attivato_ = attiva;
}

sf::VertexArray Nave::getPosizioneFrontale()
{
	sf::VertexArray vertex(sf::Points, 2);

	float angolo = entita_.getRotation();
	angolo = angolo * PI_G / 180;

	float delta_x = getPosition().x + (entita_.getSize().x / 2) * cos(angolo);
	float delta_y = getPosition().y + (entita_.getSize().y / 2) * sin(angolo);

	vertex[0].position = sf::Vector2f(getPosition().x, getPosition().y);

	vertex[1].position.x = vertex[0].position.x + entita_.getSize().x * cos(angolo);
	vertex[1].position.y = vertex[0].position.y + entita_.getSize().y * sin(angolo);

	return vertex;
}

void Nave::muovi(sf::Time deltaTime) {
	if (!distrutto_) {
		float velX = deltaTime.asSeconds() * velocita_movimento_ * sin(entita_.getRotation()*PI_G / 180.f); // movimento da fare sull'asse x calcolato rispetto al seno
		float velY = deltaTime.asSeconds() * -velocita_movimento_ * cos(entita_.getRotation()*PI_G / 180.f); // movimento da fare sull'asse y calcolato rispetto al coseno

		entita_.move(velX, velY);
	}
}

void Nave::cambiaTextureMovimento(bool movimento)
{
	if (movimento) {
		entita_.setTexture(&texture_); // impostata la texture
	}
	else {
		entita_.setTexture(&texture_distrutto_); // impostata la texture
	}
}

void Nave::passaggioAmbiente(sf::Vector2f posizione)
{
	resetProiettili();
	setPosition(posizione);
}

sf::Vector2f Nave::getPosition() { //da modificare i 12.5 con altezza/2 e larghezza/2 generici
	float coeff_x = entita_.getSize().x / 2;
	float coeff_y = entita_.getSize().y / 2;


	float x1 = entita_.getPosition().x - cos(entita_.getRotation()*PI_G / 180.f)* coeff_x;
	float y1 = entita_.getPosition().y - sin(entita_.getRotation()*PI_G / 180.f)* coeff_y;
	float x2 = x1 + sin(entita_.getRotation()*PI_G / 180.f)* coeff_x;
	float y2 = y1 - cos(entita_.getRotation()*PI_G / 180.f)* coeff_y;
	return sf::Vector2f(x2, y2);
}

void Nave::setPosition(sf::Vector2f pos) { //non testata
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

void Nave::restart(float vita, float cord_x, float cord_y, float angolo_rotazione, int carburante) {
	Comportamento::restart(vita, cord_x, cord_y, angolo_rotazione);
	carburante_ = carburante;	

}