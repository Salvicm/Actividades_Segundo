#include <fstream>
#include <vector>
#include <exception>
#include <iostream>
#include <stdlib.h>

void SaveVector(std::vector<int> o, std::string fileName);
void RecoverVector(std::vector<int> &o, std::string fileName);

// Ejercicio 1: vector int
int main() {
	// std::vector<int> tmpVect({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
	std::vector<int> tmpVect;
	/*SaveVector(tmpVect, "Save.bin");
	for (int i = 0; i < 10; i++) {
		tmpVect[i] = tmpVect[i] + 10;
	};*/
	RecoverVector(tmpVect, "Save.bin");
	for (int i = 0; i < tmpVect.size(); i++) {
		std::cout << tmpVect[i] << "\n";
	};

	system("pause");
	return 0;
}

void SaveVector(std::vector<int> o, std::string fileName) {
	try {
		std::ofstream writeFile;
		writeFile.open(fileName, std::ios::out | std::ios::binary);
		if (!writeFile.is_open())
			throw std::exception("No se ha podido abrir el fichero");
		size_t len = o.size();
		writeFile.write(reinterpret_cast<char *>(&len), sizeof(size_t));
		writeFile.write(reinterpret_cast<char *>(o.data()), sizeof(int) * len); // .data() retorna ün püntero donde se almacenan los datos del vector
		writeFile.close();
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
	}
}
void RecoverVector(std::vector <int> &o, std::string fileName) {
	try {
		std::ifstream readFile;
		readFile.open(fileName, std::ios::in | std::ios::binary);
		if (!readFile.is_open())
			throw std::exception("No se ha podido abrir el fichero");
		size_t len;
		readFile.read(reinterpret_cast<char *>(&len), sizeof(size_t));
		// Esto nos permite que sea escalable
		o.clear();
		o.resize(len);
		readFile.read(reinterpret_cast<char *>(o.data()), sizeof(int) * len);
		readFile.close();
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
	}
}