#pragma once
#include "Types.h"

class Enemy
{
public:
	Enemy();
	Enemy(std::string _name, int _vit, int _def, int _atkDmg, float _atkFreq, int _defeatedExp, std::vector<weapons*> _weaponsList);

	~Enemy();

	std::string name;
	int vit;
	int atkDmg;
	int def;
	float atkFreq;
	int defeatedExp;
	std::vector<weapons*> weaponsList;
};