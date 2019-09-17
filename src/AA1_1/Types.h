#pragma once
const int NUMBERENEMIES = 5, NUMBERWEAPONS = 2;
enum WeaponTypes {
	CUTLASS, SMALLSWORD, MUSKET, AXE, BOW, FLAIL, COUNTER
};

struct weapons {
	int range;
	WeaponTypes type;

	/*weapons(int _range , WeaponTypes _type) {
		range = _range;
		type = _type;
	}*/
};

#pragma once
