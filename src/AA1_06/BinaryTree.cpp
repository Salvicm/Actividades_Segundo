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
	delete Root;
}



void BinaryTree::PreOrder()
{
	PreOrder(Root);
}

void BinaryTree::PreOrder(node * tmp)
{
	if (tmp) {
		std::cout << tmp->value << ", ";
		PreOrder(tmp->left);
		PreOrder(tmp->right);
	}
}


void BinaryTree::InOrder()
{
	InOrder(Root);
}
void BinaryTree::InOrder(node * tmp) 
{
	if (tmp) {
		InOrder(tmp->left);
		std::cout << tmp->value << ", ";
		InOrder(tmp->right);
	}
}


void BinaryTree::PostOrder()
{
	PostOrder(Root);
}

void BinaryTree::PostOrder(node * tmp) {
	if (tmp) {
		PostOrder(tmp->left);
		PostOrder(tmp->right);
		std::cout << tmp->value << ", ";
	}
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
int BinaryTree::Height(node* n) {

	if (n == nullptr)
		return 0;

	if(Height(n->left) > Height(n->right))
		return 1 + Height(n->left);
	else 
		return 1 + Height(n->right);
}
int BinaryTree::Height()
{
	return Height(Root);
}
