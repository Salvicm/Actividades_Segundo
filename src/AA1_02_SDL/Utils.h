#pragma once
#include "Button.h"
struct mouseController {
	int x, y;
	bool press;
	Button *pressingButton = nullptr; 
	mouseController() : x(0), y(0), press(false){};
};
