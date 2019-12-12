#include "Graph.h"



Graph::Graph()
{
}

Graph::Graph(Graph * g)
{
	// Const por copia
}

Graph::Graph(std::vector<edge> e1)
{
	// Hacer
	// const lista de arcos	
	for (std::vector<edge>::const_iterator it = e1.begin(); it != e1.end(); it++) {
		Insert(*it);
	}


}


Graph::~Graph()
{
}

void Graph::Insert(edge _edge)
{
	
	// Hacer
	// Inserta el arco si no existe
	graph.try_emplace(_edge.first);
	std::vector<vertex>* mapVect = &graph.at(_edge.first);
	// Guardamos el vector en un puntero para evitar buscar todo el rato
	std::vector<vertex>::const_iterator it = std::find(mapVect->begin(), mapVect->end(), _edge.second);
	if(it == mapVect->end())
		mapVect->push_back(_edge.second);
	
}

void Graph::Remove(edge _edge)
{
	// Hacer
	// Borra el arco si existe
	std::vector<vertex>* mapVect;
	std::map<vertex, std::vector<vertex>>::iterator it;
	it = graph.find(_edge.first);

	if (it != graph.end()) {
		std::vector<vertex>* mapVect = &(it->second);
		std::vector<vertex>::iterator vertexIt = std::find(mapVect->begin(), mapVect->end(), _edge.second);
		if (vertexIt != mapVect->end())
			mapVect->erase(vertexIt);
	}
}

bool Graph::Path(vertex initial, vertex final)
{
	// Verifica si existe un camino desde el vértice inicial hasta el final
	return false;
}

bool Graph::path(vertex initial, vertex final, std::forward_list<vertex> vlist)
{
	// Verifica si existe un camino, si no existe devuelve false y la vlist vacía, si existe devuelve true y construye en vlist el camino
	return false;
}

void Graph::Print()
{
	// Hacer
	// Imprime la lista de arcos
	
	for (std::map<vertex, std::vector<vertex>>::iterator it = graph.begin(); it != graph.end(); it++) {
		std::cout << "Node " << it->first << " Connects to: \n";
		for (std::vector<vertex>::iterator itVect = it->second.begin(); itVect != it->second.end(); itVect++) {
			std::cout << "(" << *itVect << ")\n";
		}
	}
}

bool Graph::IsEulerian()
{
	// Verifica que sea euleriano
	return false;
}

int Graph::Index(vertex _vertex)
{
	// Calcula el índice
	return 0;
}
