#pragma once

#include "includes.h"
#include <map>
#include "Button.h"



class SudokuMenu
{
private:
	std::map<Response, Button*> options;

public:
	SudokuMenu(sf::Font& font);

	Response selecting(sf::Event ev, sf::RenderWindow* window);
	void hover(sf::Event ev, sf::RenderWindow* window);

	void drawTo(sf::RenderWindow* window);

};

