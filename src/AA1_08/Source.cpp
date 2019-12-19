#include <stdlib.h>
#include "Graph.h"
int main() {
	
	Graph myGraph;
	myGraph.Insert({ 1,3 });
	myGraph.Insert({ 1,4 });
	myGraph.Insert({ 2,4 });
	myGraph.Print();
	std::cout << "Index in 1: " << myGraph.Index(1) << std::endl;
	std::cout << "Euleriano: " << myGraph.IsEulerian() << std::endl;
	std::cout << "______________\n";
	myGraph.Directed(true);
	myGraph.Remove({ 4,2 });
	myGraph.Insert({ 5,1 });
	myGraph.Print();
	std::cout << "Index in 2: " << myGraph.Index(2) << std::endl;

	std::cout << "Euleriano: " << myGraph.IsEulerian() << std::endl;

	system("Pause");
	return 0;
}