#include <iostream>
#include "BTreeNode.h"
#include "BTree.h"

using namespace std;

int main() {

	BTree<int> n(4);

	n.insert(20, n.root);
	n.insert(30, n.root);
	n.insert(40, n.root);
	n.insert(50, n.root);

	n.insert(60, n.root);
	//n.insert(70, n.root);
	//n.insert(80, n.root);
	//n.insert(90, n.root);

	n.traverse(n.root);

	/*n.root->printKeys();
	n.root->childs[0]->printKeys();
	n.root->childs[1]->printKeys();
	n.root->childs[2]->printKeys();*/

	//n.InsertKey(30);
	//n.InsertKey(20);
	//n.InsertKey(10);
	//n.printKeys();

	return 0;
}


//int main()
//{
//
//    // Create B-Tree
//    BTree* tree = new BTree(3);
//    cout << "After inserting 1 and 2" << endl;
//    tree->insert(1);
//    tree->insert(2);
//    tree->display();
//
//    cout << "After inserting 5 and 6" << endl;
//    tree->insert(5);
//    tree->insert(6);
//    tree->display();
//
//    cout << "After inserting 3 and 4" << endl;
//    tree->insert(3);
//    tree->insert(4);
//    tree->display();
//
//    cout << "After inserting 7,8 and 9" << endl;
//
//    tree->insert(7);
//    tree->insert(8);
//    tree->insert(9);
//    tree->display();
//
//    return 0;
//}