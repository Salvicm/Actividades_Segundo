#include <stdlib.h>
#include <iostream>
#include <time.h>
#include "BST.h"
int main() {
	srand(time(NULL));
	BST myBST;
	node* tmp;
	for (int i = 0; i < 9; i++) {
		myBST.Insert(i);
	}
	tmp = myBST.Search(6);
	if (tmp != nullptr)
		std::cout << "Pointer found\n";
	else
		std::cout << "Pointer not found\n";
	for (int i = -5; i < 15; i++) {
		if (myBST.Exist(i)) 
			std::cout << "El numero " << i << " Existe\n";
		else 
			std::cout << "El numero " << i << " No Existe\n";
	}


		
	system("pause");
	return 0;
}