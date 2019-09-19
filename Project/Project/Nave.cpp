#include "nave.hpp"

Nave::Nave(float vita, const char nomeFile[], sf::IntRect dimensione_texture, float cord_x, float cord_y, float larghezza_e, float altezza_e, float angolo_rotazione, float velocita, int carburante) 
: Comportamento(vita, nomeFile, dimensione_texture, cord_x, cord_y, larghezza_e, altezza_e, angolo_rotazione) {
	carburante_ = carburante;
	velocita_ = velocita;
	proiettilil = NULL;
	
}
Nave::Nave() : Comportamento() {
	carburante_ = 10;
	velocita_ = 10;
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
void Nave::muovi() {
	float velX = velocita_ * sin(entita_.getRotation()*PI_G / 180.f); // movimento da fare sull'asse x calcolato rispetto al seno
	float velY = -velocita_ * cos(entita_.getRotation()*PI_G / 180.f); // movimento da fare sull'asse y calcolato rispetto al coseno
	
	entita_.move(velX, velY);
}

/*void Nave::spara(sf::Vector2f dimensioni, int velocita) { // crea un nuovo proiettile e lo inserisce in cima alla lista dei proiettili
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
		//}

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
}*/