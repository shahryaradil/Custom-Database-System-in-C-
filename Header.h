#pragma once
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

template <class T, class X>
class Node
{
public:
	T vertex;
	X edge;
	Node* next;

	Node()
	{
		vertex = 0;
		edge = 0;
		next = NULL;
	}

	Node(T d, X weight, Node* n)
	{
		setData(d, weight);
		setNext(n);
	}

	Node(T d, X weight)
	{
		setData(d, weight);
		next = NULL;

	}

	void setData(T d, X weight)
	{
		vertex = d;
		edge = weight;
	}

	void setNext(Node* n)
	{
		next = n->next;

	}

	T getVertex()
	{
		return vertex;
	}
	T getEdge()
	{
		return edge;
	}

	Node* getNext()
	{
		return this->next;
	}

};

template <class T, class X>
class SLinkedList {

public:

	Node<T, X>* head;


	SLinkedList()
	{
		head = NULL;
	}

	void insert(T d, X weight) {

		Node<T, X>* nod = new Node <T, X>(d, weight);
		Node<T, X>* temp;
		temp = head;

		while (1)
		{
			if (head == NULL) {

				head = nod;
				break;

			}
			else if (temp->next == NULL) {
				temp->next = nod;
				break;
			}
			else
			{
				temp = temp->next;

			}

		}


	}


	void insertAtHead(T d, X weight) {

		Node<T, X>* nod = new Node <T>(d, weight);
		nod->next = head;
		head = nod;

	}

	bool InsertAtIndex(T d, X weight, int ind) {


		Node<T, X>* nod = new Node <T>(d, weight);
		Node<T, X>* temp;
		temp = head;

		for (int i = 0; 1; i++)
		{

			if (i == ind) {
				nod->next = temp->next;
				temp->next = nod;
				return true;

			}

			if (temp->next == NULL) {
				return false;
			}
			else
			{
				temp = temp->next;

			}

		}


	}

	int searchVertex(T d) {

		Node<T, X>* temp;
		temp = head;

		int i = 0;
		for (i = 0; 1; i++)
		{

			if (temp->vertex == d) {
				return i;
			}

			if (temp->next == NULL) {
				return -1;
			}
			else
			{
				temp = temp->next;

			}

		}
		return -1;

	}

	int searchEdge(T d) {

		Node<T, X>* temp;
		temp = head;

		int i = 0;
		for (i = 0; 1; i++)
		{

			if (temp->edge == d) {
				return i;
			}

			if (temp->next == NULL) {
				return -1;
			}
			else
			{
				temp = temp->next;

			}

		}
		return -1;

	}

	bool updateVertex(int ind, T d) {

		Node<T, X>* temp;
		temp = head;

		for (int i = 0; 1; i++)
		{

			if (i == ind) {
				temp->vertex = d;
				return true;
			}

			if (temp->next == NULL) {
				return false;
			}
			else
			{
				temp = temp->next;

			}

		}

	}

	bool updateEdge(int ind, T d) {

		Node<T, X>* temp;
		temp = head;

		for (int i = 0; 1; i++)
		{

			if (i == ind) {
				temp->edge = d;
				return true;
			}

			if (temp->next == NULL) {
				return false;
			}
			else
			{
				temp = temp->next;

			}

		}

	}


	bool remove(int ind) {

		Node<T, X>* temp;
		Node<T, X>* del;
		temp = head;

		for (int i = 0; 1; i++)
		{

			if (i + 1 == ind) {
				del = temp->next;
				temp->next = temp->next->next;

				delete del;
				return true;

			}

			if (temp->next == NULL) {
				return false;
			}
			else
			{
				temp = temp->next;

			}

		}

	}

	void print() {

		Node<T, X>* temp;
		temp = head;

		int i = 0;
		cout << "( ";
		for (i = 0; temp; i++)
		{

			cout << temp->edge << " , ";

			if (temp->next == NULL) {
				break;
			}
			else
			{
				temp = temp->next;

			}

		}

		cout << "\b)\n";

	}

