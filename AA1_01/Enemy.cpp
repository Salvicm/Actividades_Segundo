
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

void initializeEnemies(std::vector<Enemy> &enemies, int numEnemies, std::map<int, weapons> &weaponRegister, int numWeapons) {
	std::vector<std::string> enemNames{
		"Luffy", "Zoro", "Nami", "Usopp", "Sanji", "Chopper", "Nico Robin", "Franky", "Brook"
	};

	std::vector<weapons> weaps;
	weapons newWeapon;
	int identifier;
	for (int i = 0; i < numEnemies; i++) {
		weaps.clear();
		for (int i = 0; i < numWeapons; i++) {
			identifier = rand() % 100000 + 1000;
			if (weaponRegister.count(identifier) != 0) {
				weaps.push_back(weaponRegister.at(identifier));
			}
			else {
				newWeapon = weapons{ rand() % 15 + 1, WeaponTypes(rand() % WeaponTypes::COUNTER) };
				weaps.push_back(newWeapon);
				weaponRegister.insert({ identifier, newWeapon });
			}
		}

		enemies.push_back(Enemy(rand() % 10, rand() % 10, rand() % 10, rand() % 10, rand() % 10,
			enemNames.at(rand() % enemNames.size()), weaps));
	}
}