#pragma once
#include <iostream>
#include <vector>
using namespace std;



template <class T>


class BTreeNode
{
public:

	vector<T> keys;
	vector<BTreeNode<T>*> childs;
	int order;
	bool isLeaf;
	int noOfFilledKeys = 0;

	BTreeNode()
	{
		order = 0;
		isLeaf = true;
		noOfFilledKeys = 0;

	}


	BTreeNode(int odr, bool leaf)
	{
		order = odr;
		isLeaf = leaf;
		noOfFilledKeys = 0;

	}

	void setOrder(int odr, bool leaf) {
		this->order = odr;
		isLeaf = leaf;
		noOfFilledKeys = 0;

	}

	bool InsertKey(T d) {


		if (noOfFilledKeys + 1 >= order)
			return false;

		for (int i = 0; i < noOfFilledKeys; i++)
		{
			if (d < keys[i]) {
				keys.insert(keys.begin() + i, d);
				noOfFilledKeys++;
				return true;

			}

		}

		keys.push_back(d);
		noOfFilledKeys++;

		return true;




	}


	bool InsertChild(BTreeNode<T>* child) {

		//child->printKeys();

		if (noOfFilledKeys + 1 > order)
			return false;

		for (int i = 0; i <= noOfFilledKeys; i++)
		{
			if (i < keys.size()) {

				if (child->keys.back() < keys[i]) {

					childs.insert(childs.begin() + i, child);
					return true;

				}
			}

		}

		childs.push_back(child);

		return true;


	}


	bool removeKey(T d) {



		keys.erase(d);
		noOfFilledKeys--;

		return 0;




	}

	T removeKeyIndex(int i) {

		T ans = -1;

		if (i < noOfFilledKeys) {
			ans = keys[i];
			keys.erase(ans);
			return ans;
		}


		return -1;




	}

	int searchKey(T d) {
		for (int i = 0; i < order; i++)
		{
			if (keys[i] == d) {
				return i;
			}
		}
		return -1;
	}

	void clearNode() {

		keys.clear();
		childs.clear();

		noOfFilledKeys = 0;
	}

	void bubbleSort() {


		for (int step = 0; step < noOfFilledKeys; ++step) {

			for (int i = 0; i < noOfFilledKeys - step - 1; ++i) {

				if (keys[i] > keys[i + 1]) {

					T temp = keys[i];
					keys[i] = keys[i + 1];
					keys[i + 1] = temp;
				}
			}
		}
	}

	void printKeys() {


		cout <<  "[ ";
		for (int i = 0; i < noOfFilledKeys; i++)
		{
			T val = keys[i];
			cout << val << " ";
		}

		cout << "]";
	}

	bool isFull(BTreeNode<T>* node) {

		if (node->noOfFilledKeys == order - 1) {
			return true;
		}

		return false;

	}


};




