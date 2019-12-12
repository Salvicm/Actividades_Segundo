#include "BST.h"



BST::BST()
{
	
}


BST::~BST()
{
	// Hacer una función recursiva extra, el tree debe eliminar los nodos, los nodos no pueden eliminarse solos
	delete root;
}

node * BST::Search(int key)
{
	return Search(key, root);
}

node * BST::Search(int key, node * n) {
	if (!n) // Si n no existe retorna nulo(Mantener una comprobación)
		return nullptr;
	if (key == n->value) // Si es igual, retornala
		return n;
	else if (key < n->value) // Si es menor, vete a la izquierda
		return Search(key, n->left);
	else
		return Search(key, n->right); // Si es mayor, vete a la derecha
}

void BST::Insert(int key)
{
	 Insert(key, root); // ->Recursivo
}

void BST::Insert(int key, node * &n)
{
	
	// Comprueba si existe por si acaso
	if (n) {
		if (n->value > key) { // Si es menor
				Insert(key, n->left); // Comprueba ese lado	
		}
		else if (n->value < key) { // Repite pero con la derecha
				Insert(key, n->right);
		}
	}
	else {
		n = new node(key);
		return;
	}

	
}

bool BST::Exist(int key)
{
	if (Search(key, root) != nullptr)
		return true;
	else
		return false;
}
