#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class SudokuTile
{
private:
	sf::Text textbox;
	std::ostringstream text;
	sf::RectangleShape button;
	bool isSelected = false;
	bool hasLimit = false;
	bool isSelectable = true;
	int limit;

	// private methods
	void inputLogic(int charTyped);

	void deleteLastChar();

public:
	SudokuTile();
	SudokuTile(int charSize, sf::Font& font, sf::Vector2f size, sf::Color backgroundColor, sf::Color textColor, bool sel, bool isSel);

	void setPosition(sf::Vector2f pos);
	void setLimit(bool tof);
	void setLimit(bool tof, int lim);
	void setFont(sf::Font& font);
	void setSelected(bool sel);
	void setIsSelectable(bool sel);
	bool getIsSelectable();
	std::string getText();

	void clearValue();

	bool getSelected();

	void typedOn(sf::Event input);
	void setValue(int value);
	void setString(std::string str);

	void setBackColor(sf::Color color);
	void setTextColor(sf::Color color);
	void drawTo(sf::RenderWindow* window);
	bool isMouseOver(sf::RenderWindow* window);

};