	void mergeLists(SLinkedList obj2) {

		SLinkedList list;

		Node<T, X>* l1;
		l1 = head;
		Node<T, X>* l2;
		l2 = obj2.head;

		T arr[8] = { 0 };


		for (int i = 0; i < 4; i++)
		{
			arr[i] = l1->vertex;
			l1 = l1->next;


		}
		for (int i = 4; i < 8; i++)
		{
			arr[i] = l2->vertex;
			l2 = l2->next;


		}
		for (int i = 0; i < 8; i++)
		{
			for (int j = i + 1; j < 8; j++)
			{
				if (arr[i] > arr[j]) {
					T temp = arr[i];
					arr[i] = arr[j];
					arr[j] = temp;
				}
			}


		}

		for (int i = 0; i < 8; i++)
		{
			cout << arr[i];


		}

		for (int i = 0; i < 8; i++)
		{

			list.insert(arr[i]);

		}

		this->head = list.head;


	}



};
// A BTree node
template <class T>

class BTreeNode
{
	T* keys; // An array of keys
	string* fileName;
	int* lineNum;
	int order;	 // Minimum degree (defines the range for number of keys)
	BTreeNode** C; // An array of child pointers
	int n;	 // Current number of keys
	bool leaf; // Is true when node is leaf. Otherwise false

public:

	BTreeNode(int _t, bool _leaf) {
		order = _t;
		leaf = _leaf;

		// Allocate memory for maximum number of possible keys
		// and child pointers
		keys = new T[order - 1];
		fileName = new string[order - 1];
		lineNum = new int[order - 1];
		C = new BTreeNode * [order];

		n = 0;
	}
	void traverse() {
		int i;
		for (i = 0; i < n; i++)
		{
			if (leaf == false)
				C[i]->traverse();
			cout << " " << keys[i] << "    fileLocation: " << fileName[i] << "   line number: " << lineNum[i] << endl;
		}

		if (leaf == false)
			C[i]->traverse();
	}

	void Display(T d) {
		fstream file;
		string line;
		int i;
		for (i = 0; i < n; i++)
		{
			if (leaf == false)
				C[i]->Display(d);
			if (d == keys[i]) {
				//cout << " " << keys[i] << "    fileLocation: " << fileName[i] << "   line number: " << lineNum[i] << endl;
				file.open(fileName[i], ios::in);
				for (int j = 1; getline(file, line); j++)
				{
					if (j == lineNum[i]) {
						cout << line << endl;
						line.clear();
					}
				}
				file.close();
			}
		}

		if (leaf == false)
			C[i]->Display(d);
	}


	BTreeNode* search(T k) {
		int i = 0;

		while (i < n && k > keys[i])
			i++;

		if (keys[i] == k) {
			//cout << keys[i];
			return this;
		}

		if (leaf == true)
			return NULL;

		return C[i]->search(k);
	}
	bool searchBool(T k) {
		int i = 0;

		while (i < n && k > keys[i])
			i++;

		if (keys[i] == k) {
			//cout << keys[i];
			return this;
		}

		if (leaf == true)
			return NULL;

		return C[i]->search(k);
	}
	int findKey(T k) {
		int idx = 0;
		while (idx < n && keys[idx] < k)
			++idx;
		return idx;
	}

