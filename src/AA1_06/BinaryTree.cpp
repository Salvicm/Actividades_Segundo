#include "BinaryTree.h"



BinaryTree::BinaryTree()
{
	// Montar ün arbol fijo
	Root = new node(1);
	Root->left = new node(4);
	Root->right = new node(8);
	Root->left->left = new node(5);
	Root->left->right = new node(7);
	Root->right->left = new node(9);
	Root->right->right = new node(6);
}


BinaryTree::~BinaryTree()
{
}



void BinaryTree::PreOrder()
{
}

void BinaryTree::InOrder()
{
}

void BinaryTree::PostOrder()
{
}

int BinaryTree::GetNumberNodes()
{
	return 0;
}

int BinaryTree::GetNumberNodesI()
{
	std::stack<node*> notVisited;
	int counter = 0;
	node* tmpNode;
	bool allVisited = false;
	if (Root != nullptr) {
		tmpNode = Root;
		counter++;
	

		do
		{
			// Suponiendo que la izda siempre ha sido insertada primera
			if (tmpNode->left != nullptr) { // comprobar la izquierda
				if (tmpNode->right != nullptr) { // Si la derecha está agregado, añadirlo a la lista
					notVisited.push(tmpNode->right);
				}
				tmpNode = tmpNode->left;
				counter++;
			}
			else { // Si la izquierda es nullptr entonces la derecha tambien
				if (!notVisited.empty()) {
					tmpNode = notVisited.top(); // pilla la que esté en top
					notVisited.pop();
					counter++;
				}
				else {
					allVisited = true;
				}
			}



		} while (!allVisited);
	}
	return counter;
}

void BinaryTree::PreorderI()
{
	std::stack<node*> notVisited;
	node* tmpNode;
	bool allVisited = false;
	if (Root != nullptr) {
		tmpNode = Root;
		std::cout << tmpNode->value << std::endl;
		do
		{
			// Suponiendo que la izda siempre ha sido insertada primera
			if (tmpNode->left != nullptr) { // comprobar la izquierda
				if (tmpNode->right != nullptr) { // Si la derecha está agregado, añadirlo a la lista
					notVisited.push(tmpNode->right);
				}
				tmpNode = tmpNode->left;
				std::cout << tmpNode->value << std::endl;

			}
			else { // Si la izquierda es nullptr entonces la derecha tambien
				if (!notVisited.empty()) {
					tmpNode = notVisited.top(); // pilla la que esté en top
					notVisited.pop();
					std::cout << tmpNode->value << std::endl;

				}
				else {
					allVisited = true;
				}
			}



		} while (!allVisited);
	}
}

int BinaryTree::Height()
{
	return 0;
}
