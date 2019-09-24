#include "superficie_pianeta.h"

void SuperficiePianeta::generaVertici()
{
	int range = 50;
	int altezza_massima2 = altezza_finestra_ - 15;

	for (int i = 0; i < linee_.getVertexCount(); i++) {
		/* Calcolo della coppia di coordinate (x,y).
		La x sarà determinata dalla lunghezza della linea, 
		moltiplicata per l'indice del punto, mentre la y sarà
		generata casualmente tra 0 e l'altezza massima*/
		if (i == 0)
		{
			linee_[i].position = sf::Vector2f(
				i * larghezza_finestra_ / NUMERO_DI_LINEE,
				altezza_massima2 - (rand() % (altezza_massima2 - altezza_massima_))
			);
		}
		else {
			int scarto = 0;
			if (altezza_massima_ + range > linee_[i - 1].position.y) {
				scarto = altezza_massima_ - linee_[i - 1].position.y;
			}
			else if (altezza_massima2 - range < linee_[i - 1].position.y) {
				scarto = altezza_massima2 - linee_[i - 1].position.y;
			}

			int altezza_random = ((rand() % (range * 2 + 1)) - (range + scarto)) + linee_[i - 1].position.y;
			//int altezza_random = ((rand() % (range * 2 + 1)) - range) + linee_[i - 1].position.y;

			if (altezza_random > altezza_massima2) altezza_random = altezza_massima2;
			else if (altezza_random < altezza_massima_) altezza_random = altezza_massima_;

			linee_[i].position = sf::Vector2f(
				i * larghezza_finestra_ / NUMERO_DI_LINEE,
				altezza_random
			);
		}
		
		linee_[i].color = sf::Color::Blue; // impostazione del colore della linea
	}
}

void SuperficiePianeta::generaSuperficie()
{
	for (size_t i = 0; i < NUMERO_DI_LINEE; i++)
	{
		superficie_[i].setPointCount(4);

		// Impostazione dei punti
		superficie_[i].setPoint(0, linee_[i].position);
		superficie_[i].setPoint(1, linee_[i + 1].position);
		superficie_[i].setPoint(2, sf::Vector2f(linee_[i + 1].position.x, altezza_finestra_));
		superficie_[i].setPoint(3, sf::Vector2f(linee_[i].position.x, altezza_finestra_));

		// Impostazione del colore della superficie
		superficie_[i].setFillColor(sf::Color::Blue);
	}
}

void SuperficiePianeta::generaBunker()
{
	// Il numero di bunker sarà compreso tra 2 e 4
	int numero_di_bunker = (rand() % 3) + 2;

	/* Inizialmente viene scelta casualmente la posizione del bunker
	tra le linee 0 e (MAX - 1), dopo di che, se nella posizione non è presente
	nessun bunker (controllando il vettore di booleani), il bunker verrà generato
	nel punto medio. Nel caso la posizione scelta sia già occupata, verrà ripetuto il ciclo*/
	while (numero_di_bunker > 0) {
		int posizione_bunker = rand() % (NUMERO_DI_LINEE - 1);

		if (bunker_presenti_[posizione_bunker] == false) {
			if (!controllaBunkerVicinanze(posizione_bunker)) {
				aggiungiBunker(posizione_bunker); // metodo per aggiungere il bunker alla struttura
				numero_di_bunker--;
				// Posizione impostata a true, per indicare che adesso è occupata da un bunker
				bunker_presenti_[posizione_bunker] = true;
			}
		}
	}
}

bool SuperficiePianeta::controllaBunkerVicinanze(int posizione)
{
	int distanza = 2, startIndex = 0, finishIndex = NUMERO_DI_LINEE - 1;
	bool found = false;

	if (posizione - distanza > startIndex) startIndex = posizione - distanza;
	if (posizione + distanza < finishIndex) finishIndex = posizione + distanza;

	int i = startIndex;

	while (!found && i <= finishIndex) {
		if (bunker_presenti_[i] == true) found = true;
		i++;
	}
	return found;
}

void SuperficiePianeta::aggiungiBunker(int index)
{
	// Vettore che rappresenta la coppia (x,y)
	float coordinate_bunker[2];
	int grandezza_bunker = 24;
	
	/* Viene calcolato l'angolo tra i due punti. Per prima cosa deve essere
	calcolato il coefficiente_angolare, che poi viene utilizzato per calcolare 
	l'arcotangente, che restituisce l'angolo in radianti, trasformato poi in decimale.*/
	float coefficiente_angolare = (linee_[index + 1].position.y - linee_[index].position.y) /
		(linee_[index + 1].position.x - linee_[index].position.x);

	float angolo = (atan2f(linee_[index + 1].position.y - linee_[index].position.y, 
		linee_[index + 1].position.x - linee_[index].position.x) * 180 / PI);

	/* Generazione del punto di spawn del Bunker, con l'ascisse tra 0 e 31, in modo tale che la sprite non
	sia oltre la linea, dato che la posizione è riferita all'angolo in alto a destra. Per ottenere l'ordinata sarà
	prima ottenuta l'ordinata all'origine della linea, ed infine, tramite l'equazione della retta, si otterrà 
	il valore dell'ordinata*/
	float ordinata_origine = linee_[index].position.y - linee_[index].position.x * coefficiente_angolare;
	int offset = 15;

	coordinate_bunker[0] = rand() % (grandezza_bunker) + offset + linee_[index].position.x;
	coordinate_bunker[1] = coordinate_bunker[0] * coefficiente_angolare + ordinata_origine;;

	inserisciNodoBunker(coordinate_bunker, angolo, grandezza_bunker);
}

void SuperficiePianeta::inserisciNodoBunker(float puntiMedi[], float angolo, int grandezza)
{
	Bunker *new_bunker = new Bunker(50, "Texture/dm300.png", sf::IntRect(0, 0, 20, 20), puntiMedi[0], puntiMedi[1], grandezza, grandezza, angolo);

	if (bunker_ == nullptr) {
		bunker_ = new BunkerNode();
		bunker_->bunker_item = new_bunker;
		bunker_->next = nullptr;
	}
	else {
		bunker_ptr tmp = new BunkerNode;
		tmp->bunker_item = new_bunker;
		tmp->next = bunker_;
		bunker_ = tmp;
}
}

void SuperficiePianeta::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// Draw della superficie
	for (size_t i = 0; i < NUMERO_DI_LINEE; i++)
	{
		target.draw(superficie_[i]);
	}

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
	larghezza_finestra_ = width;
	altezza_finestra_ = height;

	/* L'altezza massima della superficie può essere
	il 30% dell'altezza della finestra*/
	altezza_massima_ = height * 0.75;

	/* Vengono impostate le proprietà relative
	al VertexArray delle linee della superficie,
	per poi richiamare il metodo che si occupa di impostare le coordinate
	dei punti delle linee */
	linee_.setPrimitiveType(sf::LinesStrip); // il tipo di primitiva che deve essere rappresentata
	linee_.resize(NUMERO_DI_LINEE + 1); // il numero dei punti totali delle linee (num_linee + 1)
	generaVertici();

	/* Generazione della superficie a partire dai punti delle linee
	del VertexArray generate precedentemente */
	generaSuperficie();

	/* Il vettore di booleani rappresentante i bunker presenti
	viene impostato tutto a false */
	for (int i = 0; i < NUMERO_DI_LINEE; i++) bunker_presenti_[i] = false;
	bunker_ = nullptr;
	/* Metodo per generare i Bunker presenti sulla superficie */
	generaBunker();
}

SuperficiePianeta::SuperficiePianeta() : SuperficiePianeta(10, 10){}
