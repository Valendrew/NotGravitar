#include "Nave.hpp"


Nave::Nave(float x, float y, float r, float velocita_, int carburante_, int vita_) {
	vita = 10;
	carburante = carburante_;
	this->setPosition(x, y);
	this->setRotation(r);
	proiettilil = NULL;
	velocita = velocita_;
}
Nave::Nave() {
	Nave(0.f, 0.f, 0.f, 0.f, 0, 0);
}
void Nave::setVita(int vita_) {
	vita = vita;
}
int Nave::getVita() {
	return vita;
}
void Nave::setCarburante(int carburante_) {
	carburante = carburante_
		;
}
int Nave::getCarburante() {
	return carburante;
}
void Nave::colpito() {
	if (vita <= 0)
		vita--;
}
void Nave::fill(int carburante_) {
	carburante += carburante_;
}
void Nave::muovi() {
	float velX = velocita * sin(this->getRotation()*PI / 180.f); // movimento da fare sull'asse x calcolato rispetto al seno
	float velY = -velocita * cos(this->getRotation()*PI / 180.f); // movimento da fare sull'asse y calcolato rispetto al coseno
	this->move(velX, velY);
}
void Nave::spara(sf::Vector2f dimensioni, int velocita) { // crea un nuovo proiettile e lo inserisce in cima alla lista dei proiettili
	proiettiliP p = new proiettili;
	sf::Vector2f posizione = this->getPosition();
	float r = this->getRotation();
	p->val = new Proiettile(dimensioni, posizione, r, velocita);
	p->val->setFillColor(sf::Color::Green);
	p->next = this->proiettilil;
	proiettilil = p;
}
void Nave::updateProiettili(sf::RenderWindow &window) { // aggiorna la posizione e controlla collisione di tutta la lista di elementi
	proiettiliP p = proiettilil;
	proiettiliP pOld = proiettilil;
	Proiettile pr;
	while (p != NULL) // scorro la lista
	{
		p->val->muovi();
		window.draw(*p->val);
		if (collisioneProiettile(*p->val)) { //elimina un proiettile in caso di collisione
			pOld->next = p->next;
			delete(p);
			p = pOld->next;
		}
		else {
			pOld = p;
			p = p->next;
		}

	}
}
bool Nave::collisioneProiettile(Proiettile proiettile) {
	// TODO
	return false;
}
void Nave::eliminaListaProiettili(proiettiliP head) {
	if (head == nullptr)
		delete(head);
	else {
		eliminaListaProiettili(head->next);
		delete(head);
	}
}