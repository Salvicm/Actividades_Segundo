#pragma once
#include "Constantes.h"
#include <string>

struct keyboardInputs {
	bool ESC_KEY = false;
	bool MUTE_KEY = false;
	void clean() {
		ESC_KEY = false;
		MUTE_KEY = false;
	}
};
struct vec2 {
	int x, y;
};
struct rect_util {
	int x, y, w, h;
};
struct mouseController {
	vec2 position;
	bool pressUp;
	bool pressDown;
	std::string pressedButton = NO_BUTTON;
	mouseController() : position{ 0, 0 }, pressUp(false), pressDown(false){};
};
struct timeController {
};