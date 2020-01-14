#include <stdlib.h>
#include <iostream>
#include <string>

template<typename T, int L = 1>
T fExample1(const T const a) {

	T jaja = a + std::to_string(L);
	std::cout << jaja << std::endl;
	return a;
}

int main() {


	float i = 3.0f;
	std::cout << i << std::endl;
	fExample1<std::string, 2>("Hola");
	system("pause");
	return 0;
}