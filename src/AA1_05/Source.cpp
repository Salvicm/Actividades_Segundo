#include <fstream>
#include <vector>
#include <exception>
#include <iostream>
#include <stdlib.h>

void SaveVector(std::vector<int> o, std::string fileName);
void RecoverVector(std::vector<int> &o, std::string fileName);


int main() {
	std::vector<int> tmpVect({ 1,2,3,4,5,6,7,8,9,10 });
	SaveVector(tmpVect, "Save.bin");
	for (int i = 0; i < 10; i++) {
		tmpVect[i] = tmpVect[i] + 10;
	};
	RecoverVector(tmpVect, "Save.bin");
	for (int i = 0; i < 10; i++) {
		std::cout << tmpVect[i] << "\n";
	};

	system("pause");
	return 0;
}

void SaveVector(std::vector<int> o, std::string fileName) {
	try {
		std::ofstream writeFile;
		writeFile.open(fileName, std::ios::out | std::ios::binary);
		size_t len = o.size();
		writeFile.write(reinterpret_cast<char *>(&len), sizeof(size_t));
		writeFile.write(reinterpret_cast<char *>(&o.begin()), sizeof(int) * len);
		writeFile.close();
	}
	catch (std::exception) {
		std::cout << "File not open\n";
	}
}
void RecoverVector(std::vector <int> &o, std::string fileName) {
	try {
		std::ifstream readFile;
		readFile.open(fileName, std::ios::in | std::ios::binary);
		size_t len;
		
		readFile.read(reinterpret_cast<char *>(&len), sizeof(size_t));
		readFile.read(reinterpret_cast<char *>(&o.begin()), sizeof(int) * len);
		readFile.close();
	}
	catch (std::exception) {
		std::cout << "File not open\n";
	}
}