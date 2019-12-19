#include <fstream>
#include <vector>
#include <exception>
#include <iostream>
#include <stdlib.h>

void SaveVector(std::vector<int> o, std::string fileName);
void RecoverVector(std::vector<int> &o, std::string fileName);

// Ejercicio 1: vector int

int main()
{

	//AA1_05: Ejercicio 1
	std::vector<int> a({ 1,2,3,4,5,6,7,8,9,10 });
	SaveVector(a, "TestSaveVector.bin");
	for (int i = 0; i < 10; i++) { a[i] = a[i] + 10; };
	a.push_back(1000);
	RecoverVector(a, "TestSaveVector.bin");
	std::cout << "Ejercicio1: ";
	for (int i = 0; i < a.size(); i++) { std::cout << a[i] << ","; };

	std::cout << std::endl;
	
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