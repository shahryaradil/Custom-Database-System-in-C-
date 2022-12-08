//#pragma once
//#include "BTreeNode.h"
//#include "queue.h"
//#include <math.h> 
//
//using namespace std;
//
//template <class T>
//class BTree
//{
//public:
//
//	BTreeNode <T>* root = NULL;
//	int orderOfTree;
//
//
//
//
//	BTree()
//	{
//		root = NULL;
//		orderOfTree = 0;
//	}
//
//	BTree(int order)
//	{
//		orderOfTree = order;
//		root = new BTreeNode<T>;
//		this->setOrder(order, root, true);
//	}
//
//	void setOrder(int order, BTreeNode<T>* node, bool isLeaf) {
//
//		node->setOrder(orderOfTree, isLeaf);
//
//
//	}
//
//	void insert(T d, BTreeNode<T>* node, BTreeNode<T>* parent = NULL, bool insertNonLeaf = false) {
//
//
//		BTreeNode<T>* temp;
//
//		node->InsertKey(10);
//		node->InsertKey(20);
//		node->InsertKey(30);
//		root = splitChild(node, NULL);
//		temp = GetInsertionNode(9, root);
//		temp->InsertKey(9);
//		temp->InsertKey(8);
//		temp = GetInsertionNode(40, root);
//		temp->InsertKey(40);
//		temp->InsertKey(50);
//
//		/*temp = GetInsertionNode(50, root);
//		temp->InsertKey(50);*/
//		/*root = splitChild(temp, root);
//		temp = GetInsertionNode(60, root);
//		temp->InsertKey(60);*/
//
//
//
//		/*if (node->isLeaf == true || insertNonLeaf) {
//
//			if (!node->InsertKey(d)) {
//
//				BTreeNode<T>* temp = splitChild(node, parent);
//				if (node == root) {
//
//					node = temp;
//					root = node;
//				}
//				this->insert(d, root);
//
//
//			}
//
//		}
//		else
//		{
//			node->InsertChild(this->insert(d, this->nextNode(d, node), node));
//		}*/
//
//
//
//	}
//
//	BTreeNode<T>* splitChild(BTreeNode<T>* node, BTreeNode<T>* parent) {
//
//		if (parent == NULL) {
//			parent = new BTreeNode<T>;
//			parent->setOrder(orderOfTree, false);
//		}
//		BTreeNode<T>* childL = new BTreeNode<T>(orderOfTree, true);
//		BTreeNode<T>* childR = new BTreeNode<T>(orderOfTree, true);
//		int splitAt = -1;
//		T keyRemoved;
//		splitAt = (ceil((double)node->order / 2) - 1);
//		keyRemoved = node->keys[splitAt];
//
//
//		for (int i = 0; i < node->noOfFilledKeys; i++)
//		{
//			if (i < splitAt) {
//				childL->InsertKey(node->keys[i]);
//			}
//			else if (i > splitAt) {
//				childR->InsertKey(node->keys[i]);
//			}
//		}
//
//		//node->keys.erase(node->keys.begin() + splitAt);
//
//		parent->InsertKey(keyRemoved);
//		parent->InsertChild(childL);
//		parent->InsertChild(childR);
//		parent->isLeaf = false;
//		return parent;
//
//
//	}
//
//	void makeNewRoot(BTreeNode<T>* node) {
//
//
//
//		BTreeNode<T>* parent;
//
//		if (parent == NULL) {
//			parent = new BTreeNode<T>;
//			parent->setOrder(orderOfTree);
//			root = parent;
//		}
//		BTreeNode<T>* childL = new BTreeNode<T>(orderOfTree);
//		BTreeNode<T>* childR = new BTreeNode<T>(orderOfTree);
//		int splitAt = -1;
//		T keyRemoved;
//		int splitAt = (ceil((double)node->order / 2) - 1);
//		keyRemoved = node->removeKeyIndex(splitAt);
//
//
//		for (int i = 0; i < node->noOfFilledKeys; i++)
//		{
//			if (i < splitAt) {
//				childL.InsertKey(node->keys[i]);
//			}
//			else if (i > splitAt) {
//				childR.InsertKey(node->keys[i]);
//			}
//		}
//
//		this->insert(keyRemoved, node);
//		node->isLeaf = false;
//
//
//
//
//	}
//
//
//
//	BTreeNode<T>* nextNode(T d, BTreeNode<T>* node) {
//
//
//		for (int i = 0; i < node->noOfFilledKeys; i++)
//		{
//			if (d < node->keys[i]) {
//				return node->childs[i];
//			}
//			else if (i == node->noOfFilledKeys - 1 && d > node->keys[i]) {
//
//				return node->childs[i + 1];
//			}
//
//		}
//
//
//	}
//
//	BTreeNode<T>* GetInsertionNode(T d, BTreeNode<T>* node) {
//
//
//		for (int i = 0; i < node->noOfFilledKeys; i++)
//		{
//			if (d < node->keys[i]) {
//				node = node->childs[i];
//			}
//			else if (d > node->keys[node->noOfFilledKeys]) {
//
//				node = node->childs[i + 1];
//			}
//
//		}
//
//		return node;
//
//	}
//
//	void traverse(BTreeNode<T>* node) {
//
//		Queue<BTreeNode<T>*> nodeQue;
//		int count = -1;
//		nodeQue.Enqueue(node);
//
//		while (!nodeQue.empty())
//		{
//			BTreeNode<T>* temp = nodeQue.retFront();
//			nodeQue.Dequeue();
//			if (temp == NULL) {
//				continue;
//			}
//			/*if (count / orderOfTree == 0) {
//				cout << "\t";
//			}*/
//			temp->printKeys();
//			for (int i = 0; i < temp->childs.size(); i++)
//			{
//				if (!temp->isLeaf) {
//
//					nodeQue.Enqueue(temp->childs[i]);
//				}
//			}
//			count++;
//		}
//	}
//
//};