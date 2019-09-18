#pragma once
#include "Types.h"

class Enemy
{
public:
	Enemy();
	Enemy(std::string _name, int _vit, int _def, float _atkDmg, int _atkFreq, int _defeatedExp, std::vector<weapons> _weaponsList);

	~Enemy();

	std::string name;
	int vit;
	float atkDmg;
	int def;
	int atkFreq;
	int defeatedExp;
	std::vector<weapons> weaponsList;
};

void initializeEnemies(std::vector<Enemy> &enemies, int numEnemies, std::map<int, weapons> &weaponRegister, int numWeapons);
#pragma once
