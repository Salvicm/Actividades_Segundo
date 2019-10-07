#pragma once
#include "Interactible.h"
struct mouseController {
	int x, y;
	bool press;
	Interactible *pressingButton = nullptr;
	mouseController() : x(0), y(0), press(false){};
};

