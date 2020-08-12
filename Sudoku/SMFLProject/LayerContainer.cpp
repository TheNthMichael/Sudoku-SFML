#include "LayerContainer.h"

/* Default Constructor
	Behavior:
*/
LayerContainer::LayerContainer()
{
	
}

/* Copy Constructor
	Behavior:
*/
LayerContainer::LayerContainer(LayerContainer& copy)
{
	std::vector<MyImage*> copy_layers = copy.getImageVector();
	for (auto& p : copy_layers) {
		this->layers.push_back(p);
	}
}


/* Move Container
	Behavior:
*/
LayerContainer::LayerContainer(LayerContainer&& reference) noexcept
{
	this->layers = reference.getImageVector();
}


/* Move Assignment Operator
	Behavior:
*/
LayerContainer& LayerContainer::operator=(LayerContainer&& reference_rhs) noexcept
{
	this->layers.clear();
	std::vector<MyImage*> copy_layers = reference_rhs.getImageVector();
	for (auto& p : copy_layers) {
		this->layers.push_back(p);
	}
	return *this;
}


/* Destructor
	Behavior:
*/
LayerContainer::~LayerContainer()
{

}

/* const std::vector<MyImage*>& LayerContainer::getImageVector(void) const
	Behavior returns a constant reference to the layers  - Used for copying data

*/
const std::vector<MyImage*>& LayerContainer::getImageVector(void) const
{
	return this->layers;
}


/*sf::Vector2f LayerContainer::getMaxSize(void) const
	Behavior: Returns the maximum width and height required to hold all images

*/
sf::Vector2f LayerContainer::getMaxSize(void) const
{
	return sf::Vector2f();
}


/* void LayerContainer::insert(MyImage& a, int priority)
	Behavior: if priority is the same as another image, it will be inserted at a lower priority
*/
void LayerContainer::insert(MyImage* a, int priority)
{
	if (priority >= this->layers.size()) {
		this->layers.push_back(a);
	}
	else {
		// Worried this might cause a out of bounds exception ->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Possible Error
		priority = (priority < 0) ? 0 : priority;
		// Inserts new element and shifts all other elements over by 1
		auto p = this->layers.begin() + priority;
		MyImage* tmp1, *tmp2 = *p;
		*p = a;
		while (p+1 != this->layers.end()) {
			tmp1 = *(p+1);
			*(p + 1) = tmp2;
			tmp2 = tmp1;
			p++;	// pointer
		}
		this->layers.push_back(tmp2);	// Need to increase space for next element
	}

}


/* sf::Image& LayerContainer::createRenderableImage(void)
 Behavior: Creates a rendereable image by merging layers in order of priority into one image;
 If I wanted to implement threads, I could merge 2 images on each thread, then merge the multiples of 2 and so on.
 But I'm lazy so O(n^2 * M) where M is the number of layers. 
 Technically it is O(n*m) but I consider image algorithms to always be n^2 by default since their size is usually massive.
*/
sf::Image LayerContainer::createRenderableImage(void)
{
	MyImage* blank = new MyImage(0,0,1800, 1800);
	for (std::vector<MyImage*>::reverse_iterator p = this->layers.rbegin(); p != this->layers.rend(); p++) {			// This may cause issues if the layer contains 0 images
		blank->mergeOnTop(*p);		// Last element contains renderable image
	}
	return blank->getImage();
}
