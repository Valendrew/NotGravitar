#include "Nave.hpp"

Nave::Nave(unsigned int larghezza_finestra, unsigned int altezza_finestra, float vita, float danno,
	const char nomeFile[], const char nomeFileDistrutto[], sf::Vector2f posizione, sf::Vector2f dimensione,
	float angolo_rotazione, float velocita_movimento, float velocita_rotazione, float carburante)
	: Comportamento(larghezza_finestra, altezza_finestra, vita, danno,
		nomeFile, nomeFileDistrutto, posizione, dimensione, angolo_rotazione) {
	carburante_ = carburante;
	carburante_movimento_ = 0.001f;

	velocita_movimento_ = velocita_movimento;
	velocita_attuale_movimento_ = 0.0f;
	velocita_rotazione_ = velocita_rotazione;
	colore_proiettile_ = sf::Color(32, 181, 98);

	/*creazione del raggio traente come convex shape di forma
	trapezoidale con la base minore della larghezza della
	dimensione della shape della nave*/
	raggio_.setPointCount(4);
	raggio_.setPoint(0, sf::Vector2f(-dimensione.x, 0));
	raggio_.setPoint(1, sf::Vector2f(0, 0));
	raggio_.setPoint(2, sf::Vector2f(dimensione.x / 2, 90));
	raggio_.setPoint(3, sf::Vector2f(-dimensione.x * 3 / 2, 90));
	raggio_.setPosition(getPosition());
	raggio_.setFillColor(sf::Color(0, 255, 255, 100));

	// viene impostato il punto di origine al centro per ruotare correttamente
	entita_.setOrigin(sf::Vector2f(dimensione.x / 2.f, dimensione.y / 2.f));
}

Nave::Nave() : Comportamento() {
	carburante_ = 10;
	velocita_movimento_ = 100.f;
	velocita_attuale_movimento_ = 0.0f;
	velocita_rotazione_ = 10.f;
	colore_proiettile_ = sf::Color(0, 113, 0, 255);

	entita_.setOrigin(sf::Vector2f(25 / 2.f, 25 / 2.f)); 
}

void Nave::drawComportamento(sf::RenderTarget& target, sf::RenderStates states)
{
	Comportamento::drawComportamento(target, states);
	//disegna e aggiorna il raggio traente
	if (raggio_attivato_) {
		aggiornaRaggio();
		target.draw(raggio_);
	}
}

void Nave::ruotaSinistra()
{
		entita_.rotate(-velocita_rotazione_);
}

void Nave::ruotaDestra()
{
		entita_.rotate(velocita_rotazione_);
}

void Nave::spara()
{
	float angolo = getRotation();
	/*aggiunge alla lista proiettili un nuovo proiettile*/
	if (clock_.getElapsedTime().asMilliseconds() > 300) { //proiettili creati a non meno di 300 ms uno dall'altro
		clock_.restart();

		if (proiettili_ == nullptr) {
			proiettili_ = new ProiettileNode();
			proiettili_->proiettile = new Proiettile(sf::Vector2f(5.f, 5.f), entita_.getPosition(), angolo, velocita_sparo_, danno_, colore_proiettile_); //crea una nuovo proiettile e lo mette in cima alla lista
			proiettili_->next = nullptr;
		}
		else {
			proiettile_ptr p = new ProiettileNode;
			p->proiettile = new Proiettile(sf::Vector2f(5.f, 5.f), entita_.getPosition(), angolo, velocita_sparo_, danno_, colore_proiettile_); //crea una nuovo proiettile e lo mette in cima alla lista
			p->next = proiettili_;
			proiettili_ = p;
		}

	}
}

float Nave::getCarburante() {
	return carburante_;
}

void Nave::setCarburante(int carbu_) {
	carburante_ = carbu_;
}

void Nave::riempiCarburante(float carburante) {
	if(carburante_ + carburante > 10)
	carburante_ = 10;
	else carburante_ += carburante;
}

void Nave::aggiornaRaggio()
{
	raggio_.setPosition(getPosition());
	raggio_.setRotation(getRotation() + 180); //raggio ruotato di 180 per poterlo vedere davanti alla nave
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
	/*calcola la posizione frontale della nave,
	la posizione "originale" ? stata settata al centro*/
	sf::VertexArray vertex(sf::Points, 2);

	float angolo = entita_.getRotation();
	angolo = angolo * PI_G / 180;

	vertex[0].position = sf::Vector2f(getPosition().x, getPosition().y);

	vertex[1].position.x = vertex[0].position.x + entita_.getSize().x * cos(angolo);
	vertex[1].position.y = vertex[0].position.y + entita_.getSize().y * sin(angolo);

	return vertex;
}

void Nave::muovi(sf::Time deltaTime, bool movimento) {
	
	if (carburante_ <= 0) {
		Comportamento::setDistrutto();
	}
	else {
		/*velocit? modificata accellerando (fino a un massimo)
		o decellerando (fino a 0)*/
		float accelerazione = 2.5f;
		cambiaTextureMovimento(movimento);
		if (movimento) {
			if (velocita_attuale_movimento_ <= velocita_movimento_ - accelerazione)
				velocita_attuale_movimento_ += accelerazione;
			else
				velocita_attuale_movimento_ = velocita_movimento_;
			carburante_ -= carburante_movimento_;
		}
		else {
			if (velocita_attuale_movimento_ >= accelerazione)
				velocita_attuale_movimento_ -= accelerazione;
			else
				velocita_attuale_movimento_ = 0.0f;
		}
		
		/*velocit? calcolata rispetto al deltaTime dell'ultima 
		chiamata, per evitare possibili rallentamenti*/
		float velX = deltaTime.asSeconds() * velocita_attuale_movimento_ * sin(entita_.getRotation()*PI_G / 180.f); // movimento da fare sull'asse x calcolato rispetto al seno
		float velY = deltaTime.asSeconds() * -velocita_attuale_movimento_ * cos(entita_.getRotation()*PI_G / 180.f); // movimento da fare sull'asse y calcolato rispetto al coseno

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

void Nave::setDannoCollisione() {
	diminuisciVita(3.0f);
}

void Nave::aggiungiVita(int vita_aggiunta) {
	if (vita_ + vita_aggiunta > 100)
		vita_ = 100;
	else vita_ += vita_aggiunta;
}

sf::Vector2f Nave::getPosition() { 
	/*ritorna la posizione dell'angolo davanti a sinistra della nave*/
	float coeff_x = entita_.getSize().x / 2;
	float coeff_y = entita_.getSize().y / 2;

	//calcola a partire dal centro dell'entita l'angolo tenendo conto della rotazione
	float x1 = entita_.getPosition().x - cos(entita_.getRotation()*PI_G / 180.f)* coeff_x;
	float y1 = entita_.getPosition().y - sin(entita_.getRotation()*PI_G / 180.f)* coeff_y;
	float x2 = x1 + sin(entita_.getRotation()*PI_G / 180.f)* coeff_x;
	float y2 = y1 - cos(entita_.getRotation()*PI_G / 180.f)* coeff_y;
	return sf::Vector2f(x2, y2);
}

void Nave::setPosition(sf::Vector2f pos) { 
	/*imposta la posizione della nave, pos = all'angolo in alto a sinistra*/
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

void Nave::restart(float vita, sf::Vector2f posizione, float angolo_rotazione, float carburante, bool distrutto) {
	Comportamento::restart(vita, posizione, angolo_rotazione, distrutto);
	carburante_ = carburante;	
	resetProiettili();
}