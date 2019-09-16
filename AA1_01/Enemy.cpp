
#include "Enemy.h"
Enemy::Enemy() 
{
}

Enemy::Enemy(int _vit, int _atkDmg, int _def, int _atkFreq, int _defeatedExp, std::string _name, std::vector<weapons> _weaponsList) {
	vit = _vit;
	atkDmg = _atkDmg;
	atkFreq = _atkFreq;
	defeatedExp = _defeatedExp;
	name = _name;
	weaponsList = _weaponsList;
};


Enemy::~Enemy()
{
}

void initializeEnemies(std::vector<Enemy> enemies, int numEnemies, int numWeapons) {
	std::vector<std::string> enemNames{
		"Luffy", "Zoro", "Nami", "Usopp", "Sanji", "Chopper", "Nico Robin", "Franky", "Brook"
	};

	std::vector<weapons> weaps;
	for (int i = 0; i < numWeapons; i++) {
		weaps.push_back(weapons(rand() % 1000, rand() % 15));
	}

	for (int i = 0; i < numEnemies; i++) {
		enemies.push_back(Enemy(rand() % 10, rand() % 10, rand() % 10, rand() % 10, rand() % 10,
			enemNames.at(rand() % enemNames.size()), weaps));
	}
}