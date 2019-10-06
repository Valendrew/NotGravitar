#include "superficie_pianeta.h"

void SuperficiePianeta::generaVertici(sf::Vector2f first_point, sf::Vector2f last_point)
{
	int range = 40;
	int altezza_minima = altezza_finestra_ - 50;
		
	for (int i = 0; i < vertici_superficie_.getVertexCount(); i++) {
		/* Calcolo della coppia di coordinate (x,y).
		La x sar� determinata dalla lunghezza della linea, 
		moltiplicata per l'indice del punto, mentre la y sar�
		generata casualmente tra l'altezza minima e l'altezza massima*/
		if (i == 0)
		{
			if (first_point.y > 0) {
				vertici_superficie_[i].position = sf::Vector2f(i * larghezza_finestra_ / NUMERO_DI_LINEE
					, first_point.y);
			}
			else {
				vertici_superficie_[i].position = sf::Vector2f(i * larghezza_finestra_ / NUMERO_DI_LINEE
					, altezza_minima - (rand() % (altezza_minima - altezza_massima_)));
			}
		}

		else {
			if (i == (vertici_superficie_.getVertexCount() - 1) && last_point.y > 0) {
				vertici_superficie_[i].position = sf::Vector2f(i * larghezza_finestra_ / NUMERO_DI_LINEE
					, last_point.y);
			}
			else {
				// Lo scarto viene utilizzato per consentire che la superficie sia pi� naturale possibile
				int scarto = 0;

				if (altezza_massima_ + range > vertici_superficie_[i - 1].position.y) {
					// In questo caso lo scarto sar� negativo
					scarto = altezza_massima_ - vertici_superficie_[i - 1].position.y;
				}
				else if (altezza_minima - range < vertici_superficie_[i - 1].position.y) {
					// In questo caso lo scarto sar� positivo
					scarto = altezza_minima - vertici_superficie_[i - 1].position.y;
				}

				int altezza_random = ((rand() % (range * 2 + 1)) - (range + scarto)) + vertici_superficie_[i - 1].position.y;

				if (altezza_random > altezza_minima) altezza_random = altezza_minima;
				else if (altezza_random < altezza_massima_) altezza_random = altezza_massima_;

				vertici_superficie_[i].position = sf::Vector2f(i * larghezza_finestra_ / NUMERO_DI_LINEE
					, altezza_random);
			}
		}
		
		//vertici_superficie1_[i].color = sf::Color::Blue; // impostazione del colore della linea
	}
}

void SuperficiePianeta::generaSuperficie()
{
	/*int i = 0;
	int abs_index = 0;
	int current_sup = 0;
	int max_lines_per_window = NUMERO_DI_LINEE / numero_superfici;

	while (abs_index < NUMERO_DI_LINEE && current_sup < numero_superfici) {
		superficie_[abs_index].setPointCount(4);

		if (i % max_lines_per_window == 0) {
			float x = vertici_superficie1_[abs_index].position.x;
			float new_x = (int) vertici_superficie1_[abs_index].position.x % larghezza_finestra_;

			superficie_[abs_index].setPoint(0, sf::Vector2f(new_x, vertici_superficie1_[abs_index].position.y));
			superficie_[abs_index].setPoint(1, vertici_superficie1_[abs_index + 1].position);
			superficie_[abs_index].setPoint(2, sf::Vector2f(vertici_superficie1_[abs_index + 1].position.x, altezza_finestra_));
			superficie_[abs_index].setPoint(3, sf::Vector2f(new_x, altezza_finestra_));

		}
		else {
			// Impostazione dei punti
			superficie_[abs_index].setPoint(0, vertici_superficie1_[abs_index].position);
			superficie_[abs_index].setPoint(1, vertici_superficie1_[abs_index + 1].position);
			superficie_[abs_index].setPoint(2, sf::Vector2f(vertici_superficie1_[abs_index + 1].position.x, altezza_finestra_));
			superficie_[abs_index].setPoint(3, sf::Vector2f(vertici_superficie1_[abs_index].position.x, altezza_finestra_));
		}

		// Impostazione del colore della superficie
		superficie_[abs_index].setFillColor(sf::Color::Blue);

		i++;
		abs_index++;
		if (i % max_lines_per_window == 1) {
			i = 1;
		}
	}*/

	for (int i = 0; i < NUMERO_DI_LINEE; i++)
		{
			superficie_[i].setPointCount(4);

			// Impostazione dei punti
			superficie_[i].setPoint(0, vertici_superficie_[i].position);
			superficie_[i].setPoint(1, vertici_superficie_[i + 1].position);
			superficie_[i].setPoint(2, sf::Vector2f(vertici_superficie_[i + 1].position.x, altezza_finestra_));
			superficie_[i].setPoint(3, sf::Vector2f(vertici_superficie_[i].position.x, altezza_finestra_));

			// Impostazione del colore della superficie
			superficie_[i].setFillColor(sf::Color::Blue);
		}
}

void SuperficiePianeta::generaBunker()
{
	// Il numero di bunker sar� compreso tra 2 e 3
	int numero_di_bunker = (rand() % 2) + 2;

	/* Inizialmente viene scelta casualmente la posizione del bunker
	tra le linee 0 e (MAX - 1), dopo di che, se nella posizione non � presente
	nessun bunker (controllando il vettore di booleani), il bunker verr� generato
	nel punto medio. Nel caso la posizione scelta sia gi� occupata, verr� ripetuto il ciclo*/
	while (numero_di_bunker > 0) {
		int posizione_bunker = rand() % (NUMERO_DI_LINEE - 2) + 1;

		if (bunker_presenti_[posizione_bunker] == false) {
			if (!controllaBunkerVicinanze(posizione_bunker)) {
				aggiungiBunker(posizione_bunker); // metodo per aggiungere il bunker alla struttura
				numero_di_bunker--;
				// Posizione impostata a true, per indicare che adesso � occupata da un bunker
				bunker_presenti_[posizione_bunker] = true;
			}
		}
	}
}

