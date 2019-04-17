#include "superficie_pianeta.h"
#include <iostream>

void SuperficiePianeta::generaVertici()
{
	std::cout << "----LINEE----" << std::endl; // logging

	for (int i = 0; i <= NUMERO_DI_LINEE; i++) {
		/* Calcolo della coppia di coordinate (x,y).
		La x sarà determinata dalla lunghezza della linea, 
		moltiplicata per l'indice del punto, mentre la y sarà
		generata casualmente tra 0 e l'altezza massima*/
		linee_[i].position = sf::Vector2f(
			i * larghezza_finestra_ / NUMERO_DI_LINEE,
			altezza_finestra_ - (rand() % altezza_massima_)
		);
		linee_[i].color = sf::Color::Red; // impostazione del colore della linea
		
		std::cout << "Punto: " << linee_[i].position.x << " " << linee_[i].position.y << std::endl; // logging
	}
}

void SuperficiePianeta::generaBunker()
{
	std::cout << "----BUNKER----" << std::endl; // logging
	// Il numero di bunker sarà compreso tra 3 e 6
	int numero_di_bunker = (rand() % 4) + 3;

	/* Inizialmente viene scelta casualmente la posizione del bunker
	tra le linee 0 e (MAX - 1), dopo di che, se nella posizione non è presente
	nessun bunker (controllando il vettore di booleani), il bunker verrà generato
	nel punto medio. Nel caso la posizione scelta sia già occupata, verrà ripetuto il ciclo*/
	while (numero_di_bunker > 0) {
		int posizione_bunker = rand() % (NUMERO_DI_LINEE - 1);

		if (bunker_presenti_[posizione_bunker] == false) {
			aggiungiBunker(posizione_bunker); // metodo per aggiungere il bunker alla struttura
			numero_di_bunker--;
			// Posizione impostata a true, per indicare che adesso è occupata da un bunker
			bunker_presenti_[posizione_bunker] = true; 
		}
	}
}

void SuperficiePianeta::aggiungiBunker(int index)
{
	// Vettore che rappresenta la coppia (x,y)
	float puntiMedi[2];
	// Viene calcolato il punto medio tra il punto (passato come parametro) e il successivo
	puntiMedi[0] = ((linee_[index].position.x + linee_[index + 1].position.x) / 2);
	puntiMedi[1] = ((linee_[index].position.y + linee_[index + 1].position.y) / 2);
	
	/* Viene calcolato l'angolo tra i due punti. Per prima cosa deve essere
	calcolato il coefficiente_angolare, che poi viene utilizzato per calcolare 
	l'arcotangente, che restituisce l'angolo in radianti, trasformato poi in decimale.
	Quest'ultimo viene poi aumentato di 180 gradi per permettere che giacia sul segmento
	tra i due punti.*/
	float coefficiente_angolare = (linee_[index + 1].position.y - linee_[index].position.y) /
		(linee_[index + 1].position.x - linee_[index].position.x);

	float angolo = (atan2f(linee_[index + 1].position.y - linee_[index].position.y, 
		linee_[index + 1].position.x - linee_[index].position.x) * 180 / 3.14159265) + 180;

	inserisciNodoBunker(puntiMedi, angolo);

	std::cout << "Proprietà Bunker:\n\tPunto: " << puntiMedi[0] << ", " << puntiMedi[1] << "\n\tSlope: " <<
		coefficiente_angolare << "\n\tArctan: " << angolo << std::endl; // logging
}

void SuperficiePianeta::inserisciNodoBunker(float puntiMedi[], float angolo)
{
	if (bunker_ == nullptr) {
		bunker_ = new BunkerNode();
		bunker_->bunker_item = new Bunker(puntiMedi[0], puntiMedi[1], 20, angolo);
		bunker_->next = nullptr;
	}
	else {
		bunker_ptr tmp = new BunkerNode;
		tmp->bunker_item = new Bunker(puntiMedi[0], puntiMedi[1], 20, angolo);
		tmp->next = bunker_;
		bunker_ = tmp;
}
}

void SuperficiePianeta::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// Draw delle linee
	target.draw(linee_);

	// Puntatore all'attuale struttura rappresentante i Bunker
	bunker_ptr bunker_to_print = bunker_;
	/* Vengono disegnati i Bunker finchè il puntatore
	alla struttura dei Bunker non sarà nullo */
	while (bunker_to_print != nullptr) {
		target.draw(*bunker_to_print->bunker_item);
		bunker_to_print = bunker_to_print->next;
	}
}

SuperficiePianeta::SuperficiePianeta(unsigned int width, unsigned int height) {
	srand(time(NULL));
	larghezza_finestra_ = width;
	altezza_finestra_ = height;

	/* L'altezza massima della superficie può essere
	il 30% dell'altezza della finestra*/
	altezza_massima_ = height * 0.3;

	/* Il vettore di booleani rappresentante i bunker presenti
	viene impostato tutto a false */
	for (int i = 0; i < NUMERO_DI_LINEE; i++) bunker_presenti_[i] = false;

	/* Vengono impostate le proprietà relative
	al VertexArray delle linee della superficie,
	per poi richiamare il metodo che si occupa di impostare le coordinate
	dei punti delle linee */
	linee_.setPrimitiveType(sf::LinesStrip); // il tipo di primitiva che deve essere rappresentata
	linee_.resize(NUMERO_DI_LINEE + 1); // il numero dei punti totali delle linee (num_linee + 1)
	generaVertici();

	/* Metodo per generare i Bunker presenti sulla superficie */
	//if (bunker_ != nullptr)
	//delete bunker_;
	bunker_ = nullptr;
	generaBunker();
}

SuperficiePianeta::SuperficiePianeta() : SuperficiePianeta(10, 10){}
