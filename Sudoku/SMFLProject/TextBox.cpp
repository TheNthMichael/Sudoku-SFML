#include "TextBox.h"

void TextBox::inputLogic(int charTyped)
{
	if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY) {
		text << static_cast<char>(charTyped);
	}
	else if (charTyped == DELETE_KEY) {
		if (text.str().length() > 0) {
			deleteLastChar();
		}
	}
	// display text and a cursor indicator
	textbox.setString(text.str() + "_");
}

void TextBox::deleteLastChar()
{
	std::string t = text.str();
	std::string newT = "";
	// Copy every character except for the last
	for (int i = 0; i < t.length() - 1; i++) {
		newT += t[i];
	}
	text.str("");
	text << newT;

	textbox.setString(text.str());
}

TextBox::TextBox()
{
}

TextBox::TextBox(int size, sf::Color color, sf::Font& font, bool sel)
{
	textbox.setFont(font);
	textbox.setCharacterSize(size);
	textbox.setFillColor(color);
	isSelected = sel;
	if (sel) {
		textbox.setString("_");
	}
	else {
		textbox.setString("");
	}
}

void TextBox::setFont(sf::Font& font)
{
	textbox.setFont(font);
}

void TextBox::setPosition(sf::Vector2f pos)
{
	textbox.setPosition(pos);
}

void TextBox::setLimit(bool tof)
{
	hasLimit = tof;
}

void TextBox::setLimit(bool tof, int lim)
{
	hasLimit = tof;
	limit = lim - 1;
}

void TextBox::setSelected(bool sel)
{
	// change the look of the textbox to indicate its selected
	isSelected = sel;
	if (!sel) {
		std::string t = text.str();
		std::string newT = "";
		// Copy every character except for the last
		for (int i = 0; i < t.length(); i++) {
			newT += t[i];
		}
		textbox.setString(newT);
	}
}

std::string TextBox::getText()
{
	return text.str();
}

void TextBox::drawTo(sf::RenderWindow* window)
{
	window->draw(textbox);
}

void TextBox::typedOn(sf::Event input)
{
	if (isSelected) {
		int charTyped = input.text.unicode;
		if (charTyped < 128) {
			if (hasLimit) {
				if (hasLimit && text.str().length() <= limit) {
					inputLogic(charTyped);
				}
				else if (hasLimit && text.str().length() > limit && charTyped == DELETE_KEY) {
					deleteLastChar();
				}
			}
			else {
				inputLogic(charTyped);
			}
		}
	}
}
