#include "MyImage.h"

/* Default Constructor
	Behavior:
*/
MyImage::MyImage(void)
{
	this->size.x = 100;
	this->size.y = 100;
	this->pixels = new sf::Uint8[size.x * size.y * 4];
	unsigned int index(0);
	for (unsigned int y = 0; y < size.y; y++) {
		for (unsigned int x = 0; x < size.x; x++) {
			index = (((y * size.x) - y) + (x)) * 4;
			this->pixels[index] = 255;	// Red
			this->pixels[index + 1] = 255;	// Green
			this->pixels[index + 2] = 255;	// Blue
			this->pixels[index + 3] = 0;	// Alpha
		}
	}
}

/* Constructor from File
	Behavior:
*/
MyImage::MyImage(int pos_x, int pos_y, std::string path)
{
	this->position.x = pos_x;
	this->position.y = pos_y;
	auto err = this->im.loadFromFile(path);		// Create a default image of the given size;
	if (!err) {
		std::cout << "Failed to open " << path << std::endl << "Creating default image instead...." << std::endl;
		// Create Default image on failure
		this->size.x = 100;
		this->size.y = 100;
		this->pixels = new sf::Uint8[size.x * size.y * 4];
		int index(0);
		for (unsigned int y = 0; y < size.y; y++) {
			for (unsigned int x = 0; x < size.x; x++) {
				index = (((y * size.x) - y) + (x)) * 4;
				this->pixels[index] = 0;	// Red
				this->pixels[index + 1] = 0;	// Green
				this->pixels[index + 2] = 0;	// Blue
				this->pixels[index + 3] = 255;	// Alpha
			}
		}
	}
	else {
		this->size.x = this->im.getSize().x;
		this->size.y = this->im.getSize().y;
		this->pixels = new sf::Uint8[this->size.x * this->size.y * 4];
		const sf::Uint8* pixels_const = this->im.getPixelsPtr();
		unsigned int index(0);
		for (unsigned int y = 0; y < this->size.y; y++) {
			for (unsigned int x = 0; x < this->size.x; x++) {
				index = (((y * this->size.x) - y) + (x)) * 4;
				this->pixels[index] = pixels_const[index];	// Red
				this->pixels[index + 1] = pixels_const[index + 1];	// Green
				this->pixels[index + 2] = pixels_const[index + 2];	// Blue
				this->pixels[index + 3] = pixels_const[index + 3];	// Alpha
			}
		}
	}
}

/* Constructor from dimensions
	Behavior:
*/
MyImage::MyImage(int pos_x, int pos_y, int size_x, int size_y)
{
	this->size.x = size_x;
	this->size.y = size_y;
	this->position.x = pos_x;
	this->position.y = pos_y;
	this->pixels = new sf::Uint8[size.x * size.y * 4];
	unsigned int index(0);
	for (unsigned int y = 0; y < size.y; y++) {
		for (unsigned int x = 0; x < size.x; x++) {
			index = (((y * size.x) - y) + (x)) * 4;
			this->pixels[index] = 0;	// Red
			this->pixels[index + 1] = 0;	// Green
			this->pixels[index + 2] = 0;	// Blue
			this->pixels[index + 3] = 255;	// Alpha
		}
	}
	this->im.create(size.x, size.y, this->pixels);
}


/* Copy Constructor
	Behavior: Creates a new image of the same pixel values
*/
MyImage::MyImage(MyImage& copy)
{
	this->size = copy.size;
	this->position = copy.position;
	this->pixels = new sf::Uint8[this->size.x * this->size.y * 4];
	unsigned int index(0);
	for (unsigned int y = 0; y < this->size.y; y++) {
		for (unsigned int x = 0; x < this->size.x; x++) {
			index = (((y * this->size.x) - y) + (x)) * 4;
			this->pixels[index] = copy.pixels[index];	// Red
			this->pixels[index + 1] = copy.pixels[index + 1];	// Green
			this->pixels[index + 2] = copy.pixels[index + 2];	// Blue
			this->pixels[index + 3] = copy.pixels[index + 3];	// Alpha
		}
	}
	this->im.create(this->size.x, this->size.y, this->pixels);
}

/* Destructor
	Behavior:
*/
MyImage::~MyImage(void)
{
	delete[] this->pixels;		// Careful with references, if the image obj holds a reference to this and it is deleted first or after it may cause a problem
}

/* sf::Image MyImage::getImage(void) const
	Behavior: returns an sf::image, calls sf::image method create(int,int,sf::Uint8*)

*/
sf::Image MyImage::getImage(void)
{
	this->im.create(this->size.x, this->size.y, this->pixels);
	return this->im;
}


