#include <stdlib.h>
#include "Graph.h"
int main() {
	
	Graph myGraph;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			myGraph.Insert({ i, j });
		}
	}

	myGraph.Print();
	system("Pause");
	return 0;
}