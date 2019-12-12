#include <stdlib.h>
#include "Graph.h"
int main() {

	Graph myGraph;
	myGraph.Insert({ 1,2 });
	myGraph.Insert({ 3,4 });
	myGraph.Insert({ 5,6 });
	myGraph.Insert({ 2,4 });
	myGraph.Insert({ 1,0 });
	myGraph.Print();
	myGraph.Remove({ 1,2 });
	system("Pause");
	return 0;
}