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

void printEnemies(rapidxml::xml_node<> *pRoot, std::vector<Enemy> &enemies, std::map<std::string, weapons> weaponId);
	void initWeapons(std::map<std::string, weapons> &weaponList);

int main() {
	srand(time(NULL));
	// hey
	std::vector<Enemy> enemies;
	std::map<std::string, weapons> weaponIdentifier;
	initWeapons(weaponIdentifier);
	/*initializeEnemies(enemies, NUMBERENEMIES, weaponIdentifier, NUMBERWEAPONS);
	
	std::map<int, weapons>::iterator it = weaponIdentifier.begin();
	while (it != weaponIdentifier.end()) {
		std::cout << "Id: " << it->first << ". Type:  " << it->second.type << " Range: " << it->second.range << std::endl;
		it++;
	}*/

	rapidxml::xml_document<> doc;
	std::ifstream file("../../res/files/config.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();

	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);

	rapidxml::xml_node<> *pRoot = doc.first_node();
	printEnemies(pRoot, enemies, weaponIdentifier);
	/*for (Enemy currentEnemy : enemies) {
		std::cout << "Name: " << currentEnemy.name << std::endl << "Vit: " << currentEnemy.vit << std::endl;
		std::cout << "AtkDmg: " << currentEnemy.atkDmg << std::endl << "AtkFreq: " << currentEnemy.atkFreq << std::endl;
		std::cout << "Defense: " << currentEnemy.def << std::endl << "Experience: " << currentEnemy.defeatedExp << std::endl << std::endl;
	}*/
	system("pause");
	return 0;
}

void printEnemies(rapidxml::xml_node<> *pRoot, std::vector<Enemy> &enemies, std::map<std::string, weapons> weaponId) {
	/*int vit;
	int atkDmg;
	int atkFreq;
	std::vector<weapons> weaponsList;
	std::string name;*/

	for (rapidxml::xml_node<> *pNode = pRoot->first_node(); pNode; pNode = pNode->next_sibling()) {
		std::cout << "Name: " << pNode->first_node("name")->value() << std::endl;
		std::cout << "Vitality: " << pNode->first_node("vit")->value() << std::endl;
		std::cout << "Defense: " << pNode->first_node("def")->value() << std::endl;
		std::cout << "Atack Damage: " << pNode->first_node("atkDmg")->value() << std::endl;
		std::cout << "Attack Frequency: " << pNode->first_node("atkFreq")->value() << std::endl;
		std::cout << "Defeated Experience: " << pNode->first_node("exp")->value() << std::endl;

		int i = 1;
		for (rapidxml::xml_node<> *weaponNode = pNode->first_node("weaponId"); weaponNode != nullptr; weaponNode =  weaponNode->next_sibling("weaponId")) {
			std::cout << "Weapon number " << i << " identifier: " << weaponNode->value() << " Range: " << weaponId.at(weaponNode->value()).range 
				<< " Type: " << weaponId.at(weaponNode->value()).type << std::endl;
			
			i++;
		}
		std::cout << std::endl << std::endl;
	}
		
		/*vit = pNode->first_node("vit")->value();
		atkDmg = pNode->first_node("atkDmg")->value();
		atkFreq = pNode->first_node("atkFreq")->value();
		name = pNode->first_node("name")->value();*/
}

void initWeapons(std::map<std::string, weapons> &weaponList) {
	weapons newWeapon{ 20, "Gun" };
	weaponList.insert({ "PISTOL", newWeapon });

	newWeapon = weapons{ 25, "Gun" };
	weaponList.insert({ "BAZOOKA", newWeapon });
	newWeapon = weapons{ 2, "Katana" };
	weaponList.insert({ "WADO ICHIMONJI", newWeapon });
	newWeapon = weapons{ 1, "Katana" };
	weaponList.insert({ "SANDAI KITETSU", newWeapon });
	newWeapon = weapons{ 1, "Bo" };
	weaponList.insert({ "CLIMA TACT", newWeapon });
	newWeapon = weapons{ 12, "Bo" };
	weaponList.insert({ "SORCERY CLIMA TACT", newWeapon });
	newWeapon = weapons{ 15, "Devil Fruit" };
	weaponList.insert({ "GIGANTESCO MANO", newWeapon });
	newWeapon = weapons{ 10, "Devil Fruit" };
	weaponList.insert({ "MIL FLEUR", newWeapon });
}