	void insertNonFull(T k, string file_name, int line_number) {
		int i = n - 1;

		if (leaf == true)
		{
			// The following loop does two things
			// a) Finds the location of new key to be inserted
			// b) Moves all greater keys to one place ahead
			while (i >= 0 && keys[i] > k)
			{
				keys[i + 1] = keys[i];
				fileName[i + 1] = fileName[i];
				lineNum[i + 1] = lineNum[i];
				i--;
			}

			keys[i + 1] = k;
			fileName[i + 1] = file_name;
			lineNum[i + 1] = line_number;

			n = n + 1;
		}
		else 
		{
			while (i >= 0 && keys[i] > k)
				i--;

			if (C[i + 1]->n == order - 1)
			{
				splitChild(i + 1, C[i + 1]);

				// After split, the middle key of C[i] goes up and
				// C[i] is splitted into two. See which of the two
				// is going to have the new key
				if (keys[i + 1] < k)
					i++;
			}
			C[i + 1]->insertNonFull(k, file_name, line_number);
		}
	}

	void splitChild(int i, BTreeNode* y) {
		BTreeNode* z = new BTreeNode(y->order, y->leaf);
		z->n = (order / 2) - 1;

		for (int j = 0; j < (order / 2) - 1; j++) {
			z->keys[j] = y->keys[j + (order / 2)];
			z->fileName[j] = y->fileName[j + (order / 2)];
			z->lineNum[j] = y->lineNum[j + (order / 2)];

		}

		if (y->leaf == false)
		{
			for (int j = 0; j < (order / 2); j++)
				z->C[j] = y->C[j + (order / 2)];
		}

		y->n = (order / 2) - 1;

		for (int j = n; j >= i + 1; j--)
			C[j + 1] = C[j];

		C[i + 1] = z;

		for (int j = n - 1; j >= i; j--) {
			keys[j + 1] = keys[j];
			fileName[j + 1] = fileName[j];
			lineNum[j + 1] = lineNum[j];

		}

		keys[i] = y->keys[(order / 2) - 1];
		fileName[i] = y->fileName[(order / 2) - 1];
		lineNum[i] = y->lineNum[(order / 2) - 1];

		n = n + 1;
	}

	void removeFromFile(T d, vector<string> dup) {
		fstream file, file2;
		bool isFound = true;
		string line;

		int i;
		for (i = 0; i < n; i++)
		{
			if (leaf == false)
				C[i]->removeFromFile(d, dup);
			if (d == keys[i]) {
				//cout << " " << keys[i] << "    fileLocation: " << fileName[i] << "   line number: " << lineNum[i] << endl;
				file.open(fileName[i], ios::in);
				file2.open("temp.csv", ios::out);

				for (int j = 1; getline(file, line); j++)
				{

					for (int i = 0; i < dup.size(); i++)
					{
						if (dup.at(i) == line) {
							isFound = false;
						}

					}
					if (isFound) {
						file2 << line << endl;
						line.clear();
					}
					isFound = true;

				}

				file2.close();
				file.close();
				char tab2[1024];
				strcpy_s(tab2, fileName[i].c_str());
				remove(tab2);
				rename("temp.csv", tab2);
			}



		}


		// Print the subtree rooted with last child
		if (leaf == false)
			C[i]->removeFromFile(d, dup);
	}

	void Removee(T k) {
		int idx = findKey(k);

		// The key to be removed is present in this node
		if (idx < n && keys[idx] == k)
		{

			if (leaf)
				removeFromLeaf(idx);
			else
				removeFromNonLeaf(idx);
		}
		else
		{

			// If this node is a leaf node, then the key is not present in tree
			if (leaf)
			{
				cout << "The key " << k << " is does not exist in the tree\n";
				return;
			}

			bool flag = ((idx == n) ? true : false);

			if (C[idx]->n < (order / 2))
				fill(idx);

			if (flag && idx > n)
				C[idx - 1]->Removee(k);
			else
				C[idx]->Removee(k);
		}
		return;
	}

	void rangeSearch(T min, T max) {
		fstream file;
		string line;
		int i;
		for (i = 0; i < n; i++)
		{
			if (leaf == false) {
				C[i]->rangeSearch(min, max);

			}

			if (keys[i] <= max) {
				if (keys[i] >= min) {

					file.open(fileName[i], ios::in);
					for (int j = 1; getline(file, line); j++)
					{
						if (j == lineNum[i]) {
							cout << line << endl;
							line.clear();
						}
					}
					file.close();
				}
			}
		}

		if (leaf == false)
			C[i]->rangeSearch(min, max);
	}

