#include "BST.h"



BST::BST()
{
	
}


BST::~BST()
{
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
	// iterativo
/*	node* tmp = root;
	if (root == nullptr) {
		root = new node(key);
		return;
	}
	while (true) {
		if (key == tmp->value) {
			return;
		}
		else if (key < tmp->value) { // Si es menor
			if (tmp->left) { // Y se puede bajar mas
				tmp = tmp->left; // Insertalo
			}
			else { // Si no Puedes bajar
				tmp->left = new node(key); // Insertalo
				return;
			}
		}
		else if (key > tmp->value) { // Lo mismo pero hacia la derecha con numeros mayores
			if (tmp->right) {
				tmp = tmp->right;
			}
			else {
				tmp->right = new node(key);
				return;
			}
		}
	}*/
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
