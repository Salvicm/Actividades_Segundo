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
	std::cout << "______________\n";
	std::vector<edge> edges;
	edges.push_back({ 1,1 });
	edges.push_back({ 1,2 });
	edges.push_back({ 2,1 });
	edges.push_back({ 1,3 });
	edges.push_back({ 1,4 });
	edges.push_back({ 5,3 });
	edges.push_back({ 2,3 });

	Graph myGraph2(edges);
	myGraph2.Print();
	system("Pause");
	return 0;
}