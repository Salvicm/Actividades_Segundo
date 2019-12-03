#pragma once
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <stack>


struct node {
	node* left;
	node* right;
	int value;
	node() : value(rand() % 99 + 1), left(nullptr), right(nullptr) {};
	node(int _value) : value(_value), left(nullptr), right(nullptr) {};
};
class BinaryTree
{
	node* Root;
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
};

