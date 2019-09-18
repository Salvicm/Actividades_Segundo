#pragma once
namespace utils {
	void initEnemies(std::vector<Enemy> &enemies, std::map<std::string, weapons> weaponReg) {
#pragma region file Read
		rapidxml::xml_document<> doc;
		std::ifstream file("../../res/files/config.xml");
		std::stringstream buffer;
		buffer << file.rdbuf();
		file.close();
		std::string content(buffer.str());
		doc.parse<0>(&content[0]);
#pragma endregion
		int vit;
		float atkDmg;
		int atkFreq;
		int def;
		int exp;
		std::vector<weapons> weaponsList;
		std::string name;
		rapidxml::xml_node<> *pRoot = doc.first_node();
		for (rapidxml::xml_node<> *pNode = pRoot->first_node(); pNode; pNode = pNode->next_sibling()) {
			weaponsList.clear();

			name = pNode->first_node("name")->value();
			vit = std::stoi(pNode->first_node("vit")->value());
			def = std::stoi(pNode->first_node("def")->value());
			atkDmg = std::stof(pNode->first_node("atkDmg")->value());
			atkFreq = std::stoi(pNode->first_node("atkFreq")->value());
			exp = std::stoi(pNode->first_node("exp")->value());
			

			for (rapidxml::xml_node<> *weaponNode = pNode->first_node("weaponId"); weaponNode != nullptr; weaponNode = weaponNode->next_sibling("weaponId")) {
				weaponsList.push_back(weaponReg.at(weaponNode->value()));
			}
			enemies.push_back(Enemy(name, vit, def, atkDmg, atkFreq, exp, weaponsList));
			std::cout << std::endl << std::endl;
		}
	}

	void initWeapons(std::map<std::string, weapons> &weaponList) {
#pragma region file Read
		rapidxml::xml_document<> doc;
		std::ifstream file("../../res/files/weapons.xml");
		std::stringstream buffer;
		buffer << file.rdbuf();
		file.close();
		std::string content(buffer.str());
		doc.parse<0>(&content[0]);
		rapidxml::xml_node<> *pRoot = doc.first_node();
#pragma endregion
		weapons newWeapon;
		for (rapidxml::xml_node<> *pNode = pRoot->first_node(); pNode; pNode = pNode->next_sibling()) {
			// Read in order. Id is identifier, range is range, and the attribute is category
			newWeapon = weapons{ pNode->first_attribute()->value(), pNode->first_node("id")->value(), std::stoi(pNode->first_node("range")->value()) };
			weaponList.insert({ newWeapon.identifier, newWeapon });

		}
	}
	void printEnemies(std::vector<Enemy> enemies) {
		for (Enemy currentEnemy : enemies) {
			std::cout << "Name: " << currentEnemy.name << std::endl << "Vit: " << currentEnemy.vit << std::endl;
			std::cout << "AtkDmg: " << currentEnemy.atkDmg << std::endl << "AtkFreq: " << currentEnemy.atkFreq << std::endl;
			std::cout << "Defense: " << currentEnemy.def << std::endl << "Experience: " << currentEnemy.defeatedExp << std::endl << std::endl;
			for (weapons weapon : currentEnemy.weaponsList) {
				std::cout << "Weapon\n   Name: " << weapon.identifier << std::endl;
				std::cout << "   Type: " << weapon.type << std::endl;
				std::cout << "   Range: " << weapon.range << std::endl;
			}
			std::cout << std::endl << std::endl;
		}
	}
}
