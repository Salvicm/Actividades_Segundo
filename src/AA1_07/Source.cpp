#include <stdlib.h>
#include <time.h>
#include "BST.h"

int main() {
	srand(time(NULL));
	BST myBST;
	node* tmp;
	std::queue<int> queue;
	queue.push(-1);
	queue.push(-2);
	queue.push(-1);
	queue.push(-2);
	queue.push(-1);
	queue.push(-1);
	queue.push(-2);
	queue.push(-1);
	queue.push(-2);
	queue.push(-1);
	
	for (int i = 0; i < 20; i++) {
		myBST.Insert(rand() % 15);
	}

	/*tmp = myBST.Search(6);
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
	*/

	myBST.PrintPath(queue);

		
	system("pause");
	return 0;
}