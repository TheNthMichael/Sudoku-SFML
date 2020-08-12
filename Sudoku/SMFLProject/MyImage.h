#pragma once
/* Class that inherits the Image class
	Reference (x,y) pixel values by using: 		index = (((y * this->size_x) - y) + (x)) * 4;



*/
#include "includes.h"
class MyImage 
{
private:
	// storing an array of pixel values, operate on this and only create a new image when needed from the pixel values
	sf::Uint8* pixels;
	sf::Vector2i position;
	sf::Vector2u size;
	sf::Image im;

public:
	// Constructors & Destructor
	MyImage(void);
	MyImage(int pos_x, int pos_y, std::string path);
	MyImage(int pos_x, int pos_y, int size_x, int size_y);
	MyImage(MyImage& copy);
	~MyImage(void);

	// Accessors and Mutators
	sf::Image getImage(void);
	void setImage(sf::Image*);
	sf::Vector2u getSize(void) const;
	void setSize(sf::Vector2u);
	sf::Vector2i getPosition(void) const;
	void setPosition(sf::Vector2i);

	// Methods
	void setOpacity(sf::Uint8 value);
	void setColorOpacity(sf::Uint8 R, sf::Uint8 G, sf::Uint8 B, sf::Uint8 value);
	void mergeOnTop(MyImage* reference);

};

