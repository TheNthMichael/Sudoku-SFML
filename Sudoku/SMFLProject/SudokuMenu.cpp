#include "SudokuMenu.h"

SudokuMenu::SudokuMenu(sf::Font& font)
{
	options[TO_GAME] = new Button("Start", 20, { 100, 50 }, sf::Color(175, 175, 175), sf::Color::White);
	options[TO_GAME]->setPosition({250, 200});
	options[TO_GAME]->setFont(font);

	options[TO_QUIT] = new Button("Quit", 20, { 100, 50 }, sf::Color::Red, sf::Color::White);
	options[TO_QUIT]->setPosition({250, 350});
	options[TO_QUIT]->setFont(font);
}

Response SudokuMenu::selecting(sf::Event ev, sf::RenderWindow* window)
{
	Response res = NONE;
	for (auto& p : options) {
		if (p.second->isMouseOver(window)) {
			res = p.first;
		}
	}
	return res;
}

void SudokuMenu::hover(sf::Event ev, sf::RenderWindow* window)
{
	for (auto& p : options) {
		if (p.second->isMouseOver(window)) {
			if (p.first == TO_QUIT) {
				p.second->setBackColor(sf::Color::Red);
			}
			else {
				p.second->setBackColor(sf::Color(140, 140, 140));
			}
		}
		else {
			p.second->setBackColor(sf::Color(175, 175, 175));
		}
	}
}

void SudokuMenu::drawTo(sf::RenderWindow* window)
{
	for (auto& p : options) {
		p.second->drawTo(window);
	}
}
