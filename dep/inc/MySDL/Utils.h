#pragma once
#include "Types.h"


namespace Utils {
	static bool checkPointColision(vec2 point, rect_util _rect) {
		if (point.x >= _rect.x && point.x <= _rect.x + _rect.w) {
			// If mousePos Y
			if (point.y >= _rect.y && point.y <= _rect.y + _rect.h) {
				return true;
			}
		}
		return false;
	};

	static bool checkRectColision(rect_util rectA, rect_util rectB) {	
		if(checkPointColision({ rectA.x + rectA.w, rectA.y }, rectB))
			return true;
		else if(checkPointColision({ rectA.x + rectA.w, rectA.y + rectA.h }, rectB))
			return true;
		else if(checkPointColision({ rectA.x, rectA.y }, rectB))
			return true;
		else if(checkPointColision({ rectA.x, rectA.y + rectA.h }, rectB))
			return true;
		else 
			return false;
	}

	static bool checkWallColision(rect_util rectA, rect_util rectB) {
		// TODO
		return true;
	}

	static float lerp(float lerpSizeController, float min, float max) {
		float result = (min * (1.0 - lerpSizeController)) + (max * lerpSizeController);
		return result;
	}

}