#pragma once

#include "includes.h"
#include "SudokuGame.h"
#include "SudokuMenu.h"

typedef enum State {QUIT, MENU, GAME, NEWGAME};


class SudokuGameManager
{
private:
	SudokuGame* game;
	SudokuMenu* menu;
	State state;
	sf::Font font;
	int boardSize;

public:
	SudokuGameManager(sf::Font& font);
	SudokuGameManager(sf::Font& font, int boardSize);

	Response handleEvent(sf::Event ev, sf::RenderWindow* window);

	Response stateTransition(Response res);

	void drawTo(sf::RenderWindow* window);

};

