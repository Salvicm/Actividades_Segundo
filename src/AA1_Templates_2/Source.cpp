#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>

struct myStruct {
	int a = 0;
	int x = 0;
};

template<typename T, int L = 10>
T couter(const T const a) {
	std::cout << " " << L << " " << a << std::endl;

	return a;
}
template<int L = 10>
std::string couter(const std::string const a) {
	std::cout << "this is a string lol: " << L << std::endl;
	return a;
}

template<class T>
class pepe {
public:
	pepe() {};
	~pepe() {};
	T MyStruct;
	void hasNormalFunct() {
	}
};
template<>
class pepe<std::map<int, int>> {
public:
	pepe() {};
	~pepe() {};
	std::map<int, int> MyStruct;
	void hasMapFunct(){
	}
};

int main() {
	pepe<std::vector<int>> myNormal;
	pepe<std::map<int, int>> myMap;
	
	system("pause");
	return 0;
}

