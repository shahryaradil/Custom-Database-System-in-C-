#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>

using namespace std;


//class Data {
//public:
//	int id;
//	int deaths;
//	float adjDeathRate;
//	string sCauseName;
//	string causeName;
//	string state;
//
//	Data() {
//		id = 0;
//		deaths = 0;
//		adjDeathRate = 0;
//		sCauseName = "";
//		causeName = "";
//		state = "";
//	}
//
//	Data(int i, int d, float adjD, string sC, string c, string s) {
//		id = i;
//		deaths = d;
//		adjDeathRate = adjD;
//		sCauseName = sC;
//		causeName = c;
//		state = s;
//	}
//
//	bool operator == (Data& obj) {
//		if (obj.id == id && obj.deaths == deaths && obj.adjDeathRate == adjDeathRate && obj.sCauseName == sCauseName && obj.causeName == causeName && obj.state == state)
//		{
//			return true;
//		}
//		else {
//			return false;
//		}
//	}
//
//	bool operator != (Data& obj) {
//		if (obj.id == id && obj.deaths == deaths && obj.adjDeathRate == adjDeathRate && obj.sCauseName == sCauseName && obj.causeName == causeName && obj.state == state)
//		{
//			return false;
//		}
//		else {
//			return true;
//		}
//	}
//
//	void operator = (Data& obj) {
//		id = obj.id;
//		deaths = obj.deaths;
//		adjDeathRate = obj.adjDeathRate;
//		sCauseName = obj.sCauseName;
//		causeName = obj.causeName;
//		state = obj.state;
//	}
//};

template <class T>
class listNode {
public:
	T data;
	listNode* next;

	listNode(T x) {
		data = x;
		next = NULL;
	}
};


template <class T>
class duplicateList {
public:
	listNode<T>* head;
	listNode<T>* tail;

	duplicateList() {
		head = NULL;
		tail = NULL;
	}

	void insert(T s) {
		if (head == NULL)
		{
			head = new listNode<T>(s);
			tail = head;
		}
		else
		{
			listNode<T>* temp = new listNode<T>(s);
			tail->next = temp;
			tail = temp;
		}
	}

	void deleteN(T s) {
		listNode<T>* temp;
		listNode<T>* prev;
		if (head != NULL)
		{
			if (head->data == s)
			{
				if (head == tail)
				{
					tail = NULL;
				}
				temp = head;
				head = head->next;
				delete temp;

				return;
			}
			else
			{
				prev = head;
				temp = head->next;

				while (temp->data != s && temp->next != NULL)
				{
					temp = temp->next;
					prev = prev->next;
				}
				if (temp->data == s)
				{
					if (temp == tail)
					{
						tail = prev;
					}
					prev->next = temp->next;
					delete temp;
				}
			}
		}
	}


	void print() {
		listNode<T>* temp = head;

		while (temp != NULL)
		{
			cout << temp->data << endl;
			temp = temp->next;
		}
	}

	void deleteAll() {
		//listNode<T>* temp = head;

		while (head != NULL)
		{
			deleteN(head->data);
		}
	}

	bool search(T x) {
		listNode<T>* temp = head;

		while (temp != NULL)
		{
			if (x == temp->data)
			{
				return true;
			}
			temp = temp->next;
		}

		return false;
	}
};


template <class T>
class Node {
public:
	T data;
	duplicateList<int> line;
	duplicateList<string> location;
	int height;
	Node* left;
	Node* right;

	Node(T x) {
		data = x;
		height = 0;
		left = nullptr;
		right = nullptr;
	}
};


template <class T>
class AVL {
public:
	Node<T>* root;

	AVL() {
		root = nullptr;
	}

	Node<T>* RR(Node<T>* ptr) {
		Node<T>* holder;
		holder = ptr->left;
		ptr->left = holder->right;
		holder->right = ptr;

		ptr->height = findMax(getHeight(ptr->left), getHeight(ptr->right)) + 1;
		holder->height = findMax(getHeight(holder->left), getHeight(holder->right)) + 1;

		return holder;
	}

	Node<T>* LL(Node<T>* ptr) {
		Node<T>* holder;
		holder = ptr->right;
		ptr->right = holder->left;
		holder->left = ptr;

		ptr->height = findMax(getHeight(ptr->left), getHeight(ptr->right)) + 1;
		holder->height = findMax(getHeight(holder->left), getHeight(holder->right)) + 1;

		return holder;
	}

