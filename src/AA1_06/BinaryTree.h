#pragma once
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <stack>
#include <algorithm>    // std::max

struct node {
	node* left;
	node* right;
	int value;
	node() : value(rand() % 99 + 1), left(nullptr), right(nullptr) {};
	node(int _value) : value(_value), left(nullptr), right(nullptr) {};
	~node(){
		if (left != nullptr)
			delete left;
		if (right != nullptr)
			delete right;
	};
};
class BinaryTree
{
	node* Root;
	int GetNumberNodes(node* tmp);
	void PreOrder(node* tmp);
	void PostOrder(node* tmp);
	void InOrder(node* tmp);

public:
	BinaryTree();
	~BinaryTree();
	

	void PreOrder();
	void InOrder();
	void PostOrder();
	int GetNumberNodes();
	int GetNumberNodesI();
	void PreorderI();
	int Height();
	int Height(node* n);

};


