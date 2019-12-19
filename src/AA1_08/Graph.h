#pragma once
#include <algorithm>
#include <vector>
#include <map>
#include <forward_list>
#include <iostream>

typedef int vertex;
typedef std::pair<int, int> edge;


class Graph
{
private:
	std::map<vertex, std::vector<vertex>> graph;
	bool isDirected = false;
	
public:
	Graph();
	Graph(Graph* g); // Constructor copia
	Graph(std::vector<edge> e1); 
	~Graph();

	void Insert(edge _edge);
	void Remove(edge _edge);
	bool Path(vertex initial, vertex final);
	bool path(vertex initial, vertex final, std::forward_list<vertex> vlist);
	void Print();
	void Directed(bool b);
	bool IsEulerian();
	int Index(vertex _vertex);
};

