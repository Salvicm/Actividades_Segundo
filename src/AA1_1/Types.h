#pragma once
const int NUMBERENEMIES = 5, NUMBERWEAPONS = 2;
#include <string>


struct weapons {
	int range;
	std::string identifier;
	std::string type;
	/*weapons(int _range , WeaponTypes _type) {
		range = _range;
		type = _type;
	}*/
};