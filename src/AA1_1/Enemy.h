#pragma once
#include "Types.h"
#include <vector>
#include <map>

class Enemy
{
public:
	Enemy();
	Enemy(int, int, int, int, int, std::string, std::vector<weapons>);

	~Enemy();

	std::string name;
	int vit;
	int atkDmg;
	int def;
	int atkFreq;
	int defeatedExp;
	std::vector<weapons> weaponsList;
};

void initializeEnemies(std::vector<Enemy> &enemies, int numEnemies, std::map<int, weapons> &weaponRegister, int numWeapons);
#pragma once
