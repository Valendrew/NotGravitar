#include "superficie_pianeta.h"

void SuperficiePianeta::generaVertici(sf::Vector2f first_point, sf::Vector2f last_point)
{
	int range = 30;
		
	for (int i = 0; i < vertici_superficie_.getVertexCount(); i++) {
		/* Calcolo della coppia di coordinate (x,y).
		La x sarà determinata dalla lunghezza della linea, 
		moltiplicata per l'indice del punto, mentre la y sarà
		generata casualmente tra l'altezza minima e l'altezza massima*/
		if (i == 0)
		{
			if (first_point.y > 0) {
				vertici_superficie_[i].position = sf::Vector2f(i * larghezza_finestra_ / NUMERO_DI_LINEE
					, first_point.y);
			}
			else {
				vertici_superficie_[i].position = sf::Vector2f(i * larghezza_finestra_ / NUMERO_DI_LINEE
					, altezza_minima_ - (rand() % (altezza_minima_ - altezza_massima_)));
			}
		}

		else {
			if (i == (vertici_superficie_.getVertexCount() - 1) && last_point.y > 0) {
				vertici_superficie_[i].position = sf::Vector2f(i * larghezza_finestra_ / NUMERO_DI_LINEE
					, last_point.y);
			}
			else {
				// Lo scarto viene utilizzato per consentire che la superficie sia più naturale possibile
				int scarto = 0;

				if (altezza_massima_ + range > vertici_superficie_[i - 1].position.y) {
					// In questo caso lo scarto sarà negativo
					scarto = altezza_massima_ - vertici_superficie_[i - 1].position.y;
				}
				else if (altezza_minima_ - range < vertici_superficie_[i - 1].position.y) {
					// In questo caso lo scarto sarà positivo
					scarto = altezza_minima_ - vertici_superficie_[i - 1].position.y;
				}

				int altezza_random = ((rand() % (range * 2 + 1)) - (range + scarto)) + vertici_superficie_[i - 1].position.y;

				if (altezza_random > altezza_minima_) altezza_random = altezza_minima_;
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
	for (int i = 0; i < NUMERO_DI_LINEE; i++)
		{
			superficie_[i].setPointCount(4);

			// Impostazione dei punti
			superficie_[i].setPoint(0, vertici_superficie_[i].position);
			superficie_[i].setPoint(1, vertici_superficie_[i + 1].position);
			superficie_[i].setPoint(2, sf::Vector2f(vertici_superficie_[i + 1].position.x, altezza_finestra_));
			superficie_[i].setPoint(3, sf::Vector2f(vertici_superficie_[i].position.x, altezza_finestra_));

			// Impostazione del colore della superficie
			superficie_[i].setFillColor(sf::Color::Color(0,100,0));
		}
}

void SuperficiePianeta::generaBunker()
{
	// Il numero di bunker sarà compreso tra 2 e 3
	//int numero_di_bunker = (rand() % 2) + 2;
	int numero_di_bunker = 3;
	
	// Viene generato un solo bunker da 3 proiettili per superficie
	int bunker_stronger = 1;
	/* Inizialmente viene scelta casualmente la posizione del bunker
	tra le linee 0 e (MAX - 1), dopo di che, se nella posizione non è presente
	nessun bunker (controllando il vettore di booleani), il bunker verrà generato
	nel punto medio. Nel caso la posizione scelta sia già occupata, verrà ripetuto il ciclo*/
	while (numero_di_bunker > 0) {
		int posizione_bunker = rand() % (NUMERO_DI_LINEE - 2) + 1;

		if (bunker_presenti_[posizione_bunker] == false) {
			if (!controllaOggettiVicinanze(posizione_bunker, 2)) {
				if (bunker_stronger > 0) {
					aggiungiOggetto(posizione_bunker, BUNKER_STRONGER, sf::Vector2f(50, 50));
					bunker_stronger--;
				}
				else {
					aggiungiOggetto(posizione_bunker, BUNKER, sf::Vector2f(50, 50)); // metodo per aggiungere il bunker alla struttura
				}
				numero_di_bunker--;
				// Posizione impostata a true, per indicare che adesso è occupata da un bunker
				bunker_presenti_[posizione_bunker] = true;
			}
		}
	}
}

bool SuperficiePianeta::controllaOggettiVicinanze(int posizione, int distanza)
{
	int startIndex = 0, finishIndex = NUMERO_DI_LINEE;
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

void SuperficiePianeta::aggiungiOggetto(int index, TipologiaOggetto tipoOggetto, sf::Vector2f dimensione)
{
	// Vettore che rappresenta la coppia (x,y)
	sf::Vector2f new_coordinate;
	float coordinate[2];
	
	/* Viene calcolato l'angolo tra i due punti. Per prima cosa deve essere
	calcolato il coefficiente_angolare, che poi viene utilizzato per calcolare 
	l'arcotangente, che restituisce l'angolo in radianti, trasformato poi in decimale.*/

	float coefficiente_angolare = (vertici_superficie_[index + 1].position.y - vertici_superficie_[index].position.y) /
		(vertici_superficie_[index + 1].position.x - vertici_superficie_[index].position.x);

	float angolo = (atan2f(vertici_superficie_[index + 1].position.y - vertici_superficie_[index].position.y, 
		vertici_superficie_[index + 1].position.x - vertici_superficie_[index].position.x) * 180 / PI);

	/* Generazione del punto di spawn del Bunker, con l'ascisse tra 0 e 31, in modo tale che la sprite non
	sia oltre la linea, dato che la posizione è riferita all'angolo in alto a destra. Per ottenere l'ordinata sarà
	prima ottenuta l'ordinata all'origine della linea, ed infine, tramite l'equazione della retta, si otterrà 
	il valore dell'ordinata*/
	float ordinata_origine = vertici_superficie_[index].position.y - vertici_superficie_[index].position.x * coefficiente_angolare;
	int offset = 15;

	coordinate[0] = rand() % ((int) dimensione.x) + offset + vertici_superficie_[index].position.x;
	coordinate[1] = coordinate[0] * coefficiente_angolare + ordinata_origine;

	new_coordinate.x = rand() % ((int) dimensione.x)+offset + vertici_superficie_[index].position.x;
	new_coordinate.y = new_coordinate.x * coefficiente_angolare + ordinata_origine;;

	if (tipoOggetto == BUNKER_STRONGER)
		inserisciNodoBunkerStronger(new_coordinate, angolo, dimensione);
	else if (tipoOggetto == BUNKER)
		inserisciNodoBunker(new_coordinate, angolo, dimensione);
	else {
		
		char tipologia[50];
		char texture[50];

		switch (tipoOggetto)
		{
		case BENZINA_BEST:
		{
			char stringa_oggetto[] = "BENZINA_BEST";
			char stringa_texture[] = "Texture/benzina_best_1.png";

			copiaStringa(tipologia, 50, stringa_oggetto);
			copiaStringa(texture, 50, stringa_texture);
		} break;
		case BENZINA:
		{
			char stringa_oggetto[] = "BENZINA";
			char stringa_texture[] = "Texture/benzina_1.png";

			copiaStringa(tipologia, 50, stringa_oggetto);
			copiaStringa(texture, 50, stringa_texture);
		} break;
		case CUORE:
		{
			char stringa_oggetto[] = "CUORE";
			char stringa_texture[] = "Texture/cuore_1.png";

			copiaStringa(tipologia, 50, stringa_oggetto);
			copiaStringa(texture, 50, stringa_texture);
		} break;
		default:
			break;
		}

		benzina_ = new oggetto(tipologia, texture, new_coordinate, angolo, dimensione);
	}
}

void SuperficiePianeta::inserisciNodoBunker(sf::Vector2f coordinate, float angolo, sf::Vector2f dimensione)
{
	float vita = 50;
	float danno = 12;

	Bunker *new_bunker = new Bunker(larghezza_finestra_, altezza_finestra_, vita, danno, "Texture/bunker_1.png", "Texture/bunker_1d.png", coordinate, dimensione, angolo);

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

void SuperficiePianeta::inserisciNodoBunkerStronger(sf::Vector2f coordinate, float angolo, sf::Vector2f dimensione)
{
	float vita = 70;
	float danno = 16;

	BunkerStronger *new_bunker = new BunkerStronger(larghezza_finestra_, altezza_finestra_, vita, danno, "Texture/bunker_s_1.png", "Texture/bunker_s_1d.png", coordinate, dimensione, angolo);

	if (bunker_ == nullptr) {
		bunker_stronger_ = new BunkerStrongerNode();
		bunker_stronger_->bunker_item = new_bunker;
		bunker_stronger_->next = nullptr;
	}
	else {
		bunker_stronger_ptr tmp = new BunkerStrongerNode();
		tmp->bunker_item = new_bunker;
		tmp->next = bunker_stronger_;
		bunker_stronger_ = tmp;
	}
}

void SuperficiePianeta::generaBenzina() {
	int tipologia_benzina = rand() % 100 + 1;
	sf::Vector2f size(30, 25);
	
	int index;
	bool found = false;
	while (!found)
	{
		index = rand() % (NUMERO_DI_LINEE - 2) + 1;
		if (!controllaOggettiVicinanze(index, 0)) {
			found = true;
		}
	}

	//da calcolare posizione e angolo

	if (tipologia_benzina > 30 && tipologia_benzina < 60) {
		aggiungiOggetto(index, BENZINA, size);
	}
	else if (tipologia_benzina >= 60 && tipologia_benzina < 85) {
		aggiungiOggetto(index, BENZINA_BEST, size);
	}
	else if (tipologia_benzina >= 85) {
		aggiungiOggetto(index, CUORE, size);
	}
}

void SuperficiePianeta::copiaStringa(char stringa[], int lunghezza, char stringa_da_copiare[])
{
	int i = 0;
	while (stringa_da_copiare[i] != '\0')
	{
		stringa[i] = stringa_da_copiare[i];
		i++;
	}
	stringa[i] = '\0';
}

void SuperficiePianeta::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (size_t i = 0; i < NUMERO_DI_LINEE; i++)
	{
		target.draw(superficie_[i]);
	}

	if (benzina_ != nullptr) {
		target.draw(*benzina_);
	}
	
	// Puntatore all'attuale struttura rappresentante i Bunker
	bunker_ptr bunker_to_print = bunker_;
	/* Vengono disegnati i Bunker finchè il puntatore
	alla struttura dei Bunker non sarà nullo */

	while (bunker_to_print != nullptr) {
		(*bunker_to_print->bunker_item).spara();
		(*bunker_to_print->bunker_item).aggiornaBarraVita();

		(*bunker_to_print->bunker_item).drawComportamento(target, states);
		target.draw(*bunker_to_print->bunker_item);

		bunker_to_print = bunker_to_print->next;
	}

	// Puntatore all'attuale struttura rappresentante i Bunker
	bunker_stronger_ptr bunker_stronger_to_print = bunker_stronger_;
	/* Vengono disegnati i Bunker finchè il puntatore
	alla struttura dei Bunker non sarà nullo */
	while (bunker_stronger_to_print != nullptr) {
		(*bunker_stronger_to_print->bunker_item).spara();
		(*bunker_stronger_to_print->bunker_item).aggiornaBarraVita();

		(*bunker_stronger_to_print->bunker_item).drawComportamento(target, states);
		target.draw(*bunker_stronger_to_print->bunker_item);

		bunker_stronger_to_print = bunker_stronger_to_print->next;
	}
}

SuperficiePianeta::SuperficiePianeta(unsigned int larghezza_finestra, unsigned altezza_finestra, sf::Vector2f primo_punto, sf::Vector2f ultimo_punto)
{
	larghezza_finestra_ = larghezza_finestra;
	altezza_finestra_ = altezza_finestra;

	/* L'altezza massima della superficie può essere
	il 30% dell'altezza della finestra*/
	altezza_massima_ = altezza_finestra_ * 0.70;

	altezza_minima_ = altezza_finestra * 0.90;

	/* Vengono impostate le proprietà relative
	al VertexArray delle linee della superficie,
	per poi richiamare il metodo che si occupa di impostare le coordinate
	dei punti delle linee */
	vertici_superficie_.setPrimitiveType(sf::LineStrip); // il tipo di primitiva che deve essere rappresentata
	vertici_superficie_.resize(NUMERO_DI_LINEE + 1); // il numero dei punti totali delle linee (num_linee + 1)
	generaVertici(primo_punto, ultimo_punto);

	/* Generazione della superficie a partire dai punti delle linee
	del VertexArray generate precedentemente */
	generaSuperficie();

	/* Il vettore di booleani rappresentante i bunker presenti
	viene impostato tutto a false */
	for (int i = 0; i < NUMERO_DI_LINEE; i++) bunker_presenti_[i] = false;
	bunker_ = nullptr;

	/* Metodo per generare i Bunker presenti sulla superficie */
	generaBunker();
	generaBenzina();
}

SuperficiePianeta::SuperficiePianeta(unsigned int larghezza_finestra, unsigned int altezza_finestra) :
	SuperficiePianeta(larghezza_finestra, altezza_finestra, sf::Vector2f(), sf::Vector2f()) {}

SuperficiePianeta::SuperficiePianeta() : SuperficiePianeta(1280, 720){}

sf::Vector2f SuperficiePianeta::getFirstVertex()
{
	return vertici_superficie_[0].position;
}

sf::Vector2f SuperficiePianeta::getLastVertex()
{
	return vertici_superficie_[vertici_superficie_.getVertexCount() - 1].position;
}

proiettile_ptr SuperficiePianeta::getProiettili()
{
	proiettile_ptr lista_proiettili = nullptr;
	
	bunker_ptr tmp_list = bunker_;
	
	while (tmp_list != nullptr)
	{
		proiettile_ptr tmp = (*tmp_list->bunker_item).getProiettili();

		if (tmp != nullptr) {
			proiettile_ptr tmp2 = tmp; // per scorrere la lista di proiettili ottenuta fino alla fine
			while (tmp2->next != nullptr)
			{
				tmp2 = tmp2->next;
			}

			tmp2->next = lista_proiettili; // il puntatore successivo della lista appena ottenuta è uguale ai proiettili già processati
			lista_proiettili = tmp;
		}

		tmp_list = tmp_list->next; // bunker successivo
	}

	bunker_stronger_ptr tmp_list2 = bunker_stronger_;

	while (tmp_list2 != nullptr)
	{
		proiettile_ptr tmp = (*tmp_list2->bunker_item).getProiettili();

		if (tmp != nullptr) {
			proiettile_ptr tmp2 = tmp; // per scorrere la lista di proiettili ottenuta fino alla fine
			while (tmp2->next != nullptr)
			{
				tmp2 = tmp2->next;
			}

			tmp2->next = lista_proiettili; // il puntatore successivo della lista appena ottenuta è uguale ai proiettili già processati
			lista_proiettili = tmp;
		}

		tmp_list2 = tmp_list2->next; // bunker successivo
	}

	return lista_proiettili;
}

void SuperficiePianeta::resetProiettiliBunker()
{
	bunker_ptr tmp_bunker = bunker_;

	while (tmp_bunker != nullptr)
	{
		(*tmp_bunker->bunker_item).resetProiettili();
		tmp_bunker = tmp_bunker->next;
	}

	bunker_stronger_ptr tmp_bunker_stronger = bunker_stronger_;

	while (tmp_bunker_stronger != nullptr)
	{
		(*tmp_bunker_stronger->bunker_item).resetProiettili();
		tmp_bunker_stronger = tmp_bunker_stronger->next;
	}
}

sf::VertexArray SuperficiePianeta::getPosizioneLineaSuperficie(sf::Vector2f posizione)
{
	sf::VertexArray pos_linea(sf::LineStrip, 2);

	bool found = false;
	int index = 0;
	int i = 0;
	while (!found && i < NUMERO_DI_LINEE)
	{
		if (posizione.x >= superficie_[i].getPoint(0).x && posizione.x <= superficie_[i].getPoint(1).x) {
			found = true;
			index = i;
		}
		i++;
	}

	pos_linea[0].position = superficie_[index].getPoint(0);
	pos_linea[1].position = superficie_[index].getPoint(1);

	return pos_linea;
}
bool SuperficiePianeta::controlloCollisioneSuperficie(sf::Vector2f pos)
{
	sf::VertexArray pos_linea = getPosizioneLineaSuperficie(pos);

	sf::Vector2f point_1 = pos_linea[0].position;
	sf::Vector2f point_2 = pos_linea[1].position;

	float coefficiente_angolare = (point_2.y - point_1.y) /
		(point_2.x - point_1.x);

	float ordinata_origine = point_1.y - point_1.x * coefficiente_angolare;

	float nave_y_retta = pos.x * coefficiente_angolare + ordinata_origine;

	return (nave_y_retta < pos.y);
}

void SuperficiePianeta::controlloProiettili(proiettile_ptr lista_proiettili)
{
	bunker_ptr tmp_bunker = bunker_;

	while (tmp_bunker != nullptr)
	{
		(*tmp_bunker->bunker_item).controlloProiettili(lista_proiettili);
		tmp_bunker = tmp_bunker->next;
	}

	bunker_stronger_ptr tmp_stronger_bunker = bunker_stronger_;

	while (tmp_stronger_bunker != nullptr)
	{
		(*tmp_stronger_bunker->bunker_item).controlloProiettili(lista_proiettili);
		tmp_stronger_bunker = tmp_stronger_bunker->next;
	}

}

int SuperficiePianeta::getNumeroBunker()
{
	int numero_bunker = 0;

	bunker_ptr tmp_bunker = bunker_;
	bunker_stronger_ptr tmp_bunker_stronger = bunker_stronger_;

	while (tmp_bunker != nullptr)
	{
		numero_bunker++;
		tmp_bunker = tmp_bunker->next;
	}

	while (tmp_bunker_stronger != nullptr)
	{
		numero_bunker++;
		tmp_bunker_stronger = tmp_bunker_stronger->next;
	}
	return numero_bunker;
}