	void fillDuplicates(T d, vector<string>& dup) {
		fstream file;
		string line;
		int i;
		for (i = 0; i < n; i++)
		{
			if (leaf == false)
				C[i]->fillDuplicates(d, dup);
			if (d == keys[i]) {
				//cout << " " << keys[i] << "    fileLocation: " << fileName[i] << "   line number: " << lineNum[i] << endl;
				file.open(fileName[i], ios::in);
				for (int j = 1; getline(file, line); j++)
				{
					if (j == lineNum[i]) {
						dup.push_back(line);
						line.clear();
					}
				}
				file.close();
			}
		}


		if (leaf == false)
			C[i]->fillDuplicates(d, dup);
	}

	void removeFromLeaf(int idx) {

		for (int i = idx + 1; i < n; ++i) {
			keys[i - 1] = keys[i];
			fileName[i - 1] = fileName[i];
			lineNum[i - 1] = lineNum[i];

		}

		n--;

		return;
	}

	void removeFromNonLeaf(int idx) {

		T k = keys[idx];

		if (C[idx]->n >= (order / 2))
		{
			T pred = getPred(idx);
			keys[idx] = pred;
			C[idx]->Removee(pred);
		}

		else if (C[idx + 1]->n >= (order / 2))
		{
			T succ = getSucc(idx);
			keys[idx] = succ;
			C[idx + 1]->Removee(succ);
		}

		else
		{
			merge(idx);
			C[idx]->Removee(k);
		}
		return;
	}

	T getPred(int idx) {
		BTreeNode* cur = C[idx];
		while (!cur->leaf)
			cur = cur->C[cur->n];

		return cur->keys[cur->n - 1];
	}

	T getSucc(int idx) {
		BTreeNode* cur = C[idx + 1];
		while (!cur->leaf)
			cur = cur->C[0];

		return cur->keys[0];
	}


	void fill(int idx) {
		if (idx != 0 && C[idx - 1]->n >= (order / 2))
			borrowFromPrev(idx);

		else if (idx != n && C[idx + 1]->n >= (order / 2))
			borrowFromNext(idx);

		else
		{
			if (idx != n)
				merge(idx);
			else
				merge(idx - 1);
		}
		return;
	}

	void borrowFromPrev(int idx) {
		BTreeNode* child = C[idx];
		BTreeNode* sibling = C[idx - 1];

	


		for (int i = child->n - 1; i >= 0; --i) {
			child->keys[i + 1] = child->keys[i];
			child->fileName[i + 1] = child->fileName[i];
			child->lineNum[i + 1] = child->lineNum[i];

		}

		if (!child->leaf)
		{
			for (int i = child->n; i >= 0; --i)
				child->C[i + 1] = child->C[i];
		}

		child->keys[0] = keys[idx - 1];
		child->fileName[0] = fileName[idx - 1];
		child->lineNum[0] = lineNum[idx - 1];


		if (!child->leaf)
			child->C[0] = sibling->C[sibling->n];

		keys[idx - 1] = sibling->keys[sibling->n - 1];
		fileName[idx - 1] = sibling->fileName[sibling->n - 1];
		lineNum[idx - 1] = sibling->lineNum[sibling->n - 1];


		child->n += 1;
		sibling->n -= 1;

		return;
	}

