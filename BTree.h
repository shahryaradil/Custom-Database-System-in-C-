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

		node->setOrder(orderOfTree,true);


	}

	void insert(T d, BTreeNode<T>* node, BTreeNode<T>* parent = NULL, bool insertNonLeaf = false) {

		



		if (node->isLeaf == true || insertNonLeaf ) {

			if (!node->InsertKey(d)) {

				//splitChild(node, parent);

			}

		}
		else
		{
			//this->insert(d, this->nextNode(d, node), node);
		}



	}

	void splitChild(BTreeNode<T>* node, BTreeNode<T>* parent) {

		if (parent == NULL) {
			parent = new BTreeNode<T>;
			parent->setOrder(orderOfTree);
			root = parent;
		}
		BTreeNode<T>* childL = new BTreeNode<T>(orderOfTree);
		BTreeNode<T>* childR = new BTreeNode<T>(orderOfTree);
		int splitAt = -1;
		T keyRemoved;
		int splitAt = (ceil((double)node->order / 2) - 1);
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

		this->insert(keyRemoved, node);
		node->isLeaf = false;




	}



	/*BTreeNode<T>* nextNode(T d, BTreeNode<T>* node) {


		for (int i = 0; i < node->noOfFilledKeys; i++)
		{
			if (d < node->keys[i]) {
				return node->childs.at(i);
			}
			else if (i == node->noOfFilledKeys - 1 && d > node->keys[i]) {

				return node->childs.at(i+1);
			}

		}


	}*/


};
