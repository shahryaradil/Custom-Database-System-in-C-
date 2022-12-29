#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include "AVLTree.h"
#include "RedBlack.h"
#include "Btree.h"
#include <filesystem>
#include <direct.h>

using namespace std;
namespace fs = std::filesystem;

void delete_dir_content(const fs::path& dir_path) {
	for (auto& path : fs::directory_iterator(dir_path)) {
		fs::remove_all(path);
	}
}


void mainMenu() {
	queue<string> fileQueue;
	/*fileQueue.push("NCHS_-_Leading_Causes_of_Death__United_States_2.csv");s
	fileQueue.push("NCHS_-_Leading_Causes_of_Death__United_States_3.csv");
	fileQueue.push("NCHS_-_Leading_Causes_of_Death__United_States_4.csv");
	fileQueue.push("NCHS_-_Leading_Causes_of_Death__United_States_5.csv");
	fileQueue.push("NCHS_-_Leading_Causes_of_Death__United_States_6.csv");
	fileQueue.push("NCHS_-_Leading_Causes_of_Death__United_States_7.csv");
	fileQueue.push("NCHS_-_Leading_Causes_of_Death__United_States_9.csv");
	fileQueue.push("NCHS_-_Leading_Causes_of_Death__United_States_10.csv");*/
	fileQueue.push("NCHS_-_Leading_Causes_of_Death__United_States_1.csv");
	fileQueue.push("NCHS_-_Leading_Causes_of_Death__United_States_8.csv");
	AVL<int> avlTreeInt;
	AVL<float> avlTreeFloat;
	AVL<string> avlTreeString;
	RBTree<int> RBTreeInt;
	RBTree<float> RBTreeFloat;
	RBTree<string> RBTreeString;

	//////////////////////////////////////////////////////////////////Manage Directorires//////////////////////////////////////////////////////////////////
	_mkdir("BTree");
	delete_dir_content("./BTree/");
	_mkdir("AVLTree");
	delete_dir_content("./AVLTree/");
	_mkdir("RBTree");
	delete_dir_content("./RBTree/");



	char treechoice = '&', idchoice = '$', opchoice = '&';
	int bTreeOrder = 4;
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
	BTree<int> BtreeInt(bTreeOrder);
	BTree<float> BtreeFloat(bTreeOrder);
	BTree<string> BtreeString(bTreeOrder);
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

		

		if (treechoice == '1')
		{
			if (idchoice == '0' || idchoice == '1' || idchoice == '5') //int
			{

				if (idchoice == '0') //id
				{
					for (int i = 1; i < fileInp.size(); i++)
					{
						avlTreeInt.root = avlTreeInt.insert(stoi(fileInp[i][0]), i + 1, myFilePath, avlTreeInt.root);
						avlTreeInt.storeTree(avlTreeInt.root);

						RBTreeInt.insert(stoi(fileInp[i][0]), i + 1, myFilePath);
						RBTreeInt.storeTree(RBTreeInt.root);

						BtreeInt.insert(stoi(fileInp[i][0]), myFilePath, i + 1);
						BtreeInt.storeTree();

					}
				}
				else if (idchoice == '1') //year
				{
					for (int i = 1; i < fileInp.size(); i++)
					{
						avlTreeInt.root = avlTreeInt.insert(stoi(fileInp[i][1]), i + 1, myFilePath, avlTreeInt.root);
						avlTreeInt.storeTree(avlTreeInt.root);


						RBTreeInt.insert(stoi(fileInp[i][1]), i + 1, myFilePath);
						RBTreeInt.storeTree(RBTreeInt.root);

						BtreeInt.insert(stoi(fileInp[i][1]), myFilePath, i + 1);
						BtreeInt.storeTree();
					}
				}
				else if (idchoice == '5') //deaths
				{
					for (int i = 1; i < fileInp.size(); i++)
					{
						avlTreeInt.root = avlTreeInt.insert(stoi(fileInp[i][5]), i + 1, myFilePath, avlTreeInt.root);
						avlTreeInt.storeTree(avlTreeInt.root);


						RBTreeInt.insert(stoi(fileInp[i][5]), i + 1, myFilePath);
						RBTreeInt.storeTree(RBTreeInt.root);

						BtreeInt.insert(stoi(fileInp[i][5]), myFilePath, i + 1);
						BtreeInt.storeTree();
					}
				}
			}
			if (idchoice == '6') //float
			{
				if (idchoice == '6')
				{
					for (int i = 1; i < fileInp.size(); i++)
					{
						avlTreeFloat.root = avlTreeFloat.insert(stof(fileInp[i][6]), i + 1, myFilePath, avlTreeFloat.root);
						avlTreeFloat.storeTree(avlTreeFloat.root);


						BtreeFloat.insert(stof(fileInp[i][6]), myFilePath, i + 1);
						BtreeFloat.storeTree();

						RBTreeFloat.insert(stof(fileInp[i][6]), i + 1, myFilePath);
						RBTreeFloat.storeTree(RBTreeFloat.root);


					}
				}
			}
			if (idchoice == '2' || idchoice == '3' || idchoice == '4') //string
			{
				if (idchoice == '2') //113 cause name
				{
					for (int i = 1; i < fileInp.size(); i++)
					{
						avlTreeString.root = avlTreeString.insert(fileInp[i][2], i + 1, myFilePath, avlTreeString.root);
						avlTreeString.storeTree(avlTreeString.root);

						BtreeString.insert(fileInp[i][2], myFilePath, i + 1);
						BtreeString.storeTree();

						RBTreeString.insert(fileInp[i][2], i + 1, myFilePath);
						RBTreeString.storeTree(RBTreeString.root);

					}
				}
				else if (idchoice == '3') //cause name
				{
					for (int i = 1; i < fileInp.size(); i++)
					{
						avlTreeString.root = avlTreeString.insert(fileInp[i][3], i + 1, myFilePath, avlTreeString.root);
						avlTreeString.storeTree(avlTreeString.root);


						BtreeString.insert(fileInp[i][3], myFilePath, i + 1);
						BtreeString.storeTree();
						RBTreeString.insert(fileInp[i][3], i + 1, myFilePath);
						RBTreeString.storeTree(RBTreeString.root);


					}
				}
				else if (idchoice == '4') //state
				{
					for (int i = 1; i < fileInp.size(); i++)
					{
						avlTreeString.root = avlTreeString.insert(fileInp[i][4], i + 1, myFilePath, avlTreeString.root);
						avlTreeString.storeTree(avlTreeString.root);


						BtreeString.insert(fileInp[i][4], myFilePath, i + 1);
						RBTreeString.insert(fileInp[i][4], i + 1, myFilePath);
						RBTreeString.storeTree(RBTreeString.root);

					}
				}
			}
		}
		else if (treechoice == '2')
		{
			if (idchoice == '0' || idchoice == '1' || idchoice == '5') //int
			{

				if (idchoice == '0') //id
				{
					for (int i = 1; i < fileInp.size(); i++)
					{
						avlTreeInt.root = avlTreeInt.insert(stoi(fileInp[i][0]), i + 1, myFilePath, avlTreeInt.root);
						avlTreeInt.storeTree(avlTreeInt.root);


						RBTreeInt.insert(stoi(fileInp[i][0]), i + 1, myFilePath);
						RBTreeInt.storeTree(RBTreeInt.root);

						BtreeInt.insert(stoi(fileInp[i][0]), myFilePath, i + 1);
						BtreeInt.storeTree();

					}
				}
				else if (idchoice == '1') //year
				{
					for (int i = 1; i < fileInp.size(); i++)
					{
						avlTreeInt.root = avlTreeInt.insert(stoi(fileInp[i][1]), i + 1, myFilePath, avlTreeInt.root);
						avlTreeInt.storeTree(avlTreeInt.root);


						RBTreeInt.insert(stoi(fileInp[i][1]), i + 1, myFilePath);
						RBTreeInt.storeTree(RBTreeInt.root);

						BtreeInt.insert(stoi(fileInp[i][1]), myFilePath, i + 1);
						BtreeInt.storeTree();
					}
				}
				else if (idchoice == '5') //deaths
				{
					for (int i = 1; i < fileInp.size(); i++)
					{
						avlTreeInt.root = avlTreeInt.insert(stoi(fileInp[i][5]), i + 1, myFilePath, avlTreeInt.root);
						avlTreeInt.storeTree(avlTreeInt.root);


						RBTreeInt.insert(stoi(fileInp[i][5]), i + 1, myFilePath);
						RBTreeInt.storeTree(RBTreeInt.root);

						BtreeInt.insert(stoi(fileInp[i][5]), myFilePath, i + 1);
						BtreeInt.storeTree();
					}
				}
			}
			if (idchoice == '6') //float
			{
				if (idchoice == '6')
				{
					for (int i = 1; i < fileInp.size(); i++)
					{
						avlTreeFloat.root = avlTreeFloat.insert(stof(fileInp[i][6]), i + 1, myFilePath, avlTreeFloat.root);
						avlTreeFloat.storeTree(avlTreeFloat.root);

						BtreeFloat.insert(stof(fileInp[i][6]), myFilePath, i + 1);
						BtreeFloat.storeTree();

						RBTreeFloat.insert(stof(fileInp[i][6]), i + 1, myFilePath);
						RBTreeFloat.storeTree(RBTreeFloat.root);


					}
				}
			}
			if (idchoice == '2' || idchoice == '3' || idchoice == '4') //string
			{
				if (idchoice == '2') //113 cause name
				{
					for (int i = 1; i < fileInp.size(); i++)
					{
						avlTreeString.root = avlTreeString.insert(fileInp[i][2], i + 1, myFilePath, avlTreeString.root);
						avlTreeString.storeTree(avlTreeString.root);


						BtreeString.insert(fileInp[i][2], myFilePath, i + 1);
						BtreeString.storeTree();
						RBTreeString.insert(fileInp[i][2], i + 1, myFilePath);
						RBTreeString.storeTree(RBTreeString.root);

					}
				}
				else if (idchoice == '3') //cause name
				{
					for (int i = 1; i < fileInp.size(); i++)
					{
						avlTreeString.root = avlTreeString.insert(fileInp[i][3], i + 1, myFilePath, avlTreeString.root);
						avlTreeString.storeTree(avlTreeString.root);

						BtreeString.insert(fileInp[i][3], myFilePath, i + 1);
						BtreeString.storeTree();
						RBTreeString.insert(fileInp[i][3], i + 1, myFilePath);
						RBTreeString.storeTree(RBTreeString.root);


					}
				}
				else if (idchoice == '4') //state
				{
					for (int i = 1; i < fileInp.size(); i++)
					{
						avlTreeString.root = avlTreeString.insert(fileInp[i][4], i + 1, myFilePath, avlTreeString.root);
						avlTreeString.storeTree(avlTreeString.root);

						BtreeString.insert(fileInp[i][4], myFilePath, i + 1);
						BtreeString.storeTree();
						RBTreeString.insert(fileInp[i][4], i + 1, myFilePath);
						RBTreeString.storeTree(RBTreeString.root);

					}
				}
			}
		}
		else if (treechoice == '3')
		{
			if (idchoice == '0' || idchoice == '1' || idchoice == '5') //int
			{

				if (idchoice == '0') //id
				{
					for (int i = 1; i < fileInp.size(); i++)
					{
						avlTreeInt.root = avlTreeInt.insert(stoi(fileInp[i][0]), i + 1, myFilePath, avlTreeInt.root);
						avlTreeInt.storeTree(avlTreeInt.root);

						RBTreeInt.insert(stoi(fileInp[i][0]), i + 1, myFilePath);
						RBTreeInt.storeTree(RBTreeInt.root);

						BtreeInt.insert(stoi(fileInp[i][0]), myFilePath, i + 1);
						BtreeInt.storeTree();

					}
				}
				else if (idchoice == '1') //year
				{
					for (int i = 1; i < fileInp.size(); i++)
					{
						avlTreeInt.root = avlTreeInt.insert(stoi(fileInp[i][1]), i + 1, myFilePath, avlTreeInt.root);
						avlTreeInt.storeTree(avlTreeInt.root);

						RBTreeInt.insert(stoi(fileInp[i][1]), i + 1, myFilePath);
						RBTreeInt.storeTree(RBTreeInt.root);

						BtreeInt.insert(stoi(fileInp[i][1]), myFilePath, i + 1);
						BtreeInt.storeTree();
					}
				}
				else if (idchoice == '5') //deaths
				{
					for (int i = 1; i < fileInp.size(); i++)
					{
						avlTreeInt.root = avlTreeInt.insert(stoi(fileInp[i][5]), i + 1, myFilePath, avlTreeInt.root);
						avlTreeInt.storeTree(avlTreeInt.root);

						RBTreeInt.insert(stoi(fileInp[i][5]), i + 1, myFilePath);
						RBTreeInt.storeTree(RBTreeInt.root);

						BtreeInt.insert(stoi(fileInp[i][5]), myFilePath, i + 1);
						BtreeInt.storeTree();
					}
				}
			}
			if (idchoice == '6') //float
			{
				if (idchoice == '6')
				{
					for (int i = 1; i < fileInp.size(); i++)
					{
						avlTreeFloat.root = avlTreeFloat.insert(stof(fileInp[i][6]), i + 1, myFilePath, avlTreeFloat.root);
						avlTreeFloat.storeTree(avlTreeFloat.root);

						BtreeFloat.insert(stof(fileInp[i][6]), myFilePath, i + 1);
						BtreeFloat.storeTree();

						RBTreeFloat.insert(stof(fileInp[i][6]), i + 1, myFilePath);
						RBTreeFloat.storeTree(RBTreeFloat.root);


					}
				}
			}
			if (idchoice == '2' || idchoice == '3' || idchoice == '4') //string
			{
				if (idchoice == '2') //113 cause name
				{
					for (int i = 1; i < fileInp.size(); i++)
					{
						avlTreeString.root = avlTreeString.insert(fileInp[i][2], i + 1, myFilePath, avlTreeString.root);
						avlTreeString.storeTree(avlTreeString.root);

						BtreeString.insert(fileInp[i][2], myFilePath, i + 1);
						BtreeString.storeTree();
						RBTreeString.insert(fileInp[i][2], i + 1, myFilePath);
						RBTreeString.storeTree(RBTreeString.root);

					}
				}
				else if (idchoice == '3') //cause name
				{
					for (int i = 1; i < fileInp.size(); i++)
					{
						avlTreeString.root = avlTreeString.insert(fileInp[i][3], i + 1, myFilePath, avlTreeString.root);
						avlTreeString.storeTree(avlTreeString.root);

						BtreeString.insert(fileInp[i][3], myFilePath, i + 1);
						BtreeString.storeTree();
						RBTreeString.insert(fileInp[i][3], i + 1, myFilePath);
						RBTreeString.storeTree(RBTreeString.root);


					}
				}
				else if (idchoice == '4') //state
				{
					for (int i = 1; i < fileInp.size(); i++)
					{
						avlTreeString.root = avlTreeString.insert(fileInp[i][4], i + 1, myFilePath, avlTreeString.root);
						avlTreeString.storeTree(avlTreeString.root);

						BtreeString.insert(fileInp[i][4], myFilePath, i + 1);
						BtreeString.storeTree();
						RBTreeString.insert(fileInp[i][4], i + 1, myFilePath);
						RBTreeString.storeTree(RBTreeString.root);

					}
				}
			}
		}
	}
	while ((opchoice != '1') && (opchoice != '2') && (opchoice != '3') && (opchoice != '4') && (opchoice != '5'))
	{
		cout << "----------------------------------\nSimple Database Management System\n----------------------------------\n\n";
		cout << "Choose operation to perform:\n1. Point search\n2. Range Search\n3. Update key, field, old value, new value\n4. Delete key\n5. Print Tree\n";
		cin >> opchoice;
		system("CLS");
	}

	char menuchoice;

	if (treechoice == '1')
	{
		if (idchoice == '0' || idchoice == '1' || idchoice == '5')
		{
			int keyinput, keyinput1;
			if (opchoice == '1')
			{
				cout << "----------------------------------\nSimple Database Management System\n----------------------------------\n\n";
				cout << "Enter Key to display record : ";
				cin >> keyinput;
				system("CLS");
				avlTreeInt.displayRecords(keyinput, avlTreeInt.root);
			}
			else if (opchoice == '2')
			{
				cout << "----------------------------------\nSimple Database Management System\n----------------------------------\n\n";
				cout << "Enter Minimum Value : ";
				cin >> keyinput;
				cout << "Enter Maximum Value : ";
				cin >> keyinput1;
				system("CLS");
				avlTreeInt.rangeSearch(keyinput, keyinput1, avlTreeInt.root);
			}
			else if (opchoice == '4')
			{
				cout << "----------------------------------\nSimple Database Management System\n----------------------------------\n\n";
				cout << "Enter Minimum Value : ";
				cin >> keyinput;
				system("CLS");
				avlTreeInt.deleteRecords(keyinput, avlTreeInt.root);
				RBTreeInt.deleteRecords(keyinput, RBTreeInt.root);
				BtreeInt.deleteWithKey(keyinput);

				_mkdir("AVLTree");
				delete_dir_content("./AVLTree/");
				_mkdir("RBTree");
				delete_dir_content("./RBTree/");

				avlTreeInt.storeTree(avlTreeInt.root);
				RBTreeInt.storeTree(RBTreeInt.root);



			}
			else if (opchoice == '5') {
				avlTreeInt.printAVL("", avlTreeInt.root, false);
			}
		}
		if (idchoice == '2' || idchoice == '3' || idchoice == '4')
		{
			string keyinput, keyinput1;
			if (opchoice == '1')
			{
				cout << "----------------------------------\nSimple Database Management System\n----------------------------------\n\n";
				cout << "Enter Key to display record : ";
				cin >> keyinput;
				system("CLS");
				avlTreeString.displayRecords(keyinput, avlTreeString.root);
			}
			else if (opchoice == '2')
			{
				cout << "----------------------------------\nSimple Database Management System\n----------------------------------\n\n";
				cout << "Enter Minimum Value : ";
				cin >> keyinput;
				cout << "Enter Maximum Value : ";
				cin >> keyinput1;
				system("CLS");
				avlTreeString.rangeSearch(keyinput, keyinput1, avlTreeString.root);
			}
			else if (opchoice == '4')
			{
				cout << "----------------------------------\nSimple Database Management System\n----------------------------------\n\n";
				cout << "Enter Key Value : ";
				cin >> keyinput;
				system("CLS");
				avlTreeString.deleteRecords(keyinput, avlTreeString.root);
				RBTreeString.deleteRecords(keyinput, RBTreeString.root);
				BtreeString.deleteWithKey(keyinput);

				_mkdir("AVLTree");
				delete_dir_content("./AVLTree/");
				_mkdir("RBTree");
				delete_dir_content("./RBTree/");

				avlTreeString.storeTree(avlTreeString.root);
				RBTreeString.storeTree(RBTreeString.root);
				
			}
			else if (opchoice == '5') {
				avlTreeString.printAVL("", avlTreeString.root, false);
			}
		}
		if (idchoice == '6')
		{
			float keyinput, keyinput1;
			if (opchoice == '1')
			{
				cout << "----------------------------------\nSimple Database Management System\n----------------------------------\n\n";
				cout << "Enter Key to display record : ";
				cin >> keyinput;
				system("CLS");
				avlTreeFloat.displayRecords(keyinput, avlTreeFloat.root);
			}
			else if (opchoice == '2')
			{
				cout << "----------------------------------\nSimple Database Management System\n----------------------------------\n\n";
				cout << "Enter Minimum Value : ";
				cin >> keyinput;
				cout << "Enter Maximum Value : ";
				cin >> keyinput1;
				system("CLS");
				avlTreeFloat.rangeSearch(keyinput, keyinput1, avlTreeFloat.root);
			}
			else if (opchoice == '4')
			{
				cout << "----------------------------------\nSimple Database Management System\n----------------------------------\n\n";
				cout << "Enter Minimum Value : ";
				cin >> keyinput;
				system("CLS");
				avlTreeFloat.deleteRecords(keyinput, avlTreeFloat.root);
				RBTreeFloat.deleteRecords(keyinput, RBTreeFloat.root);
				BtreeFloat.deleteWithKey(keyinput);

				_mkdir("AVLTree");
				delete_dir_content("./AVLTree/");
				_mkdir("RBTree");
				delete_dir_content("./RBTree/");


				avlTreeFloat.storeTree(avlTreeFloat.root);
				RBTreeFloat.storeTree(RBTreeFloat.root);

			}
			else if (opchoice == '5') {
				avlTreeFloat.printAVL("", avlTreeFloat.root, false);
			}
		}
	}
	if (treechoice == '2')
	{
		if (idchoice == '0' || idchoice == '1' || idchoice == '5')
		{
			int keyinput, keyinput1;
			if (opchoice == '1')
			{
				cout << "----------------------------------\nSimple Database Management System\n----------------------------------\n\n";
				cout << "Enter Key to display record : ";
				cin >> keyinput;
				system("CLS");
				BtreeInt.PointSearch(keyinput);
			}
			else if (opchoice == '2')
			{
				cout << "----------------------------------\nSimple Database Management System\n----------------------------------\n\n";
				cout << "Enter Minimum Value : ";
				cin >> keyinput;
				cout << "Enter Maximum Value : ";
				cin >> keyinput1;
				system("CLS");
				BtreeInt.rangeSearchh(keyinput, keyinput1);
			}
			else if (opchoice == '4')
			{
				cout << "----------------------------------\nSimple Database Management System\n----------------------------------\n\n";
				cout << "Enter Minimum Value : ";
				cin >> keyinput;
				system("CLS");
				avlTreeInt.deleteRecords(keyinput, avlTreeInt.root);
				RBTreeInt.deleteRecords(keyinput, RBTreeInt.root);
				BtreeInt.deleteWithKey(keyinput);

				_mkdir("AVLTree");
				delete_dir_content("./AVLTree/");
				_mkdir("RBTree");
				delete_dir_content("./RBTree/");
				avlTreeInt.storeTree(avlTreeInt.root);
				RBTreeInt.storeTree(RBTreeInt.root);
			}
		}
		if (idchoice == '2' || idchoice == '3' || idchoice == '4')
		{
			string keyinput, keyinput1;
			if (opchoice == '1')
			{
				cout << "----------------------------------\nSimple Database Management System\n----------------------------------\n\n";
				cout << "Enter Key to display record : ";
				cin >> keyinput;
				system("CLS");
				BtreeString.PointSearch(keyinput1);
			}
			else if (opchoice == '2')
			{
				cout << "----------------------------------\nSimple Database Management System\n----------------------------------\n\n";
				cout << "Enter Minimum Value : ";
				cin >> keyinput;
				cout << "Enter Maximum Value : ";
				cin >> keyinput1;
				system("CLS");
				BtreeString.rangeSearchh(keyinput, keyinput1);
			}
			else if (opchoice == '4')
			{
				cout << "----------------------------------\nSimple Database Management System\n----------------------------------\n\n";
				cout << "Enter Minimum Value : ";
				//cin.getline((keyinput,100);
				system("CLS");
				avlTreeString.deleteRecords(keyinput, avlTreeString.root);
				RBTreeString.deleteRecords(keyinput, RBTreeString.root);
				BtreeString.deleteWithKey(keyinput);

				_mkdir("AVLTree");
				delete_dir_content("./AVLTree/");
				_mkdir("RBTree");
				delete_dir_content("./RBTree/");

				avlTreeString.storeTree(avlTreeString.root);
				RBTreeString.storeTree(RBTreeString.root);
			}
		}
		if (idchoice == '6')
		{
			float keyinput, keyinput1;
			if (opchoice == '1')
			{
				cout << "----------------------------------\nSimple Database Management System\n----------------------------------\n\n";
				cout << "Enter Key to display record : ";
				cin >> keyinput;
				system("CLS");
				BtreeFloat.PointSearch(keyinput);
			}
			else if (opchoice == '2')
			{
				cout << "----------------------------------\nSimple Database Management System\n----------------------------------\n\n";
				cout << "Enter Minimum Value : ";
				cin >> keyinput;
				cout << "Enter Maximum Value : ";
				cin >> keyinput1;
				system("CLS");
				BtreeFloat.rangeSearchh(keyinput, keyinput1);
			}
			else if (opchoice == '4')
			{
				cout << "----------------------------------\nSimple Database Management System\n----------------------------------\n\n";
				cout << "Enter Minimum Value : ";
				cin >> keyinput;
				system("CLS");
				avlTreeFloat.deleteRecords(keyinput, avlTreeFloat.root);
				RBTreeFloat.deleteRecords(keyinput, RBTreeFloat.root);
				BtreeFloat.deleteWithKey(keyinput);

				_mkdir("AVLTree");
				delete_dir_content("./AVLTree/");
				_mkdir("RBTree");
				delete_dir_content("./RBTree/");


				avlTreeFloat.storeTree(avlTreeFloat.root);
				RBTreeFloat.storeTree(RBTreeFloat.root);

			}
		}
	}
	if (treechoice == '3')
	{
		if (idchoice == '0' || idchoice == '1' || idchoice == '5')
		{
			int keyinput, keyinput1;
			if (opchoice == '1')
			{
				cout << "----------------------------------\nSimple Database Management System\n----------------------------------\n\n";
				cout << "Enter Key to display record : ";
				cin >> keyinput;
				system("CLS");
				RBTreeInt.displayRecords(keyinput, RBTreeInt.root);
			}
			else if (opchoice == '2')
			{
				cout << "----------------------------------\nSimple Database Management System\n----------------------------------\n\n";
				cout << "Enter Minimum Value : ";
				cin >> keyinput;
				cout << "Enter Maximum Value : ";
				cin >> keyinput1;
				system("CLS");
				RBTreeInt.rangeSearch(keyinput, keyinput1, RBTreeInt.root);
			}
			else if (opchoice == '4')
			{
				cout << "----------------------------------\nSimple Database Management System\n----------------------------------\n\n";
				cout << "Enter Minimum Value : ";
				cin >> keyinput;
				system("CLS");
				//RBTreeInt.deleteByVal(keyinput);
				RBTreeInt.deleteRecords(keyinput, RBTreeInt.root);
				avlTreeInt.deleteRecords(keyinput, avlTreeInt.root);
				BtreeInt.deleteWithKey(keyinput);
	
				_mkdir("AVLTree");
				delete_dir_content("./AVLTree/");
				_mkdir("RBTree");
				delete_dir_content("./RBTree/");

				avlTreeInt.storeTree(avlTreeInt.root);
				RBTreeInt.storeTree(RBTreeInt.root);
			}
			else if (opchoice == '5') {
				RBTreeInt.printRB("", RBTreeInt.root, false);
			}
		}
		if (idchoice == '2' || idchoice == '3' || idchoice == '4')
		{
			string keyinput, keyinput1;
			if (opchoice == '1')
			{
				cout << "----------------------------------\nSimple Database Management System\n----------------------------------\n\n";
				cout << "Enter Key to display record : ";
				cin >> keyinput;
				system("CLS");
				RBTreeString.displayRecords(keyinput, RBTreeString.root);
			}
			else if (opchoice == '2')
			{
				cout << "----------------------------------\nSimple Database Management System\n----------------------------------\n\n";
				cout << "Enter Minimum Value : ";
				cin >> keyinput;
				cout << "Enter Maximum Value : ";
				cin >> keyinput1;
				system("CLS");
				RBTreeString.rangeSearch(keyinput, keyinput1, RBTreeString.root);
			}
			else if (opchoice == '4')
			{
				cout << "----------------------------------\nSimple Database Management System\n----------------------------------\n\n";
				cout << "Enter Minimum Value : ";
				cin >> keyinput;
				system("CLS");
				//RBTreeString.deleteByVal(keyinput);
				RBTreeString.deleteRecords(keyinput, RBTreeString.root);
				avlTreeString.deleteRecords(keyinput, avlTreeString.root);
				BtreeString.deleteWithKey(keyinput);

				_mkdir("AVLTree");
				delete_dir_content("./AVLTree/");
				_mkdir("RBTree");
				delete_dir_content("./RBTree/");

				avlTreeString.storeTree(avlTreeString.root);
				RBTreeString.storeTree(RBTreeString.root);
			}
			else if (opchoice == '5') {
				RBTreeString.printRB("", RBTreeString.root, false);
			}
		}
		if (idchoice == '6')
		{
			float keyinput, keyinput1;
			if (opchoice == '1')
			{
				cout << "----------------------------------\nSimple Database Management System\n----------------------------------\n\n";
				cout << "Enter Key to display record : ";
				cin >> keyinput;
				system("CLS");
				RBTreeFloat.displayRecords(keyinput, RBTreeFloat.root);
			}
			else if (opchoice == '2')
			{
				cout << "----------------------------------\nSimple Database Management System\n----------------------------------\n\n";
				cout << "Enter Minimum Value : ";
				cin >> keyinput;
				cout << "Enter Maximum Value : ";
				cin >> keyinput1;
				system("CLS");
				RBTreeFloat.rangeSearch(keyinput, keyinput1, RBTreeFloat.root);
			}
			else if (opchoice == '4')
			{
				cout << "----------------------------------\nSimple Database Management System\n----------------------------------\n\n";
				cout << "Enter Minimum Value : ";
				cin >> keyinput;
				system("CLS");
				//RBTreeFloat.deleteByVal(keyinput);
				RBTreeFloat.deleteRecords(keyinput, RBTreeFloat.root);
				avlTreeFloat.deleteRecords(keyinput, avlTreeFloat.root);
				BtreeFloat.deleteWithKey(keyinput);

				_mkdir("AVLTree");
				delete_dir_content("./AVLTree/");
				_mkdir("RBTree");
				delete_dir_content("./RBTree/");


				avlTreeFloat.storeTree(avlTreeFloat.root);
				RBTreeFloat.storeTree(RBTreeFloat.root);
			}
			else if (opchoice == '5') {
				RBTreeFloat.printRB("", RBTreeFloat.root, false);
			}
		}

	}


}

int main()
{

start:

	mainMenu();
	
	string kk;

	cout << "Press \'Y\' to Continue or \'N\' to terminate:";
	cin >> kk;

	if (kk == "Y"|| kk == "y")
		goto start;


	return 0;
}