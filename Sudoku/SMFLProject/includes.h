#pragma once
// SFML Includes - Look into precompiled headers **** precompiled headers speeds up the compile time
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "mathtools.h"
#include "TextBox.h"
#include "Button.h"


typedef enum Response { TO_QUIT, TO_MENU, TO_GAME, TO_NEWGAME, NONE };

typedef struct pair {
	int i;
	int j;
}PAIR;