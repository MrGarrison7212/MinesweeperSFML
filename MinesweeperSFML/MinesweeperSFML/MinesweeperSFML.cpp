// MinesweeperSFML.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
	srand(time(0));

	sf::RenderWindow window(sf::VideoMode(400, 400), "Minesweeper baby!");


	//mines

	int w = 32;
	int grid[12][12];
	int sgrid[12][12];

	sf::Texture stuff;
	
	stuff.loadFromFile("Data/tiles.jpg");

	sf::Sprite mines(stuff);

	//adding fields and mines

	for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= 10; j++) {
			sgrid[i][j] = 10;
			if (rand() % 5 == 0) {
				grid[i][j] = 9;
			}
			else {
				grid[i][j] = 0;
			}
		}
	}
	//adding numbers based on distance from mines
	for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= 10; j++) {
			int n = 0;
			if (grid[i][j] == 9) continue;
			if (grid[i + 1][j] == 9) n++;
			if (grid[i][j + 1] == 9) n++;
			if (grid[i - 1][j] == 9) n++;
			if (grid[i][j - 1] == 9) n++;
			if (grid[i + 1][j + 1] == 9) n++;
			if (grid[i - 1][j - 1] == 9) n++;
			if (grid[i + 1][j - 1] == 9) n++;
			if (grid[i - 1][j + 1] == 9) n++;
			grid[i][j] = n;
		}
	}

	while (window.isOpen()) {

		sf::Vector2i position = sf::Mouse::getPosition(window);
		int x = position.x / w;
		int y = position.y / w;

		sf::Event e;
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				window.close();
			}
			//events, left&right mouseclick
			if (e.type == sf::Event::MouseButtonPressed) {
				if (e.key.code == sf::Mouse::Left) {
					sgrid[x][y] = grid[x][y];
				}
				else if (e.key.code == sf::Mouse::Right) {
					sgrid[x][y] = 11;
				}
			}

		}
		window.clear(sf::Color::White);
		for (int i = 1; i <= 10; i++) {
			for (int j = 1; j <= 10; j++) {
				if (sgrid[x][y] == 9) {
					sgrid[i][j] = grid[i][j];
				}
				mines.setTextureRect(sf::IntRect(sgrid[i][j]*w, 0, w, w));
				mines.setPosition(i*w, j*w);
				window.draw(mines);
			}
		}
		window.display();
	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
