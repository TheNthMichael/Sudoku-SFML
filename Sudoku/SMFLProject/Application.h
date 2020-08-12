#pragma once
#include "includes.h"
#include "SudokuGameManager.h"

/* class Application

 #### Wrapper class for all application functions


*/

class Application
{
private:
	// Var
	// Window
	sf::RenderWindow* window;		// Store a reference to the window for easy access
	sf::VideoMode videoMode;
	sf::Event ev;
	std::map<std::string, sf::Font> fonts;

	// Private Methods
	void initializeVar();
	void initWindow();
	void initFonts();
	void initGameManager();

	// Game Objects
	SudokuGameManager* gameManager;


public:
	// Default Constructor and Destructor
	Application();
	virtual ~Application();

	// Mutators and Accessors
	const bool running() const;

	// Public Methods
	void pollEvents();
	void update();
	void render();

};

