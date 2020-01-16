#include <fstream>
#include <vector>
#include <exception>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <random>

struct Object {
	char type;
	int x;
	int y;
};
void Save(std::vector<Object> o, std::string fileName);
void Recover(std::vector<Object> &o, std::string fileName);

// Podemos hacer un template
int main()
{
	//AA1_05: Ejercicio 2

	std::vector<Object> objects;

	objects.push_back({ 'a',1,11 });
	objects.push_back({ 'b',2,22 });
	objects.push_back({ 'c',3,33 });
	objects.push_back({ 'd',4,44 });
	objects.push_back({ 'e',5,55 });
	//guardo 5
	Save(objects, "TestSaveObjects.bin");
	objects[0] = { 'x',6,66 };
	objects[4] = { 'z',9,99 };
	objects.push_back({ 'f',7,77 });
	//hay 6
	Recover(objects, "TestSaveObjects.bin");
	//recupero
	std::cout << "Ejercicio2: " << std::endl;
	for (int i = 0; i < objects.size(); i++) {
		std::cout << i << ":" << objects[i].type << "," << objects[i].x << "," << objects[i].y;
		std::cout << std::endl;
	};

	system("pause");
	return 0;
}

void Save(std::vector<Object> o, std::string fileName) {
	try {
		std::ofstream writeFile;
		writeFile.open(fileName, std::ios::out | std::ios::binary);
		if (!writeFile.is_open())
			throw std::exception("No se ha podido abrir el fichero");
		size_t len = o.size();
		writeFile.write(reinterpret_cast<char *>(&len), sizeof(size_t));
		// Hacerlo así, con el [0] nos sirve en este caso al ser un vector, porque tienen todos los datos consecutivos en memoria.
		// La mejor forma de hacerlo es con .data
		writeFile.write(reinterpret_cast<char *>(o.data()), sizeof(Object) * len);
		writeFile.close();
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
	}
}
void Recover(std::vector<Object> &o, std::string fileName) {
	try {
		std::ifstream readFile;
		readFile.open(fileName, std::ios::in | std::ios::binary);
		if (!readFile.is_open())
			throw std::exception("No se ha podido abrir el fichero");
		size_t len;
		readFile.read(reinterpret_cast<char *>(&len), sizeof(size_t));
		o.clear();
		o.resize(len);
		readFile.read(reinterpret_cast<char *>(o.data()), sizeof(Object) * len);
		readFile.close();
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
	}
}

Object generateRandObject() {
	Object tmp;
	tmp.x = rand() % 1000;
	tmp.y = rand() % 1000;
	tmp.type = (rand() % ('z' - 'a') )+ 'a';
	return tmp;
}