/* void MyImage::setImage(sf::Image)
	Behavior: sets an sf::image, calls sf::image method create(int,int,sf::Uint8*)

*/
void MyImage::setImage(sf::Image* new_im)
{
	delete[] this->pixels;
	this->size = new_im->getSize();
	this->pixels = new sf::Uint8[this->size.x * this->size.y * 4];
	const sf::Uint8* pixels_const = new_im->getPixelsPtr();
	unsigned int index(0);
	for (int y = 0; y < this->size.y; y++) {
		for (int x = 0; x < this->size.x; x++) {
			index = (((y * this->size.x) - y) + (x)) * 4;
			this->pixels[index] = pixels_const[index];	// Red
			this->pixels[index + 1] = pixels_const[index + 1];	// Green
			this->pixels[index + 2] = pixels_const[index + 2];	// Blue
			this->pixels[index + 3] = pixels_const[index + 3];	// Alpha
		}
	}
}

sf::Vector2u MyImage::getSize(void) const
{
	return this->size;
}

void MyImage::setSize(sf::Vector2u new_size)
{
	this->size = new_size;
}

sf::Vector2i MyImage::getPosition(void) const
{
	return this->position;
}

void MyImage::setPosition(sf::Vector2i new_pos)
{
	this->position = new_pos;
}

/* void MyImage::setOpacity(sf::Uint8 value)
	Behavior: sets the image opacity to a specific value

*/
void MyImage::setOpacity(sf::Uint8 value)
{
	unsigned int index(0);
	for (unsigned int y = 0; y < size.y; y++) {
		for (unsigned int x = 0; x < size.x; x++) {
			index = (((y * size.x) - y) + (x)) * 4;
			this->pixels[index + 3] = value;	// Alpha
		}
	}
}


/* void MyImage::setColorOpacity(sf::Uint8 R, sf::Uint8 G, sf::Uint8 B, sf::Uint8 value)
	Behavior:

*/
void MyImage::setColorOpacity(sf::Uint8 R, sf::Uint8 G, sf::Uint8 B, sf::Uint8 value)
{
	unsigned int index(0);
	for (unsigned int y = 0; y < size.y; y++) {
		for (unsigned int x = 0; x < size.x; x++) {
			index = (((y * size.x) - y) + (x)) * 4;
			if (pixels[index] == R && pixels[index + 1] == G && pixels[index + 2] == B) {
				this->pixels[index + 3] = value;	// Alpha
			}
		}
	}
}


/* void MyImage::mergeOnTop(MyImage* reference)
	Behavior: Merges the referenced image on top of the current image.

	equation for overlaying pixels with varying opacities:
	Source: https://wikimedia.org/api/rest_v1/media/math/render/svg/a92cffa85057fafdd90b31202ce44690958b8cb9
	a_k = 1 - (1 - t.a) * (1 - r.a)
	a_k != 0:		c_k = t.a * t.p + (1 - t.a)*r.a*r.p / a_k
	else:			c_k = 0

*/
void MyImage::mergeOnTop(MyImage* reference)
{
	// First, is there any intersection?
	sf::Vector2i p_left(max(this->position.x, reference->position.x), max(this->position.y + this->size.y, reference->position.y + reference->size.y));
	sf::Vector2i p_right(min(this->position.x+this->size.x, reference->position.x+reference->size.x), min(this->position.y, reference->position.y));
	if (p_left.x > p_right.x || p_left.y > p_right.y) {
		std::cout << "lx: " << p_left.x << " ly: " << p_left.y << " rx: ";
		std::cout << "no intersection found\n";
		return;
	}
					// No intersection was found
	std::cout << "here\n";
	if (reference == nullptr) {
		std::cout << "nullptr passed in merge\n";
		return;
	}
		
	auto p = reference->pixels;
	sf::Uint8 a_k;

	float ta(0), ra(0);

	int index1(0), index2(0);
	for (int y = p_right.y; y < p_left.y; y++) {
		for (int x = p_left.x; x < p_right.x; x++) {
			index1 = (((y * this->size.x) - y) + (x)) * 4;
			index2 = (((y * reference->size.x) - y) + (x)) * 4;
			ta = map(pixels[index1 + 3], 0, 255, 0, 1);
			ra = map(p[index2 + 3], 0, 255, 0, 1);
			a_k = 1.0 - (1.0 - ta) * (1.0 - ra);
			if (a_k != 0) {
				/*
				this->pixels[index1] = static_cast<sf::Uint8>(ta * this->pixels[index1] + (1.0 - ta) * ra * p[index2] / a_k);
				this->pixels[index1+1] = static_cast<sf::Uint8>(ta * this->pixels[index1+1] + (1.0 - ta) * ra * p[index2+1] / a_k);
				this->pixels[index1+2] = static_cast<sf::Uint8>(ta * this->pixels[index1+2] + (1.0 - ta) * ra * p[index2+2] / a_k);
				this->pixels[index1 + 3] = static_cast<sf::Uint8>(a_k);
				*/
				std::cout << ta * static_cast<double>(this->pixels[index1]) + (1.0 - ta) * ra * p[index2] / a_k << "\n";
				std::cout << ta * static_cast<double>(this->pixels[index1 + 1]) + (1.0 - ta) * ra * p[index2 + 1] / a_k << "\n";
				std::cout << ta * static_cast<double>(this->pixels[index1 + 2]) + (1.0 - ta) * ra * p[index2 + 2] / a_k << "\n";
				std::cout << a_k << "\n";
			}
		}
	}
}
