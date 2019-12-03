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
	PreOrder(Root);
}
void BinaryTree::PreOrder(node * tmp)
{

	PreOrder(tmp->left);

	PreOrder(tmp->right);
}

void BinaryTree::InOrder()
{
}

void BinaryTree::PostOrder()
{
}

int BinaryTree::GetNumberNodes()
{

	return GetNumberNodes(Root);
}

int BinaryTree::GetNumberNodes(node * tmp)
{

	if (tmp == nullptr)
		return 0;
	return GetNumberNodes(tmp->left) + GetNumberNodes(tmp->right) + 1;
}


void BinaryTree::PostOrder(node * tmp)
{
}

void BinaryTree::InOrder(node * tmp)
{
}

int BinaryTree::GetNumberNodesI()
{
	if (Root == nullptr) return 0;
	
	std::stack<node*> notVisited;
	int counter = 0;
	node* tmpNode;	
	notVisited.push(Root);
	while (!notVisited.empty())
	{
		// La versión de Tona
		tmpNode = notVisited.top();
		notVisited.pop();
		counter++;
		if (tmpNode->right)
			notVisited.push(tmpNode->right);
		if (tmpNode->left)
			notVisited.push(tmpNode->left);
		
		
		/* MI VERSION
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
		}*/
	} 
	
	return counter;
}

void BinaryTree::PreorderI()
{
	

	std::stack<node*> notVisited;
	node* tmpNode;
	if(Root != nullptr)
		notVisited.push(Root);
	while (!notVisited.empty())
	{
		// La versión de Tona
		tmpNode = notVisited.top();
		notVisited.pop();
		std::cout << tmpNode->value << ", ";
		if (tmpNode->right)
			notVisited.push(tmpNode->right);
		if (tmpNode->left)
			notVisited.push(tmpNode->left);
	}
	std::cout << std::endl;
}

int BinaryTree::Height()
{
	return 0;
}
