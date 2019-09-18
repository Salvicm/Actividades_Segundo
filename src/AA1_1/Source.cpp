#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
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
	srand(time(NULL));
	std::vector<Enemy> enemies;
	std::map<std::string, weapons> weaponIdentifier;
	utils::initWeapons(weaponIdentifier);
	utils::initEnemies(enemies, weaponIdentifier);
	utils::printEnemies(enemies);
	
	system("pause");
	return 0;
}

