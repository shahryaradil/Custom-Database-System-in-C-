#include<iostream>
#include "BTreeNode.h"
using namespace std;

// A BTree node
//template <class T>


class BTree
{
	BTreeNode* root; // Pointer to root node
	int order; // Minimum degree
public:

	// Constructor (Initializes tree as empty)
	BTree(int orderr)
	{
		root = NULL;
		order = orderr;
	}

	void traverse()
	{
		if (root != NULL) root->traverse();
	}

	// function to search a key in this tree
	BTreeNode* search(int k)
	{
		return (root == NULL) ? NULL : root->search(k);
	}

	// The main function that inserts a new key in this B-Tree
	void insert(int k);

	// The main function that removes a new key in this B-Tree
	void remove(int k);

};





// The main function that inserts a new key in this B-Tree
void BTree::insert(int k)
{
	// If tree is empty
	if (root == NULL)
	{
		// Allocate memory for root
		root = new BTreeNode(order, true);
		root->keys[0] = k; // Insert key
		root->n = 1; // Update number of keys in root
	}
	else // If tree is not empty
	{
		// If root is full, then tree grows in height
		if (root->n == order - 1)
		{
			// Allocate memory for new root
			BTreeNode* s = new BTreeNode(order, false);

			// Make old root as child of new root
			s->C[0] = root;

			// Split the old root and move 1 key to the new root
			s->splitChild(0, root);

			// New root has two children now. Decide which of the
			// two children is going to have new key
			int i = 0;
			if (s->keys[0] < k)
				i++;
			s->C[i]->insertNonFull(k);

			// Change root
			root = s;
		}
		else // If root is not full, call insertNonFull for root
			root->insertNonFull(k);
	}
}
void BTree::remove(int k)
{
	if (!root)
	{
		cout << "The tree is empty\n";
		return;
	}

	// Call the remove function for root
	root->remove(k);

	// If the root node has 0 keys, make its first child as the new root
	// if it has a child, otherwise set root as NULL
	if (root->n == 0)
	{
		BTreeNode* tmp = root;
		if (root->leaf)
			root = NULL;
		else
			root = root->C[0];

		// Free the old root
		delete tmp;
	}
	return;
}

