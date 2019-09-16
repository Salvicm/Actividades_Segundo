#pragma once
#include "Types.h"
#include <vector>
#include <string>

class Enemy
{
public:
	Enemy();
	Enemy(int, int, int, int, int, std::string, std::vector<weapons>);

	~Enemy();
private: 
	std::string name;
	int vit;
	int atkDmg;
	int def;
	int atkFreq;
	int defeatedExp;
	std::vector<weapons> weaponsList;
};

void initializeEnemies(std::vector<Enemy> enemies, int numEnemies, int numWeapons);
