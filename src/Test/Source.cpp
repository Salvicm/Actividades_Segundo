#include <stdlib.h>
#include <iostream>
struct enemy {
	int life;
	int level;
};

template<class T = int>
T sum(T a, T b) {
	std::cout << a << b << std::endl;
	return a + b;
}

void templateTest() {
	enemy a1, a2;
	a1.level = 10;
	a1.life = 2;
	a2.level = 3;
	a2.life = 4;
	int a = 1, b = 1;
	//sum<enemy>(a1, a2);
	sum<>(a, b);
}


int main() {
	templateTest();

	system("pause");
	return 0;
}