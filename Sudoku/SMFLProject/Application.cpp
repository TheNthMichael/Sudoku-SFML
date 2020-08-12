#include "Application.h"
// ########### Private Methods

void Application::initializeVar()
{
	this->window = nullptr;
}

void Application::initWindow() 
{
	// Set window size
	this->videoMode.width = 800;
	this->videoMode.height = 600;
	// this->videoMode.getDesktopMode()  => Use to dynamically set the window to your screens size
	this->window = new sf::RenderWindow(this->videoMode, "Sudoku", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Application::initFonts()
{
	sf::Font arial;
	arial.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");
	fonts["Arial"] = arial;
}

void Application::initGameManager()
{
	this->gameManager = new SudokuGameManager(fonts["Arial"]);
}


// ########### Public Methods

// Default Constructor
Application::Application() {
	this->initializeVar();
	this->initWindow();
	// must init fonts before any gameobjects that require fonts.
	this->initFonts();
	this->initGameManager();
}

// Destructor
Application::~Application() {
	delete this->window;
}

// Mutators and Accessors
const bool Application::running() const
{
	return this->window->isOpen();
}

// Functions


void Application::pollEvents()
{

	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		textbox.setSelected(true);
	}*/
	/*else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		textbox.setSelected(false);
	}*/

	Response res = NONE;

	while (this->window->pollEvent(this->ev)) {
		switch (this->ev.type) {
			case sf::Event::Closed:
				this->window->close();
				break;
			default:
				res = this->gameManager->handleEvent(ev, window);
				break;
		}
		if (res == TO_QUIT) {
			this->window->close();
		}
	}
}

// Updates the application state every frame
void Application::update()
{
	this->pollEvents();

	// Relative to screen
	// std::cout << "Mouse Position: " << sf::Mouse::getPosition().x << ", " << sf::Mouse::getPosition().y << std::endl;

	// Relative to window

	// Move Block
	//float x = sf::Mouse::getPosition(*this->window).x - (this->block.getSize().x * this->block.getScale().x / 2);
	//float y = sf::Mouse::getPosition(*this->window).y - (this->block.getSize().y * this->block.getScale().y / 2);
	//this->block.setPosition(sf::Vector2f(x,y));
	//std::cout << "Mouse Position: " << sf::Mouse::getPosition(*this->window).x << ", " << sf::Mouse::getPosition(*this->window).y << std::endl;

}

/*
	@return void

	 - clear old frame
	 - render new objects
	 - display to window
	Renders the application
	*/
void Application::render()
{
	this->window->clear(sf::Color(255, 255, 255, 0));
	
	// Add GameObjects Here
	this->gameManager->drawTo(this->window);
		

	this->window->display();
}
