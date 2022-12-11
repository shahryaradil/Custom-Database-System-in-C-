#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include "BTree.h"

using namespace std;

#include <iostream>
using namespace std;

class Data {
public:
	int id;
	int deaths;
	float adjDeathRate;
	string sCauseName;
	string causeName;
	string state;

	Data() {
		id = 0;
		deaths = 0;
		adjDeathRate = 0;
		sCauseName = "";
		causeName = "";
		state = "";
	}

	Data(int i, int d, float adjD, string sC, string c, string s) {
		id = i;
		deaths = d;
		adjDeathRate = adjD;
		sCauseName = sC;
		causeName = c;
		state = s;
	}

	bool operator == (Data& obj) {
		if (obj.id == id && obj.deaths == deaths && obj.adjDeathRate == adjDeathRate && obj.sCauseName == sCauseName && obj.causeName == causeName && obj.state == state)
		{
			return true;
		}
		else {
			return false;
		}
	}

	bool operator != (Data& obj) {
		if (obj.id == id && obj.deaths == deaths && obj.adjDeathRate == adjDeathRate && obj.sCauseName == sCauseName && obj.causeName == causeName && obj.state == state)
		{
			return false;
		}
		else {
			return true;
		}
	}

	void operator = (Data& obj) {
		id = obj.id;
		deaths = obj.deaths;
		adjDeathRate = obj.adjDeathRate;
		sCauseName = obj.sCauseName;
		causeName = obj.causeName;
		state = obj.state;
	}
};

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
		listNode* temp;
		listNode* prev;
		if (head != NULL)
		{
			if (head->data == s)
			{
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
		if (ptr == nullptr)
		{
			ptr = new Node<T>(x);
			ptr->line.insert(l);
			ptr->location.insert(loc);
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
				ptr = ptr->left;
				delete temp;
			}
			else if (ptr->left == NULL)
			{
				temp = ptr;
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
			inorder(ptr->left);
			cout << ptr->data << endl;
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
};

int main()
{
	queue<string> fileQueue;
	fileQueue.push("NCHS_-_Leading_Causes_of_Death__United_States_1.csv");
	fileQueue.push("NCHS_-_Leading_Causes_of_Death__United_States_2.csv");
	fileQueue.push("NCHS_-_Leading_Causes_of_Death__United_States_3.csv");
	fileQueue.push("NCHS_-_Leading_Causes_of_Death__United_States_4.csv");
	fileQueue.push("NCHS_-_Leading_Causes_of_Death__United_States_5.csv");
	fileQueue.push("NCHS_-_Leading_Causes_of_Death__United_States_6.csv");
	fileQueue.push("NCHS_-_Leading_Causes_of_Death__United_States_7.csv");
	fileQueue.push("NCHS_-_Leading_Causes_of_Death__United_States_8.csv");
	fileQueue.push("NCHS_-_Leading_Causes_of_Death__United_States_9.csv");
	fileQueue.push("NCHS_-_Leading_Causes_of_Death__United_States_10.csv");
	AVL<int> avlTreeInt;
	AVL<float> avlTreeFloat;
	AVL<string> avlTreeString;

	BTree <int> bTreeInt(4);
	BTree <float> bTreeFloat(4);
	BTree <string> bTreeString(4);

	char treechoice = '&', idchoice = '$', opchoice = '&';
	int bTreeOrder = 0;
	while ((treechoice != '1') && (treechoice != '2') && (treechoice != '3'))
	{
		cout << "----------------------------------\nSimple Database Management System\n----------------------------------\n\n";
		cout << "Choose a tree:\n1. AVL Tree\n2. B-Tree\n3. Red-Black Tree\n\n";
		cin >> treechoice;
		system("CLS");
	}
	if (treechoice == '2')
	{
		cout << "----------------------------------\nSimple Database Management System\n----------------------------------\n\n";
		cout << "Enter B-Tree order:\n\n";
		cin >> bTreeOrder;
		system("CLS");
	}
	while ((idchoice != '1') && (idchoice != '2') && (idchoice != '3') && (idchoice != '4') && (idchoice != '5') && (idchoice != '6') && (idchoice != '7'))
	{
		cout << "----------------------------------\nSimple Database Management System\n----------------------------------\n\n";
		cout << "Choose a field to perform indexing:\n1. ID\n2. Year\n3. 113 Cause Name\n4. Cause Name\n5. State\n6. Deaths\n7. Age Adjusted Death-rate\n\n";
		cin >> idchoice;
		system("CLS");
	}
	idchoice--;
	while (!fileQueue.empty())
	{
		string myFilePath = fileQueue.front();
		fileQueue.pop();
		string lineInp, wordInp;
		vector<vector<string>> fileInp;
		vector<string> rowData;
		string temp1;
		fstream file(myFilePath, ios::in);
		if (file.is_open())
		{
			while (getline(file, lineInp))
			{
				rowData.clear();
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
						/*string temp1 = wordInp;
						getline(str, wordInp, ',');
						string temp2 = wordInp;
						temp1 += ',';
						temp1 += temp2;
						wordInp = temp1;*/
					}
					rowData.push_back(wordInp);
				}
				fileInp.push_back(rowData);
			}
		}
		else
		{
			cout << "File not present.";
		}
		file.close();

		if (idchoice == '0' || idchoice == '1' || idchoice == '5') //int
		{

			if (idchoice == '0') //id
			{
				for (int i = 1; i < fileInp.size(); i++)
				{
					bTreeInt.insert(stoi(fileInp[i][0]), myFilePath, i + 1);
				}
				//bTreeInt.displayLL(bTreeInt.root);
			}
			else if (idchoice == '1') //year
			{
				for (int i = 1; i < fileInp.size(); i++)
				{
					bTreeInt.insert(stoi(fileInp[i][1]), myFilePath, i + 1);

				}
				//bTreeInt.displayLL(bTreeInt.root);
			}
			else if (idchoice == '5') //deaths
			{
				for (int i = 1; i < fileInp.size(); i++)
				{
					bTreeInt.insert(stoi(fileInp[i][5]), myFilePath, i + 1);

				}
				//bTreeInt.displayLL(bTreeInt.root);
			}
		}
		if (idchoice == '6') //float
		{
			if (idchoice == '6')
			{
				for (int i = 1; i < fileInp.size(); i++)
				{
					bTreeFloat.insert(stof(fileInp[i][6]), myFilePath, i + 1);

				}
				//avlTreeFloat.displayLL(avlTreeFloat.root);
			}
		}
		if (idchoice == '2' || idchoice == '3' || idchoice == '4') //string
		{
			if (idchoice == '2') //113 cause name
			{
				for (int i = 1; i < fileInp.size(); i++)
				{
					bTreeString.insert(fileInp[i][2], myFilePath, i + 1);

				}
				//avlTreeString.displayLL(avlTreeString.root);
			}
			else if (idchoice == '3') //cause name
			{
				for (int i = 1; i < fileInp.size(); i++)
				{
					bTreeString.insert(fileInp[i][3], myFilePath, i + 1);

				}
				//avlTreeString.displayLL(avlTreeString.root);
			}
			else if (idchoice == '4') //state
			{
				for (int i = 1; i < fileInp.size(); i++)
				{
					bTreeString.insert(fileInp[i][4], myFilePath, i + 1);

				}
				//avlTreeString.displayLL(avlTreeString.root);
			}
		}
	}


	while ((opchoice != '1') && (opchoice != '2') && (opchoice != '3') && (opchoice != '4') && (opchoice != '5'))
	{
		cout << "----------------------------------\nSimple Database Management System\n----------------------------------\n\n";
		cout << "Choose operation to perform:\n1. Create index\n2. Point search\n3. Range Search\n4. Update key, field, old value, new value\n5. Delete key\n\n";
		cin >> opchoice;
		system("CLS");
	}

	//bTreeString.removeIndex("Accidents (unintentional injuries) (V01-X59,Y85-Y86)");


	if (idchoice == '2' || idchoice == '3' || idchoice == '4')
	{
		//avlTreeString.displayLL(avlTreeString.root);
		bTreeString.traverse();
	}
	if (idchoice == '0' || idchoice == '1' || idchoice == '5')
	{
		//avlTreeInt.displayLL(avlTreeInt.root);
		bTreeInt.traverse();

	}
	if (idchoice == '6')
	{
		//avlTreeFloat.displayLL(avlTreeFloat.root);
		bTreeFloat.traverse();

	}

	//system("CLS");

	//cout << endl << "Display: \n";
	//bTreeString.Display("Alzheimer's disease (G30)");
	//bTreeString.Display("Diabetes mellitus (E10-E14)");

	//bTreeString.removeIndex("Malignant neoplasms (C00-C97)");
	bTreeString.removeIndex("Accidents (unintentional injuries) (V01-X59,Y85-Y86)");
	//bTreeString.removeIndex("All Causes");
	bTreeString.removeIndex("Diabetes mellitus (E10-E14)");
	//bTreeString.Display("Alzheimer's disease (G30)");


	//bTreeString.range("Accidents (unintentional injuries) (V01-X59,Y85-Y86)", "Alzheimer's disease (G30)");
	//bTreeInt.range(2, 20);
	//bTreeInt.Display(2);

	return 0;
}