	Node<T>* insert(T x, int l, string loc, Node<T>* ptr) {

		fstream filee;

		if (ptr == nullptr)
		{
			ptr = new Node<T>(x);
			ptr->line.insert(l);
			ptr->location.insert(loc);
			filee.open("AVLTree.txt", ios::out | ios::app);
			filee << x << "," << loc << "," << l << "," << endl;
			filee.close();
		}
		else if (x < ptr->data) {
			ptr->left = insert(x, l, loc, ptr->left);

			if (getHeight(ptr->left) - getHeight(ptr->right) == 2)
			{
				if (x < ptr->left->data)
				{
					ptr = RR(ptr);
				}
				else {
					ptr->left = LL(ptr->left);
					ptr = RR(ptr);
				}
			}
		}
		else if (x > ptr->data) {
			ptr->right = insert(x, l, loc, ptr->right);
			if (getHeight(ptr->left) - getHeight(ptr->right) == -2)
			{
				if (x > ptr->right->data)
				{
					ptr = LL(ptr);
				}
				else {
					ptr->right = RR(ptr->right);
					ptr = LL(ptr);
				}
			}
		}
		else if (ptr->data == x)
		{
			ptr->line.insert(l);
			ptr->location.insert(loc);
			filee.open("AVLTree.txt", ios::out | ios::app);
			filee << x << "," << loc << "," << l << "," << endl;
			filee.close();
		}

		ptr->height = findMax(getHeight(ptr->left), getHeight(ptr->right)) + 1;

		return ptr;
	}

	Node<T>* deletion(T x, Node<T>* ptr) {
		Node<T>* temp;
		if (ptr == NULL) {
			return ptr;
		}

		else if (ptr->data > x)
		{
			ptr->left = deletion(x, ptr->left);
		}

		else if (ptr->data < x)
		{
			ptr->right = deletion(x, ptr->right);
		}

		else
		{
			if (ptr->right == NULL)
			{
				temp = ptr;
				//ptr->location.deleteAll();
				//ptr->line.deleteAll();
				ptr = ptr->left;
				delete temp;
			}
			else if (ptr->left == NULL)
			{
				temp = ptr;
				//ptr->location.deleteAll();
				//ptr->line.deleteAll();
				ptr = ptr->right;
				delete temp;
			}
			else
			{
				temp = ptr->right;
				while (temp->left != NULL)
				{
					temp = temp->left;
				}
				ptr->data = temp->data;
				ptr->location.deleteAll();
				ptr->line.deleteAll();
				ptr->line.head = temp->line.head;
				ptr->location.head = temp->location.head;

				ptr->right = deletion(temp->data, ptr->right);

			}
		}

		if (ptr != NULL)
		{
			ptr->height = findMax(getHeight(ptr->left), getHeight(ptr->right)) + 1;

			if (getHeight(ptr->left) - getHeight(ptr->right) == 2) {
				if (getHeight(ptr->left->left) - getHeight(ptr->left->right) >= 0)
				{
					ptr = RR(ptr);
				}
				else
				{
					ptr->left = LL(ptr->left);
					ptr = RR(ptr);
				}
			}

			if (getHeight(ptr->left) - getHeight(ptr->right) == -2) {
				if (getHeight(ptr->right->left) - getHeight(ptr->right->right) <= 0)
				{
					ptr = LL(ptr);
				}
				else
				{
					ptr->right = RR(ptr->right);
					ptr = LL(ptr);
				}
			}
		}

		return ptr;
	}


	int findMax(int ptr1, int ptr2) {
		if (ptr1 > ptr2)
		{
			return ptr1;
		}
		else
		{
			return ptr2;
		}
	}

	int getHeight(Node<T>* ptr) {
		if (ptr == nullptr) {
			return -1;
		}
		else {
			return ptr->height;
		}
	}

	void inorder(Node<T>* ptr) {
		if (ptr != nullptr)
		{
			cout << ptr->data << endl;
			inorder(ptr->left);
			//ptr->line.print();
			inorder(ptr->right);
		}
	}
	void displayLL(Node<T>* ptr)
	{
		if (ptr != nullptr)
		{
			displayLL(ptr->left);
			ptr->line.print();
			displayLL(ptr->right);
		}
	}

