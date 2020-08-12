#include "Application.h"

/*
What do you want to do?

*/


int main() {
	

	// Init Application
	Application app;

	// Application Loop
	while (app.running()) {
		// Update
		app.update();
		// Render
		app.render();
	}


	// End of application 
	return 0;
}