//#include <iostream>
//#include "BTree.h"
//
////#include "BTree.h"
//
//using namespace std;
//
//int main() {
//
//	BTree<int> t(6); // A B-Tree with minimum degree 3
//
//	/*t.insert(10);
//	t.insert(20);
//	t.insert(5);
//	t.insert(6);
//	t.insert(12);
//	t.insert(30);
//	t.insert(7);
//	t.insert(17);
//
//
//	cout << "Traversal of the constructed tree is ";
//	t.traverse();
//
//	int k = 6;
//	(t.search(k) != NULL) ? cout << "\nPresent" : cout << "\nNot Present";
//
//	k = 15;
//	(t.search(k) != NULL) ? cout << "\nPresent" : cout << "\nNot Present";*/
//
//
//
//
//	t.insert(1,"a",69);
//	t.insert(3,"a",69);
//	t.insert(7,"a",69);
//	t.insert(10, "b", 6969);
//	t.insert(11, "b", 6969);
//	t.insert(13,"b",6969);
//	t.insert(14,"b",6969);
//	t.insert(15,"b",6969);
//	t.insert(18,"b",6969);
//	t.insert(16,"b",6969);
//	t.insert(19,"b",6969);
//	t.insert(24,"b",6969);
//	t.insert(25,"b",6969);
//	t.insert(26,"b",6969);
//	t.insert(21,"b",6969);
//	t.insert(4, "b", 6969);
//	t.insert(5, "b", 6969);
//	t.insert(20, "b", 6969);
//	t.insert(22, "b", 6969);
//	t.insert(2, "b", 6969);
//	t.insert(17, "b", 6969);
//	t.insert(12, "b", 6969);
//	t.insert(6, "b", 6969);
//
//	cout << "Traversal of tree constructed is\n";
//	t.traverse();
//	cout << endl;
//
//	/*t.remove(6);
//	cout << "Traversal of tree after removing 6\n";
//	t.traverse();
//	cout << endl;
//
//	t.remove(13);
//	cout << "Traversal of tree after removing 13\n";
//	t.traverse();
//	cout << endl;
//
//	t.remove(7);
//	cout << "Traversal of tree after removing 7\n";
//	t.traverse();
//	cout << endl;
//
//	t.remove(4);
//	cout << "Traversal of tree after removing 4\n";
//	t.traverse();
//	cout << endl;
//
//	t.remove(2);
//	cout << "Traversal of tree after removing 2\n";
//	t.traverse();
//	cout << endl;
//
//	t.remove(16);
//	cout << "Traversal of tree after removing 16\n";
//	t.traverse();
//	cout << endl;*/
//
//
//
//	return 0;
//}
//

