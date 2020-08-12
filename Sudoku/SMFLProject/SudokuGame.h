#pragma once

#include "includes.h"
#include <vector>
#include <set>
#include <cstdlib>
#include <ctime>
#include "SudokuTile.h"
#include "Button.h"



class SudokuGame
{
private:
	std::vector<std::vector<SudokuTile*>> board;
	
	sf::Font font;
	Button btn_solve;
	int boardSize;
	int tileSize;
	int rowSel;
	int colSel;
	SudokuTile *selected;

	std::vector<PAIR> moveList;

	// private methods
	bool validMove(int row, int col);
	bool validSubmatrix(int startRow, int startCol);

	bool validMove(std::vector<std::vector<std::string>> tmpBoard, int r, int c);
	bool validSubmatrix(std::vector<std::vector<std::string>> tmpBoard, int r, int c);
	void createSet(std::vector<std::vector<std::string>> tmpBoard, int r, int c, std::set<std::string>& elements);
	std::string getRandomElement(std::set<std::string> elements);

	void randomBoard();
	std::vector<std::vector<std::string>> generateSimpleBoardCopy();

	bool boardFull();

	bool solve(int r, int c);
	bool solve(std::vector<std::vector<std::string>>& tmpBoard, int r, int c);

public:
	SudokuGame(sf::Font& font);
	SudokuGame(sf::Font& font, int numTiles);


	void hover(sf::Event ev, sf::RenderWindow* window);
	Response selecting(sf::Event ev, sf::RenderWindow* window);
	bool deselect();
	Response enteringText(sf::Event ev, sf::RenderWindow* window);

	void drawTo(sf::RenderWindow* window);

};



