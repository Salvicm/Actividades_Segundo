#pragma once
#include "button.h"
struct mouseController {
	int x, y;
	bool press;
	button *pressingButton = nullptr; 
	mouseController() : x(0), y(0), press(false){};
};
