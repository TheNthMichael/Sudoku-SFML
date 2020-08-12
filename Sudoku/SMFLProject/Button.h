#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Button
{
private:
	sf::RectangleShape button;
	sf::Text text;

public:
	Button();
	Button(std::string t, int charSize, sf::Vector2f size, sf::Color backgroundColor, sf::Color textColor);

	void setFont(sf::Font& font);
	void setBackColor(sf::Color color);
	void setTextColor(sf::Color color);
	void setPosition(sf::Vector2f pos);
	void drawTo(sf::RenderWindow* window);
	bool isMouseOver(sf::RenderWindow* window);

};

