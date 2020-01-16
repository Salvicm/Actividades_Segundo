#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>


struct myStruct {
	int a = 0;
	int x = 0;
};

template<typename T, int L = 10>
T couter(const T const a) {
	   std::cout <<  " " << L << " " << a << std::endl;
	return a;
}
template<int L = 10>
std::string couter(const std::string const a) {
	std::cout << "this is a string lol: " << L << std::endl;
	return a;
}

template<typename T>
T addAll(std::vector<T> list) {
	T count = 0;
	for (auto& elem : list) {
		count += elem;
	}
	return count;
}



template<>
std::string addAll(std::vector<std::string> list) {
	std::string total = "";
	for (auto& elem : list) {
		total += elem;
	}
	return total;
}

template <typename T, int t>
T funct(T m) {
	for (int i = 0; i < t; i++) {
		std::cout << m << ": " << i << std::endl;
	}
	return m;
}

void testFex1() {
	couter<int, 20>(10);
	couter<float, 32>(10.5f);
	couter<bool, 15>(true);
	couter<char>('a');
	couter<100>("Hola bro");
}

void testVects() {
	std::vector<int> vecInt = { 4,3,2,5,6,1 };
	std::vector<double> vecDouble = { 4.1,3.2,2.3,5.4,6.5,1.6 };
	std::vector<char> vecChar = { 'a','b','c','d','e','f' };
	std::vector<std::string> vecStr = { "Hola", ", Puto"};
	std::cout << addAll<int>(vecInt) << std::endl;
	std::cout << addAll<double>(vecDouble) << std::endl;
	std::cout << addAll<char>(vecChar) << std::endl;
	std::cout << addAll<std::string>(vecStr) << std::endl;
}

void testFunct() {
	funct<int, 5>(5);
}
int main() {
	testFunct();

	
	
	system("pause");
	return 0;
}

