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


int main() {
	srand(time(NULL));

	std::vector<Enemy> enemies;
	std::map<int, weapons> weaponIdentifier;
	initializeEnemies(enemies, NUMBERENEMIES, weaponIdentifier, NUMBERWEAPONS);

	std::map<int, weapons>::iterator it = weaponIdentifier.begin();
	while(it != weaponIdentifier.end()){
		std::cout << "Id: " << it->first << ". Type:  " << it->second.type << " Range: " << it->second.range << std::endl;
		it++;
	}
	rapidxml::xml_document<> doc;
	std::ifstream file("../../res/files/Enemies.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();

	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);
	
	system("pause");
	return 0;
}