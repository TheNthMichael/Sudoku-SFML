#include "SudokuTile.h"


/*	void SudokuTile::inputLogic(int charTyped)
		inserts a character into the string stream
			(given that the key doesn't represent an action)
		action keys, so far only DELETE_KEY is used are handled by their own function
			(DELETE_KEY removes the last character in the stream given that the stream is not empty)
*/
void SudokuTile::inputLogic(int charTyped)
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
	textbox.setString(text.str() + "");
}


/*	void SudokuTile::deleteLastChar()
		deletes the last character in the stream
*/
void SudokuTile::deleteLastChar()
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

/***************************************************	PUBLIC	**********************************************************************/


/*	SudokuTile::SudokuTile()
		default constructor
*/
SudokuTile::SudokuTile()
{

}


/*	SudokuTile::SudokuTile(int charSize, sf::Font& font, sf::Vector2f size, sf::Color backgroundColor, sf::Color textColor, bool sel)
		Parameterized constructor
*/
SudokuTile::SudokuTile(int charSize, sf::Font& font, sf::Vector2f size, sf::Color backgroundColor, sf::Color textColor, bool sel, bool isSel)
{
	this->hasLimit = true;
	this->limit = 0;
	textbox.setFont(font);
	textbox.setCharacterSize(charSize);
	textbox.setFillColor(textColor);
	isSelected = sel;
	isSelectable = isSel;
	if (sel && isSel) {
		textbox.setString("");
	}
	else {
		textbox.setString("");
	}

	button.setSize(size);
	button.setFillColor(backgroundColor);
}


/*	void SudokuTile::setPosition(sf::Vector2f pos)
		sets the position of the top left corner of the tile, given a sf::Vector2f
*/
void SudokuTile::setPosition(sf::Vector2f pos)
{
	button.setPosition(pos);
	// center text
	float xPos = (pos.x + button.getGlobalBounds().width / 2) - (textbox.getLocalBounds().width / 2);
	float yPos = (pos.y + button.getGlobalBounds().height / 2) - (textbox.getLocalBounds().height / 2);
	textbox.setPosition({ xPos, yPos });
}

/*	void SudokuTile::setLimit(bool tof)
		enable/disable the character limit
*/
void SudokuTile::setLimit(bool tof)
{
	hasLimit = tof;
}


/*	void SudokuTile::setLimit(bool tof, int lim)
		sets the limit for the amount of characters a tile can contain
		enable/disable character limit
*/
void SudokuTile::setLimit(bool tof, int lim)
{
	hasLimit = tof;
	limit = lim - 1;
}


/*	void SudokuTile::setFont(sf::Font& font)
		changes the font used for Sudoku, 
			must be passed by reference 
			so ensure that the passed font 
			is kept in memory or the call stack
			while it is needed.
*/
void SudokuTile::setFont(sf::Font& font)
{
	textbox.setFont(font);
}


/*	void SudokuTile::setSelected(bool sel)
		enable/disable selection

*/
void SudokuTile::setSelected(bool sel)
{
	// change the look of the textbox to indicate its selected
	if (!isSelectable)
		return;
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

void SudokuTile::setIsSelectable(bool sel)
{
	this->isSelectable = sel;
}

bool SudokuTile::getIsSelectable()
{
	return isSelectable;
}


/*	std::string SudokuTile::getText()
		returns the string from the stream object
*/
std::string SudokuTile::getText()
{
	return text.str();
}

void SudokuTile::clearValue()
{
	text.str(std::string());
	text.clear();
	textbox.setString(text.str());
}


bool SudokuTile::getSelected()
{
	return isSelected;
}

void SudokuTile::typedOn(sf::Event input)
{
	if (isSelected && isSelectable) {
		std::cout << "Typing\n";
		int charTyped = input.text.unicode;
		if (charTyped < 128 && charTyped > '0' && charTyped <= '9' || charTyped == DELETE_KEY) {
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

void SudokuTile::setValue(int value)
{
	int charTyped = value;
	if (charTyped < 128 && charTyped > '0' && charTyped <= '9') {
		if (hasLimit) {
			if (hasLimit && text.str().length() <= limit) {
				inputLogic(charTyped);
			}
			else if (hasLimit && text.str().length() > limit&& charTyped == DELETE_KEY) {
				deleteLastChar();
			}
		}
		else {
			inputLogic(charTyped);
		}
	}
}

void SudokuTile::setString(std::string str)
{
	this->clearValue();
	for (auto& c : str) {
		this->setValue(c);
	}
}



/*	void SudokuTile::setBackColor(sf::Color color)
		sets the fillColor for the tile background
*/
void SudokuTile::setBackColor(sf::Color color)
{
	button.setFillColor(color);
	button.setOutlineColor(sf::Color::Black);
}


/*	void SudokuTile::setTextColor(sf::Color color)
		sets the fillColor for the tile background
*/
void SudokuTile::setTextColor(sf::Color color)
{
	textbox.setFillColor(color);
}


/*	void SudokuTile::drawTo(sf::RenderWindow* window)
		given a render window, draw the tile
*/
void SudokuTile::drawTo(sf::RenderWindow* window)
{
	window->draw(button);
	window->draw(textbox);
}


/*	bool SudokuTile::isMouseOver(sf::RenderWindow* window)
		check if the mouse relative to the window intersects
		with the tile.
*/
bool SudokuTile::isMouseOver(sf::RenderWindow* window)
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