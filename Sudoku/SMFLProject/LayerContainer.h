#pragma once
/* LayerContainer Class
Author: Michael Nickerson
Description: Class manages the order priority, rendering, and deleting of image references.
				Operations:
					bool insert(MyImage& ref, int priority);			-> Insert an image into the layer of its priority.
					bool delete(int layer_id);			-> Deletes a layer at a given id.
					sf::Texture render(MyImage& ref);	-> Combines layer into a single image to be rendered on the screen.
					bool CollapseDown(int i, int j);	-> Combines to layers (i & j) into one layer of default settings with pixel values directly overlayed in order of priority.
					bool CollapseAll(void);				-> Combines all layers into a single layer of default settings with pixel values directly overlayed in order of priority.


*/
#include <vector>
#include "includes.h"
#include "MyImage.h"

class LayerContainer
{
private:
	// Reference by address to increase the speed of layer operations
	std::vector<MyImage*> layers;


public:
	LayerContainer();
	LayerContainer(LayerContainer& copy);
	explicit LayerContainer(LayerContainer&& reference) noexcept;
	LayerContainer& operator=(LayerContainer&& reference_rhs) noexcept;
	~LayerContainer();
	// Accessors ang Mutators
	const std::vector<MyImage*>& getImageVector(void) const;
	sf::Vector2f getMaxSize(void) const;

	// Methods
	void insert(MyImage* a, int priority);
	sf::Image createRenderableImage(void);
};

