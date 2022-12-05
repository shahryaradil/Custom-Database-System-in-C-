#include <iostream>
#include "BTreeNode.h"
#include "BTree.h"

using namespace std;

int main() {

	BTree<int> n(4);

	n.insert(30, n.root);
	n.insert(20, n.root);
	n.insert(40, n.root);
	n.root->printKeys();

	return 0;
}