#include <SFML/Graphics.hpp>
#include "universo.hpp";
#include "mappa.hpp";
#include <stdlib.h>   
#include <iostream>
#include <time.h>
using namespace sf;
using namespace std;
int main()
{
	int row = 18;
	int col = 24;
	srand(time(0));
	ContextSettings settings;
	settings.antialiasingLevel = 8;

	CircleShape nave(10);
	nave.setPointCount(4);


	RenderWindow window;
	window.create(VideoMode(1620, 910), "My window", Style::Default, settings);

	Vector2u size = window.getSize();
	unsigned int width = size.x;
	unsigned int height = size.y;


	window.clear(Color::Black);

	mappa m = mappa(3, width / 24, height / 18);


	nave.setPosition(width / 2, height / 2);
	nave.setFillColor(Color(255, 0, 0));
	cout << "\n\nCOORDINATE UNIVERSO: " << m.getPosizioneAttuale()->c.x << ", " << m.getPosizioneAttuale()->c.y << "\n\n";
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			cout << (*m.getPosizioneAttuale()->u).getMatriceSpawn(i, j) << " ";

		cout << "\n";
	}
	int r = 75; //su 75
	CircleShape sprite[6];
	for (int i = 0; i < (*m.getPosizioneAttuale()->u).getNumeroPianeti(); i++) {
		sprite[i] = CircleShape(r);
		sprite[i].setFillColor(Color(0, 255, 0));
		sprite[i].setPosition(0, 0);
		sprite[i].setPointCount(100);
	}
	int k = 0;
	int spx = 0;
	int spy = 0;
	for (int i = 0; i < row; i++)
	{
		spy += (*m.getPosizioneAttuale()->u).getDimensioniCelle().y / 2;
		for (int j = 0; j < col; j++)
		{
			spx += (*m.getPosizioneAttuale()->u).getDimensioniCelle().x / 2;
			if ((*m.getPosizioneAttuale()->u).getMatriceSpawn(i, j)) {
				cout << "\n" << spx << "  " << spy;

				sprite[k].setPosition(spx - r, spy - r);
				window.draw(sprite[k]);
				k++;
			}
			spx += (*m.getPosizioneAttuale()->u).getDimensioniCelle().x / 2;
		}
		spx = 0;
		spy += (*m.getPosizioneAttuale()->u).getDimensioniCelle().y / 2;
	}

	window.draw(nave);
	window.display();
	int velocita = 30;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.key.code == Keyboard::A)
			{
				nave.setPosition(nave.getPosition().x - velocita, nave.getPosition().y);
				if (nave.getPosition().x <= 0)
				{
					m.spostamento(3);
					nave.setPosition(width, nave.getPosition().y);
				}
			}
			if (event.key.code == Keyboard::D)
			{
				nave.setPosition(nave.getPosition().x + velocita, nave.getPosition().y);
				if (nave.getPosition().x >= width)
				{
					m.spostamento(1);
					nave.setPosition(0, nave.getPosition().y);
				}
			}
			if (event.key.code == Keyboard::W)
			{
				nave.setPosition(nave.getPosition().x, nave.getPosition().y - velocita);
				if (nave.getPosition().y <= 0)
				{
					m.spostamento(0);
					nave.setPosition(nave.getPosition().x, height);
				}
			}
			if (event.key.code == Keyboard::S)
			{
				nave.setPosition(nave.getPosition().x, nave.getPosition().y + velocita);
				if (nave.getPosition().y >= height)
				{
					m.spostamento(2);
					nave.setPosition(nave.getPosition().x, 0);
				}
			}
			cout << "\n\nCOORDINATE UNIVERSO: " << m.getPosizioneAttuale()->c.x << ", " << m.getPosizioneAttuale()->c.y << "\n\n";


			CircleShape sprite[6];
			for (int i = 0; i < (*m.getPosizioneAttuale()->u).getNumeroPianeti(); i++) {
				sprite[i] = CircleShape(r);
				sprite[i].setFillColor(Color(0, 255, 0));
				sprite[i].setPosition(0, 0);
				sprite[i].setPointCount(100);

			}
			window.clear(Color::Black);
			int k = 0;
			int spx = 0;
			int spy = 0;
			for (int i = 0; i < row; i++)
			{
				spy += (*m.getPosizioneAttuale()->u).getDimensioniCelle().y / 2;
				for (int j = 0; j < col; j++)
				{
					spx += (*m.getPosizioneAttuale()->u).getDimensioniCelle().x / 2;
					if ((*m.getPosizioneAttuale()->u).getMatriceSpawn(i, j)) {
						cout << "\n" << spx << "  " << spy;
						sprite[k].setPosition(spx - r, spy - r);
						window.draw(sprite[k]);
						k++;
					}
					spx += (*m.getPosizioneAttuale()->u).getDimensioniCelle().x / 2;
				}
				spx = 0;
				spy += (*m.getPosizioneAttuale()->u).getDimensioniCelle().y / 2;
			}

			window.draw(nave);
			window.display();
		}

	}
	return 0;
}