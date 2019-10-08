#pragma once

struct keyboardInputs{ 
	bool ESC_KEY = false;
	void clean() {
		ESC_KEY = false;
	}
};
struct vec2 {
	int x, y;
};
struct rect_util {
	int x, y;
	int h, w;
};



static bool checkMouseColision(vec2 mousePos, rect_util _rect) {
	if (mousePos.x >= _rect.x && mousePos.x <= _rect.x + _rect.w) {
		// If mousePos Y
		if (mousePos.y >= _rect.y && mousePos.y <= _rect.y + _rect.h) {
			return true;
		}
	}
	return false;
};

static bool checkRectColision(rect_util rectA, rect_util rectB) {
	return true;
}
static bool checkWallColision(rect_util rectA, rect_util rectB) {
	return true;
}
static float lerp() {
	return 10.0f;
}