	void borrowFromNext(int idx) {
		BTreeNode* child = C[idx];
		BTreeNode* sibling = C[idx + 1];

	
		child->keys[(child->n)] = keys[idx];
		child->fileName[(child->n)] = fileName[idx];
		child->lineNum[(child->n)] = lineNum[idx];

		if (!(child->leaf))
			child->C[(child->n) + 1] = sibling->C[0];

		keys[idx] = sibling->keys[0];
		fileName[idx] = sibling->fileName[0];
		lineNum[idx] = sibling->lineNum[0];

		for (int i = 1; i < sibling->n; ++i) {
			sibling->keys[i - 1] = sibling->keys[i];
			sibling->fileName[i - 1] = sibling->fileName[i];
			sibling->lineNum[i - 1] = sibling->lineNum[i];

		}

		if (!sibling->leaf)
		{
			for (int i = 1; i <= sibling->n; ++i)
				sibling->C[i - 1] = sibling->C[i];
		}

		child->n += 1;
		sibling->n -= 1;

		return;
	}

	

	void merge(int idx) {
		BTreeNode* child = C[idx];
		BTreeNode* sibling = C[idx + 1];


		child->keys[(order / 2) - 1] = keys[idx];
		child->fileName[(order / 2) - 1] = fileName[idx];
		child->lineNum[(order / 2) - 1] = lineNum[idx];

		
		for (int i = 0; i < sibling->n; ++i) {
			child->keys[i + (order / 2)] = sibling->keys[i];
			child->fileName[i + (order / 2)] = sibling->fileName[i];
			child->lineNum[i + (order / 2)] = sibling->lineNum[i];

		}

		if (!child->leaf)
		{
			for (int i = 0; i <= sibling->n; ++i)
				child->C[i + (order / 2)] = sibling->C[i];
		}

		for (int i = idx + 1; i < n; ++i) {
			keys[i - 1] = keys[i];
			fileName[i - 1] = fileName[i];
			lineNum[i - 1] = lineNum[i];

		}

		for (int i = idx + 2; i <= n; ++i)
			C[i - 1] = C[i];

		
		child->n += sibling->n + 1;
		n--;

		
		delete(sibling);
		return;
	}


	template <typename X> friend class BTree;
};



template <class T>

class BTree
{
	BTreeNode<T>* root; 
	int order;
public:

	
	BTree(int orderr)
	{
		root = NULL;
		order = orderr;
	}

	void traverse()
	{
		if (root != NULL) root->traverse();
	}

	BTreeNode<T>* search(T k)
	{
		return (root == NULL) ? NULL : root->search(k);
	}


	void insert(T k, string file_name, int line_number) {
	
		if (root == NULL)
		{
	
			root = new BTreeNode<T>(order, true);
			root->keys[0] = k; 
			root->fileName[0] = file_name; 
			root->lineNum[0] = line_number; 
			root->n = 1; 
		}
		else 
		{
	
			if (root->n == order - 1)
			{

				BTreeNode<T>* s = new BTreeNode<T>(order, false);

				s->C[0] = root;

				s->splitChild(0, root);

		
				int i = 0;
				if (s->keys[0] < k)
					i++;
				s->C[i]->insertNonFull(k, file_name, line_number);

				root = s;
			}
			else 
				root->insertNonFull(k, file_name, line_number);
		}
	}


	void Removee(T k)
	{
		if (!root)
		{
			cout << "The tree is empty\n";
			return;
		}

		root->Removee(k);

		if (root->n == 0)
		{
			BTreeNode<T>* tmp = root;
			if (root->leaf)
				root = NULL;
			else
				root = root->C[0];

		
			delete tmp;
		}
		return;
	}

	void PointSearch(T d) {

		BTreeNode<T>* temp = root->search(d);
		root->Display(d);


	}
	void deleteWithKey(T d) {


		BTreeNode<T>* temo = root->search(d);
		vector<string> dup;
		root->fillDuplicates(d, dup);
		root->removeFromFile(d, dup);
		int i = 0;
		while (i < 1000) {
			Removee(d);
			++i;
		}
		//cout << this->search(d) << endl;
		temo->traverse();

	}
	void rangeSearchh(T min, T max) {

		BTreeNode<T>* temp = root->search(min);

		root->rangeSearch(min, max);

	}

};
