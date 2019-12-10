#include "BinaryTree.h"

int main() {

	srand(time(NULL));
	BinaryTree Tree;
	std::cout <<"Number of nodes : " <<  Tree.GetNumberNodes() << std::endl;
	std::cout <<"Height: " << Tree.Height() << std::endl;
	std::cout << "\n__________________PreOrder__________________\n\n";
	Tree.PreOrder();
	std::cout << "\n_________________PostOrder__________________\n\n";
	Tree.PostOrder();
	std::cout << "\n__________________InOrder___________________\n\n";
	Tree.InOrder();
	/*
	Tree.PreorderI();
	std::cout << "Number of nodes: " << Tree.GetNumberNodesI() << std::endl;
	*/
	system("pause");
	return 0;
}