	void displayRecords(T key, Node<T>* ptr) {
		if (ptr != NULL)
		{
			if (ptr->data > key)
			{
				displayRecords(key, ptr->left);
			}
			else if (ptr->data < key)
			{
				displayRecords(key, ptr->right);
			}
			else {
				string temp1, lineInp, wordInp;
				Node<T>* temp = ptr;
				listNode<int>* linet = temp->line.head;
				listNode<string>* loct = temp->location.head;

				while (linet != NULL)
				{
					fstream file(loct->data, ios::in);

					for (int i = 0; i < linet->data; i++)
					{
						getline(file, lineInp);
					}
					//getline(file, lineInp);
					if (file.is_open())
					{
						stringstream str(lineInp);
						while (getline(str, wordInp, ','))
						{
							if (wordInp[0] == '"')
							{
								while (wordInp[wordInp.length() - 1] != '"')
								{
									temp1 = temp1 + wordInp;
									temp1 += ',';
									getline(str, wordInp, ',');
								}
								temp1 = temp1 + wordInp;
								wordInp = temp1;
								temp1 = "";
							}
							cout << wordInp << " ";
						}
						cout << endl;
					}
					else
					{
						cout << "File not present.";
					}
					file.close();

					linet = linet->next;
					loct = loct->next;
				}
			}
		}
	}

	void deleteRecords(T key, Node<T>* ptr) {
		if (ptr != NULL)
		{
			if (ptr->data > key)
			{
				deleteRecords(key, ptr->left);
			}
			else if (ptr->data < key)
			{
				deleteRecords(key, ptr->right);
			}
			else {
				string temp1, lineInp, wordInp;
				Node<T>* temp = ptr;
				listNode<int>* linet = temp->line.head;
				listNode<string>* loct = temp->location.head;
				duplicateList<string> delete_strings;


				while (linet != NULL)
				{
					fstream file(loct->data, ios::in);

					if (file.is_open())
					{
						for (int i = 1; getline(file, lineInp); i++)
						{
							if (i == linet->data)
							{
								delete_strings.insert(lineInp);
							}
							lineInp = "";
						}
					}
					else
					{
						cout << "File not present.";
					}
					file.close();
					linet = linet->next;
					loct = loct->next;
				}

				Update(delete_strings);
				delete_strings.deleteAll();
				ptr = deletion(ptr->data, ptr);
			}

		}
	}

	void Update(duplicateList<string>& sl) {
		queue<string> fileQueue;
		/*fileQueue.push("NCHS_-_Leading_Causes_of_Death__United_States_2.csv");
		fileQueue.push("NCHS_-_Leading_Causes_of_Death__United_States_3.csv");
		fileQueue.push("NCHS_-_Leading_Causes_of_Death__United_States_4.csv");
		fileQueue.push("NCHS_-_Leading_Causes_of_Death__United_States_5.csv");
		fileQueue.push("NCHS_-_Leading_Causes_of_Death__United_States_6.csv");
		fileQueue.push("NCHS_-_Leading_Causes_of_Death__United_States_7.csv");
		fileQueue.push("NCHS_-_Leading_Causes_of_Death__United_States_9.csv");
		fileQueue.push("NCHS_-_Leading_Causes_of_Death__United_States_10.csv");*/
		fileQueue.push("NCHS_-_Leading_Causes_of_Death__United_States_1.csv");
		fileQueue.push("NCHS_-_Leading_Causes_of_Death__United_States_8.csv");

		while (!fileQueue.empty())
		{
			string myFilePath = fileQueue.front();
			fileQueue.pop();
			string lineInp, wordInp;
			string temp1;
			fstream file(myFilePath, ios::in);
			fstream file1("temp.csv", ios::out);
			if (file.is_open())
			{
				while (getline(file, lineInp))
				{

					if (!sl.search(lineInp))
					{
						file1 << lineInp;
						file1 << "\n";
					}
					else {
						file1 << "-1,-1,Deleted,Deleted,Deleted,-1,-1,\n";
					}
				}
			}
			else
			{
				cout << "File not present.";
			}
			file.close();
			file1.close();


			char filenamet[1024];
			for (int i = 0; i < 1024; i++)
			{
				filenamet[i] = '\0';
			}
			for (int i = 0; i < myFilePath.length(); i++)
			{
				filenamet[i] = myFilePath[i];
			}
			remove(filenamet);
			rename("temp.csv", filenamet);
		}
	}

	void rangeSearch(T low, T high, Node<T>* ptr) {
		if (ptr == NULL)
		{
			return;
		}
		if (ptr->data > low)
		{
			rangeSearch(low, high, ptr->left);
		}
		if (ptr->data >= low && ptr->data <= high)
		{
			displayRecords(ptr->data, ptr);
		}
		if (ptr->data < high)
		{
			rangeSearch(low, high, ptr->right);
		}
	}
};