#pragma once
#include <iostream>
using namespace std;



template <class T>


class BTreeNode
{
public:

	T* keys = NULL;
	BTreeNode<T>** childs = NULL;
	int order;
	bool isLeaf = 1;
	int noOfFilledKeys = 0;

	BTreeNode()
	{
		keys = NULL;
		childs = NULL;
		order = 0;
		isLeaf = 1;
		noOfFilledKeys = 0;

	}


	BTreeNode(int odr)
	{
		order = odr;
		keys = new T[order - 1]{ NULL };
		childs = new BTreeNode<T>*[order] {NULL};
		isLeaf = 1;
		noOfFilledKeys = 0;

	}

	void setOrder(int odr) {
		this->order = odr;
		keys = new T[order - 1]{ NULL };
		childs = new BTreeNode<T>*[order] {NULL};
		isLeaf = 1;
		noOfFilledKeys = 0;

	}

	bool InsertKey(T d) {



		if (noOfFilledKeys < order - 1) {

			keys[noOfFilledKeys] = d;
			noOfFilledKeys++;
			bubbleSort();
			return 1;

		}

		return 0;




	}

	bool removeKey(T d) {



		for (int i = 0; i < order; i++)
		{
			if (keys[i] == d) {
				keys[i] = INT_MAX;
				bubbleSort();
				noOfFilledKeys--;
				return 1;
			}
		}

		return 0;




	}

	T removeKeyIndex(int i) {



		if (i < noOfFilledKeys) {
			T ans = keys[i];
			keys[i] = INT_MAX;
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

		for (int i = 0; i < noOfFilledKeys; i++)
		{
			keys[i] = INT_MAX;
		}

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


		cout << endl << "[ ";
		for (int i = 0; i < noOfFilledKeys; i++)
		{
			cout << keys[i] << " ";
		}

		cout << "]";
	}




};




