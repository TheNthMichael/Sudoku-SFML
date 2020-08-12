#include "SudokuGameManager.h"


SudokuGameManager::SudokuGameManager(sf::Font& font)
{
	this->font = font;
	this->state = MENU;
	this->menu = new SudokuMenu(this->font);
	this->boardSize = 9;
}

SudokuGameManager::SudokuGameManager(sf::Font& font, int boardSize)
{
	this->font = font;
	this->state = MENU;
	this->menu = new SudokuMenu(this->font);
	this->boardSize = boardSize;
}

Response SudokuGameManager::handleEvent(sf::Event ev, sf::RenderWindow* window)
{
	Response res = NONE;

	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		if (state == GAME) {
			this->game->deselect();
			return res;
		}
	}
	*/
	switch (ev.type) {
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape)
				window->close();
			break;
		case sf::Event::TextEntered:
			// text input event
			/*
				Search for which tile is selected
			*/
			std::cout << "entering text: " << static_cast<char>(ev.text.unicode) << std::endl;
			if (state == GAME) {
				res = game->enteringText(ev, window);
			}
			break;
		case sf::Event::MouseMoved:
			// hover event
			if (state == GAME) {
				this->game->hover(ev, window);
			}
			else if (state == MENU) {
				this->menu->hover(ev, window);
			}
			break;
		case sf::Event::MouseButtonPressed:
			// click event
			if (state == GAME) {
				res = this->game->selecting(ev, window);
			}
			else if (state == MENU) {
				res = this->menu->selecting(ev, window);
			}
			break;
	}
	return this->stateTransition(res);
}

Response SudokuGameManager::stateTransition(Response res)
{
	switch (res) {
		case TO_GAME:
			if (state == MENU) {
				delete this->menu;
				this->state = GAME;
				this->game = new SudokuGame(this->font);
			}
			return NONE;
		case TO_MENU:
			if (state == GAME) {
				delete this->game;
				this->state = MENU;
				this->menu = new SudokuMenu(this->font);
			}
			return NONE;
		default:
			return res;
	}
}

void SudokuGameManager::drawTo(sf::RenderWindow* window)
{
	switch (state) {
		case QUIT:
			std::cout << "Quitting...\n";
			break;
		case MENU:
			std::cout << "------Menu\n";
			menu->drawTo(window);
			break;
		case NEWGAME:
			std::cout << "------NewGame\n";
			break;
		case GAME:
			std::cout << "------Game\n";
			this->game->drawTo(window);
			break;
		default:
			std::cout << "default case triggered in SudokuGameManager::drawTo\n";
			break;
	}
}
