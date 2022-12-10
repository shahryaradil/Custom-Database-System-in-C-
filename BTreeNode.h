#include<iostream>
#include<fstream>
using namespace std;

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
		// Copy the given minimum degree and leaf property
		order = _t;
		leaf = _leaf;

		// Allocate memory for maximum number of possible keys
		// and child pointers
		keys = new T[order - 1];
		fileName = new string[order - 1];
		lineNum = new int[order - 1];
		C = new BTreeNode * [order];

		// Initialize the number of keys as 0
		n = 0;
	} // Constructor//

	// A function to traverse all nodes in a subtree rooted with this node
	// Function to traverse all nodes in a subtree rooted with this node//
	void traverse() {
		// There are n keys and n+1 children, traverse through n keys
		// and first n children
		int i;
		for (i = 0; i < n; i++)
		{
			// If this is not leaf, then before printing key[i],
			// traverse the subtree rooted with child C[i].
			if (leaf == false)
				C[i]->traverse();
			cout << " " << keys[i] << "    fileLocation: " << fileName[i] << "   line number: " << lineNum[i] << endl;
		}

		// Print the subtree rooted with last child
		if (leaf == false)
			C[i]->traverse();
	}



	void Display(T d) {
		// There are n keys and n+1 children, traverse through n keys
		// and first n children
		fstream file;
		string line;
		int i;
		for (i = 0; i < n; i++)
		{
			// If this is not leaf, then before printing key[i],
			// traverse the subtree rooted with child C[i].
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

		// Print the subtree rooted with last child
		if (leaf == false)
			C[i]->Display(d);
	}


	// A function to search a key in subtree rooted with this node.
	// Function to search key k in subtree rooted with this node//
	BTreeNode* search(T k) {
		// Find the first key greater than or equal to k
		int i = 0;

		while (i < n && k > keys[i])
			i++;

		// If the found key is equal to k, return this node
		if (keys[i] == k) {
			//cout << keys[i];
			return this;
		}

		// If key is not found here and this is a leaf node
		if (leaf == true)
			return NULL;

		// Go to the appropriate child
		return C[i]->search(k);
	} // returns NULL if k is not present.

	// A function that returns the index of the first key that is greater
	// or equal to k
	// A utility function that returns the index of the first key that is
	// greater than or equal to k//
	int findKey(T k) {
		int idx = 0;
		while (idx < n && keys[idx] < k)
			++idx;
		return idx;
	}

	// A utility function to insert a new key in the subtree rooted with
	// this node. The assumption is, the node must be non-full when this
	// function is called
	// A utility function to insert a new key in this node
	// The assumption is, the node must be non-full when this
	// function is called//
	void insertNonFull(T k, string file_name, int line_number) {
		// Initialize index as index of rightmost element
		int i = n - 1;

		// If this is a leaf node
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

			// Insert the new key at found location
			keys[i + 1] = k;
			fileName[i + 1] = file_name;
			lineNum[i + 1] = line_number;

			n = n + 1;
		}
		else // If this node is not leaf
		{
			// Find the child which is going to have the new key
			while (i >= 0 && keys[i] > k)
				i--;

			// See if the found child is full
			if (C[i + 1]->n == order - 1)
			{
				// If the child is full, then split it
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

	// A utility function to split the child y of this node. i is index
	// of y in child array C[]. The Child y must be full when this
	// function is called
	// A utility function to split the child y of this node
	// Note that y must be full when this function is called//
	void splitChild(int i, BTreeNode* y) {
		// Create a new node which is going to store (order-1) keys
		// of y
		BTreeNode* z = new BTreeNode(y->order, y->leaf);
		z->n = (order / 2) - 1;

		// Copy the last (order-1) keys of y to z
		for (int j = 0; j < (order / 2) - 1; j++) {
			z->keys[j] = y->keys[j + (order / 2)];
			z->fileName[j] = y->fileName[j + (order / 2)];
			z->lineNum[j] = y->lineNum[j + (order / 2)];

		}

		// Copy the last order children of y to z
		if (y->leaf == false)
		{
			for (int j = 0; j < (order / 2); j++)
				z->C[j] = y->C[j + (order / 2)];
		}

		// Reduce the number of keys in y
		y->n = (order / 2) - 1;

		// Since this node is going to have a new child,
		// create space of new child
		for (int j = n; j >= i + 1; j--)
			C[j + 1] = C[j];

		// Link the new child to this node
		C[i + 1] = z;

		// A key of y will move to this node. Find location of
		// new key and move all greater keys one space ahead
		for (int j = n - 1; j >= i; j--) {
			keys[j + 1] = keys[j];
			fileName[j + 1] = fileName[j];
			lineNum[j + 1] = lineNum[j];

		}

		// Copy the middle key of y to this node
		keys[i] = y->keys[(order / 2) - 1];
		fileName[i] = y->fileName[(order / 2) - 1];
		lineNum[i] = y->lineNum[(order / 2) - 1];

		// Increment count of keys in this node
		n = n + 1;
	}

	void removeFromFile(T d) {
		// There are n keys and n+1 children, traverse through n keys
		// and first n children
		fstream file, file2;
		string line;
		int i;
		for (i = 0; i < n; i++)
		{
			// If this is not leaf, then before printing key[i],
			// traverse the subtree rooted with child C[i].
			if (leaf == false)
				C[i]->removeFromFile(d);
			if (d != keys[i]) {

				//cout << " " << keys[i] << "    fileLocation: " << fileName[i] << "   line number: " << lineNum[i] << endl;
				file.open(fileName[i], ios::in);
				file2.open("temp.csv", ios::out );
				for (int j = 1; getline(file, line); j++)
				{
						file2 << line ;
						file2 << "\n";
						line.clear();
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
			C[i]->removeFromFile(d);
	}

	// A wrapper function to Removee the key k in subtree rooted with
	// this node.//
	// A function to Removee the key k from the sub-tree rooted with this node//
	void Removee(T k) {
		int idx = findKey(k);

		// The key to be removed is present in this node
		if (idx < n && keys[idx] == k)
		{

			// If the node is a leaf node - removeFromLeaf is called
			// Otherwise, removeFromNonLeaf function is called
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
				return ;
			}

			// The key to be removed is present in the sub-tree rooted with this node
			// The flag indicates whether the key is present in the sub-tree rooted
			// with the last child of this node
			bool flag = ((idx == n) ? true : false);

			// If the child where the key is supposed to exist has less that order keys,
			// we fill that child
			if (C[idx]->n < (order / 2))
				fill(idx);

			// If the last child has been merged, it must have merged with the previous
			// child and so we recurse on the (idx-1)th child. Else, we recurse on the
			// (idx)th child which now has atleast order keys
			if (flag && idx > n)
				C[idx - 1]->Removee(k);
			else
				C[idx]->Removee(k);
		}
		return ;
	}

	// A function to Removee the key present in idx-th position in
	// this node which is a leaf//
	// A function to Removee the idx-th key from this node - which is a leaf node//
	void removeFromLeaf(int idx) {

		// Move all the keys after the idx-th pos one place backward
		for (int i = idx + 1; i < n; ++i) {
			keys[i - 1] = keys[i];
			fileName[i - 1] = fileName[i];
			lineNum[i - 1] = lineNum[i];

		}

		// Reduce the count of keys
		n--;

		return;
	}

	// A function to Removee the key present in idx-th position in
	// this node which is a non-leaf node
	// A function to Removee the idx-th key from this node - which is a non-leaf node//
	void removeFromNonLeaf(int idx) {

		T k = keys[idx];

		// If the child that precedes k (C[idx]) has atleast order keys,
		// find the predecessor 'pred' of k in the subtree rooted at
		// C[idx]. Replace k by pred. Recursively delete pred
		// in C[idx]
		if (C[idx]->n >= (order / 2))
		{
			T pred = getPred(idx);
			keys[idx] = pred;
			C[idx]->Removee(pred);
		}

		// If the child C[idx] has less that order keys, examine C[idx+1].
		// If C[idx+1] has atleast order keys, find the successor 'succ' of k in
		// the subtree rooted at C[idx+1]
		// Replace k by succ
		// Recursively delete succ in C[idx+1]
		else if (C[idx + 1]->n >= (order / 2))
		{
			T succ = getSucc(idx);
			keys[idx] = succ;
			C[idx + 1]->Removee(succ);
		}

		// If both C[idx] and C[idx+1] has less that order keys,merge k and all of C[idx+1]
		// into C[idx]
		// Now C[idx] contains 2t-1 keys
		// Free C[idx+1] and recursively delete k from C[idx]
		else
		{
			merge(idx);
			C[idx]->Removee(k);
		}
		return;
	}

	// A function to get the predecessor of the key- where the key
	// is present in the idx-th position in the node
	// A function to get predecessor of keys[idx]
	T getPred(int idx) {
		// Keep moving to the right most node until we reach a leaf
		BTreeNode* cur = C[idx];
		while (!cur->leaf)
			cur = cur->C[cur->n];

		// Return the last key of the leaf
		return cur->keys[cur->n - 1];
	}

	// A function to get the successor of the key- where the key
	// is present in the idx-th position in the node
	T getSucc(int idx) {
		// Keep moving the left most node starting from C[idx+1] until we reach a leaf
		BTreeNode* cur = C[idx + 1];
		while (!cur->leaf)
			cur = cur->C[0];

		// Return the first key of the leaf
		return cur->keys[0];
	}

	// A function to fill up the child node present in the idx-th
	// position in the C[] array if that child has less than order-1 keys//
	// A function to fill child C[idx] which has less than order-1 keys//

	void fill(int idx) {
		// If the previous child(C[idx-1]) has more than order-1 keys, borrow a key
	// from that child
		if (idx != 0 && C[idx - 1]->n >= (order / 2))
			borrowFromPrev(idx);

		// If the next child(C[idx+1]) has more than order-1 keys, borrow a key
		// from that child
		else if (idx != n && C[idx + 1]->n >= (order / 2))
			borrowFromNext(idx);

		// Merge C[idx] with its sibling
		// If C[idx] is the last child, merge it with its previous sibling
		// Otherwise merge it with its next sibling
		else
		{
			if (idx != n)
				merge(idx);
			else
				merge(idx - 1);
		}
		return;
	}

	// A function to borrow a key from the C[idx-1]-th node and place
	// it in C[idx]th node
	// A function to borrow a key from C[idx-1] and insert it
	// into C[idx]//
	void borrowFromPrev(int idx) {
		BTreeNode* child = C[idx];
		BTreeNode* sibling = C[idx - 1];

		// The last key from C[idx-1] goes up to the parent and key[idx-1]
		// from parent is inserted as the first key in C[idx]. Thus, the loses
		// sibling one key and child gains one key

		// Moving all key in C[idx] one step ahead
		for (int i = child->n - 1; i >= 0; --i) {
			child->keys[i + 1] = child->keys[i];
			child->fileName[i + 1] = child->fileName[i];
			child->lineNum[i + 1] = child->lineNum[i];

		}

		// If C[idx] is not a leaf, move all its child pointers one step ahead
		if (!child->leaf)
		{
			for (int i = child->n; i >= 0; --i)
				child->C[i + 1] = child->C[i];
		}

		// Setting child's first key equal to keys[idx-1] from the current node
		child->keys[0] = keys[idx - 1];
		child->fileName[0] = fileName[idx - 1];
		child->lineNum[0] = lineNum[idx - 1];


		// Moving sibling's last child as C[idx]'s first child
		if (!child->leaf)
			child->C[0] = sibling->C[sibling->n];

		// Moving the key from the sibling to the parent
		// This reduces the number of keys in the sibling
		keys[idx - 1] = sibling->keys[sibling->n - 1];
		fileName[idx - 1] = sibling->fileName[sibling->n - 1];
		lineNum[idx - 1] = sibling->lineNum[sibling->n - 1];


		child->n += 1;
		sibling->n -= 1;

		return;
	}

	// A function to borrow a key from the C[idx+1]-th node and place it
	// in C[idx]th node
	// A function to borrow a key from the C[idx+1] and place
	// it in C[idx]//
	void borrowFromNext(int idx) {
		BTreeNode* child = C[idx];
		BTreeNode* sibling = C[idx + 1];

		// keys[idx] is inserted as the last key in C[idx]
		child->keys[(child->n)] = keys[idx];
		child->fileName[(child->n)] = fileName[idx];
		child->lineNum[(child->n)] = lineNum[idx];

		// Sibling's first child is inserted as the last child
		// into C[idx]
		if (!(child->leaf))
			child->C[(child->n) + 1] = sibling->C[0];

		//The first key from sibling is inserted into keys[idx]
		keys[idx] = sibling->keys[0];
		fileName[idx] = sibling->fileName[0];
		lineNum[idx] = sibling->lineNum[0];

		// Moving all keys in sibling one step behind
		for (int i = 1; i < sibling->n; ++i) {
			sibling->keys[i - 1] = sibling->keys[i];
			sibling->fileName[i - 1] = sibling->fileName[i];
			sibling->lineNum[i - 1] = sibling->lineNum[i];

		}

		// Moving the child pointers one step behind
		if (!sibling->leaf)
		{
			for (int i = 1; i <= sibling->n; ++i)
				sibling->C[i - 1] = sibling->C[i];
		}

		// Increasing and decreasing the key count of C[idx] and C[idx+1]
		// respectively
		child->n += 1;
		sibling->n -= 1;

		return;
	}

	// A function to merge idx-th child of the node with (idx+1)th child of
	// the node
	// A function to merge C[idx] with C[idx+1]
	// C[idx+1] is freed after merging//
	void merge(int idx) {
		BTreeNode* child = C[idx];
		BTreeNode* sibling = C[idx + 1];

		// Pulling a key from the current node and inserting it into (order-1)th
		// position of C[idx]
		child->keys[(order / 2) - 1] = keys[idx];
		child->fileName[(order / 2) - 1] = fileName[idx];
		child->lineNum[(order / 2) - 1] = lineNum[idx];

		// Copying the keys from C[idx+1] to C[idx] at the end
		for (int i = 0; i < sibling->n; ++i) {
			child->keys[i + (order / 2)] = sibling->keys[i];
			child->fileName[i + (order / 2)] = sibling->fileName[i];
			child->lineNum[i + (order / 2)] = sibling->lineNum[i];

		}

		// Copying the child pointers from C[idx+1] to C[idx]
		if (!child->leaf)
		{
			for (int i = 0; i <= sibling->n; ++i)
				child->C[i + (order / 2)] = sibling->C[i];
		}

		// Moving all keys after idx in the current node one step before -
		// to fill the gap created by moving keys[idx] to C[idx]
		for (int i = idx + 1; i < n; ++i) {
			keys[i - 1] = keys[i];
			fileName[i - 1] = fileName[i];
			lineNum[i - 1] = lineNum[i];

		}

		// Moving the child pointers after (idx+1) in the current node one
		// step before
		for (int i = idx + 2; i <= n; ++i)
			C[i - 1] = C[i];

		// Updating the key count of child and the current node
		child->n += sibling->n + 1;
		n--;

		// Freeing the memory occupied by sibling
		delete(sibling);
		return;
	}

	// Make BTree friend of this so that we can access private members of
	// this class in BTree functions
	template <typename X> friend class BTree;
};


