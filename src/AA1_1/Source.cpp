#include <iostream>
#include <sstream>
#include <stdlib.h>
#pragma region XML
#include "../../dep/inc/XML/rapidxml.hpp"
#include "../../dep/inc/XML/rapidxml_iterators.hpp"
#include "../../dep/inc/XML/rapidxml_print.hpp"
#include "../../dep/inc/XML/rapidxml_utils.hpp"
#pragma endregion

#include "Enemy.h"
#include "Utils.h"

int main() {
	std::vector<Enemy> enemies;
	std::map<std::string, weapons> weaponIdentifier;
	utils::initWeapons(weaponIdentifier);
	utils::initEnemies(enemies, weaponIdentifier);
	utils::printEnemies(enemies);
	std::cout << "Hello";
	system("pause");
	return 0;
}

