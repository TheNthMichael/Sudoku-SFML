#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>


#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class TextBox
{
private:
	sf::Text textbox;
	std::ostringstream text;
	bool isSelected = false;
	bool hasLimit = false;
	int limit;

	// private methods
	void inputLogic(int charTyped);

	void deleteLastChar();

public:
	TextBox();
	TextBox(int size, sf::Color color, sf::Font& font, bool sel);

	void setFont(sf::Font& font);
	void setPosition(sf::Vector2f pos);
	void setLimit(bool tof);
	void setLimit(bool tof, int lim);
	void setSelected(bool sel);
	std::string getText();
	
	// render
	void drawTo(sf::RenderWindow* window);

	void typedOn(sf::Event input);





};

