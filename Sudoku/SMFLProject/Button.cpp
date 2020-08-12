#include "Button.h"

Button::Button()
{
}

Button::Button(std::string t, int charSize, sf::Vector2f size, sf::Color backgroundColor, sf::Color textColor)
{
	text.setString(t);
	text.setFillColor(textColor);
	text.setCharacterSize(charSize);


	button.setSize(size);
	button.setFillColor(backgroundColor);
}

void Button::setFont(sf::Font& font)
{
	text.setFont(font);
}

void Button::setBackColor(sf::Color color)
{
	button.setFillColor(color);
}

void Button::setTextColor(sf::Color color)
{
	text.setFillColor(color);
}

void Button::setPosition(sf::Vector2f pos)
{
	button.setPosition(pos);
	// center text
	float xPos = (pos.x + (button.getLocalBounds().width / 2) - (text.getLocalBounds().width / 2) - (text.getCharacterSize() / text.getString().getSize() * 2));
	float yPos = (pos.y + (button.getLocalBounds().height / 2) - (text.getLocalBounds().height / 2) - (text.getCharacterSize() / 2));
	text.setPosition({ xPos, yPos });
}

void Button::drawTo(sf::RenderWindow* window)
{
	window->draw(button);
	window->draw(text);
}

bool Button::isMouseOver(sf::RenderWindow* window)
{
	float mouseX = sf::Mouse::getPosition(*window).x;
	float mouseY = sf::Mouse::getPosition(*window).y;

	float btnPosX = button.getPosition().x;
	float btnPosY = button.getPosition().y;

	float btnPosWidth = btnPosX + button.getLocalBounds().width;
	float btnPosHeight = btnPosY + button.getLocalBounds().height;

	return (mouseX < btnPosWidth && mouseX > btnPosX
			&& mouseY < btnPosHeight && mouseY > btnPosY);
}
