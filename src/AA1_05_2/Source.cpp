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
Object generateRandObject();


int main() {
	srand(time(NULL));
	std::vector<Object> objects;
	/*for (int i = 0; i < 15; i++) {
		objects.push_back(generateRandObject());
	}
	for (std::vector<Object>::iterator it = objects.begin(); it != objects.end(); it++)
	{
		std::cout << "X: " << it->x << " Y: " << it->y << " Type: " << it->type << std::endl;
	}
	Save(objects, "Obj.UwU");
	objects.clear();
	*/
	Recover(objects, "Obj.UwU");
	std::cout << "RECOVERED\n";
	for (std::vector<Object>::iterator it = objects.begin(); it != objects.end(); it++)
	{
		std::cout << "X: " << it->x << " Y: " << it->y << " Type: " << it->type << std::endl;
	}
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
		// En el caso de hacerlo con stack ü otros tipos de stl, podría petar, así que habría que hacerlo uno a uno volcando la memoria.
		writeFile.write(reinterpret_cast<char *>(&o[0]), sizeof(Object) * len);
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
		// Esto nos permite que sea escalable
		o.clear();
		o.resize(len);
		readFile.read(reinterpret_cast<char *>(&o[0]), sizeof(Object) * len);
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