bool SuperficiePianeta::controllaBunkerVicinanze(int posizione)
{
	int distanza = 2, startIndex = 0, finishIndex = NUMERO_DI_LINEE;
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
	sf::Vector2f new_coordinate_bunker;
	float coordinate_bunker[2];
	int grandezza_bunker = 30;
	
	/* Viene calcolato l'angolo tra i due punti. Per prima cosa deve essere
	calcolato il coefficiente_angolare, che poi viene utilizzato per calcolare 
	l'arcotangente, che restituisce l'angolo in radianti, trasformato poi in decimale.*/

	float coefficiente_angolare = (vertici_superficie_[index + 1].position.y - vertici_superficie_[index].position.y) /
		(vertici_superficie_[index + 1].position.x - vertici_superficie_[index].position.x);

	float angolo = (atan2f(vertici_superficie_[index + 1].position.y - vertici_superficie_[index].position.y, 
		vertici_superficie_[index + 1].position.x - vertici_superficie_[index].position.x) * 180 / PI);

	/* Generazione del punto di spawn del Bunker, con l'ascisse tra 0 e 31, in modo tale che la sprite non
	sia oltre la linea, dato che la posizione � riferita all'angolo in alto a destra. Per ottenere l'ordinata sar�
	prima ottenuta l'ordinata all'origine della linea, ed infine, tramite l'equazione della retta, si otterr� 
	il valore dell'ordinata*/
	float ordinata_origine = vertici_superficie_[index].position.y - vertici_superficie_[index].position.x * coefficiente_angolare;
	int offset = 15;

	coordinate_bunker[0] = rand() % (grandezza_bunker) + offset + vertici_superficie_[index].position.x;
	coordinate_bunker[1] = coordinate_bunker[0] * coefficiente_angolare + ordinata_origine;

	new_coordinate_bunker.x = rand() % (grandezza_bunker)+offset + vertici_superficie_[index].position.x;
	new_coordinate_bunker.y = new_coordinate_bunker.x * coefficiente_angolare + ordinata_origine;;

	inserisciNodoBunker(new_coordinate_bunker, angolo, sf::Vector2f(grandezza_bunker, grandezza_bunker));
}

void SuperficiePianeta::inserisciNodoBunker(sf::Vector2f coordinate, float angolo, sf::Vector2f grandezza)
{
	Bunker *new_bunker = new Bunker(larghezza_finestra_, altezza_finestra_, 40, "Texture/bunker_3.png", coordinate, grandezza, angolo);

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
	for (size_t i = 0; i < NUMERO_DI_LINEE; i++)
	{
		target.draw(superficie_[i]);
	}

	// Puntatore all'attuale struttura rappresentante i Bunker
	bunker_ptr bunker_to_print = bunker_;
	/* Vengono disegnati i Bunker finch� il puntatore
	alla struttura dei Bunker non sar� nullo */
	while (bunker_to_print != nullptr) {
		(*bunker_to_print->bunker_item).spara();
		target.draw(*bunker_to_print->bunker_item);
		bunker_to_print = bunker_to_print->next;
	}
}

SuperficiePianeta::SuperficiePianeta(unsigned int width, unsigned height, sf::Vector2f first_point, sf::Vector2f last_point)
{
	larghezza_finestra_ = width;
	altezza_finestra_ = height;

	/* L'altezza massima della superficie pu� essere
	il 30% dell'altezza della finestra*/
	altezza_massima_ = altezza_finestra_ * 0.75;

	/* Vengono impostate le propriet� relative
	al VertexArray delle linee della superficie,
	per poi richiamare il metodo che si occupa di impostare le coordinate
	dei punti delle linee */
	vertici_superficie_.setPrimitiveType(sf::LinesStrip); // il tipo di primitiva che deve essere rappresentata
	vertici_superficie_.resize(NUMERO_DI_LINEE + 1); // il numero dei punti totali delle linee (num_linee + 1)
	generaVertici(first_point, last_point);

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

SuperficiePianeta::SuperficiePianeta(unsigned int width, unsigned int height) : SuperficiePianeta(width, height, sf::Vector2f(), sf::Vector2f()) {}

SuperficiePianeta::SuperficiePianeta() : SuperficiePianeta(10, 10){}

sf::Vector2f SuperficiePianeta::getLastVertex()
{
	return vertici_superficie_[vertici_superficie_.getVertexCount() - 1].position;
}

sf::Vector2f SuperficiePianeta::getFirstVertex()
{
	return vertici_superficie_[0].position;
}

proiettile_ptr SuperficiePianeta::getProiettili()
{
	proiettile_ptr lista_proiettili = nullptr;
	
	bunker_ptr tmp_list = bunker_;
	
	while (tmp_list != nullptr)
	{
		lista_proiettili = (*tmp_list->bunker_item).getProiettili();
		tmp_list = tmp_list->next;
	}

	return lista_proiettili;
}

bool SuperficiePianeta::controlloCollisioneSuperficie(sf::Vector2f pos)
{
	bool collisione = false;

	for (int i = 0; i < NUMERO_DI_LINEE; i++)
	{
		if (superficie_[i].getGlobalBounds().contains(pos)) {
			collisione = true;
		}
	}
	return collisione;
}
