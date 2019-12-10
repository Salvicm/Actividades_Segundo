#pragma once


struct node {
	node* left;
	node* right;
	int value;
	node() : left(nullptr), right(nullptr) {};
	node(int _value) : value(_value), left(nullptr), right(nullptr) {};
	~node() {
		if (left != nullptr)
			delete left;
		if (right != nullptr)
			delete right;
	};
};

class BST
{
	node * root;
	node * Search(int key, node * n);
	void Insert(int key, node * &n);
public:
	BST();
	~BST();

	node* Search(int key);

	void Insert(int key);
	bool Exist(int key);
};

