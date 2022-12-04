#pragma once
#include "BTreeNode.h"
#include <math.h> 

using namespace std;

template <class T>
class BTree
{
public:

	BTreeNode <T>* root = NULL;
	int orderOfTree;




	BTree()
	{
		root = NULL;
		orderOfTree = 0;
	}

	BTree(int order)
	{
		orderOfTree = order;
		root = new BTreeNode<T>;
		this->setOrder(order, root);
	}

	void setOrder(int order, BTreeNode<T>* node) {

		node->setOrder(orderOfTree);


	}

	void insert(T d, BTreeNode<T>* node) {

		if (node->isLeaf == true) {

			if (!node->InsertKey(d)) {
				node->clearNode();
			}

		}
		else
		{
			this->insert(d, this->nextNode(d, node));
		}



	}

	BTreeNode<T>* splitChild(int splitAt, BTreeNode<T>* node) {

		BTreeNode<T> childL(orderOfTree), childR(orderOfTree);

		T keyRemoved;
		int splitAt = (node->order / 2);
		keyRemoved = node->removeKeyIndex(splitAt);


		for (int i = 0; i < node->noOfFilledKeys; i++)
		{
			if (i < splitAt) {
				childL.InsertKey(node->keys[i]);
			}
			else if (i > splitAt) {
				childR.InsertKey(node->keys[i]);
			}
		}

		node->clearNode();
		this->insert(keyRemoved, node);
		node->isLeaf = false;
		



	}



	BTreeNode<T>* nextNode(T d, BTreeNode<T>* node) {


		for (int i = 0; i < node->noOfFilledKeys; i++)
		{
			if (d < node->keys[i]) {
				return node->childs[i];
			}
			else if (i == node->noOfFilledKeys - 1 && d > node->keys[i]) {

				return node->childs[i + 1];
			}

		}


	}


};
