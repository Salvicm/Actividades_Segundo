
#include "Enemy.h"
Enemy::Enemy()
{
}

Enemy::Enemy(std::string _name, int _vit, int _def, int _atkDmg,  float _atkFreq, int _defeatedExp,  std::vector<weapons*> _weaponsList) {
	name = _name;
	vit = _vit;
	def = _def;
	atkDmg = _atkDmg;
	atkFreq = _atkFreq;
	defeatedExp = _defeatedExp;
	weaponsList = _weaponsList;
};


Enemy::~Enemy()
{
}
