#pragma once
enum COLOR { RED, BLACK };

template <class T>

class RBNode {
public:
	T val;
	COLOR color;
	RBNode* left, * right, * parent;
	duplicateList<int> line;
	duplicateList<string> location;

	RBNode(T val) : val(val) {
		parent = left = right = NULL;
		color = RED;
	}

	RBNode* parentNeighbour() {
		if (parent == NULL or parent->parent == NULL)
			return NULL;

		if (parent->onLeft())
			return parent->parent->right;
		else
			return parent->parent->left;
	}

	bool onLeft() { return this == parent->left; }

	RBNode* neighbour() {
		if (parent == NULL)
			return NULL;

		if (onLeft())
			return parent->right;

		return parent->left;
	}

	void replaceDown(RBNode* nParent) {
		if (parent != NULL) {
			if (onLeft()) {
				parent->left = nParent;
			}
			else {
				parent->right = nParent;
			}
		}
		nParent->parent = parent;
		parent = nParent;
	}

	bool redChild() {
		return (left != NULL and left->color == RED) or
			(right != NULL and right->color == RED);
	}
};

template <class T>

class RBTree {
public:
	RBNode<T>* root;

	void leftRotate(RBNode<T>* x) {
		RBNode<T>* nParent = x->right;

		if (x == root)
			root = nParent;

		x->replaceDown(nParent);

		x->right = nParent->left;
		if (nParent->left != NULL)
			nParent->left->parent = x;

		nParent->left = x;
	}

	void rightRotate(RBNode<T>* x) {
		RBNode<T>* nParent = x->left;

		if (x == root)
			root = nParent;

		x->replaceDown(nParent);

		x->left = nParent->right;

		if (nParent->right != NULL)
			nParent->right->parent = x;

		nParent->right = x;
	}

	void swapColors(RBNode<T>* x1, RBNode<T>* x2) {
		COLOR temp;
		temp = x1->color;
		x1->color = x2->color;
		x2->color = temp;
	}

	void swapValues(RBNode<T>* u, RBNode<T>* v) {
		T temp;
		temp = u->val;
		u->val = v->val;
		v->val = temp;
	}

	void RRViolation(RBNode<T>* x) {
		if (x == root) {
			x->color = BLACK;
			return;
		}

		RBNode<T>* parent = x->parent, * grandparent = parent->parent,
			* parentNeighbour = x->parentNeighbour();

		if (parent->color != BLACK) {
			if (parentNeighbour != NULL && parentNeighbour->color == RED) {
				parent->color = BLACK;
				parentNeighbour->color = BLACK;
				grandparent->color = RED;
				RRViolation(grandparent);
			}
			else {
				if (parent->onLeft()) {
					if (x->onLeft()) {
						swapColors(parent, grandparent);
					}
					else {
						leftRotate(parent);
						swapColors(x, grandparent);
					}
					rightRotate(grandparent);
				}
				else {
					if (x->onLeft()) {
						rightRotate(parent);
						swapColors(x, grandparent);
					}
					else {
						swapColors(parent, grandparent);
					}

					leftRotate(grandparent);
				}
			}
		}
	}

	RBNode<T>* next(RBNode<T>* x) {
		RBNode<T>* temp = x;

		while (temp->left != NULL)
			temp = temp->left;

		return temp;
	}

	RBNode<T>* delNodeRep(RBNode<T>* x) {
		if (x->left != NULL and x->right != NULL)
			return next(x->right);

		if (x->left == NULL and x->right == NULL)
			return NULL;

		if (x->left != NULL)
			return x->left;
		else
			return x->right;
	}

	void delNode(RBNode<T>* v) {
		RBNode<T>* u = delNodeRep(v);

		bool uvBlack = ((u == NULL or u->color == BLACK) and (v->color == BLACK));
		RBNode<T>* parent = v->parent;

		if (u == NULL) {
			if (v == root) {
				root = NULL;
			}
			else {
				if (uvBlack) {
					BBViolation(v);
				}
				else {
					if (v->neighbour() != NULL)
						v->neighbour()->color = RED;
				}

				if (v->onLeft()) {
					parent->left = NULL;
				}
				else {
					parent->right = NULL;
				}
			}
			delete v;
			return;
		}

		if (v->left == NULL or v->right == NULL) {
			if (v == root) {
				v->val = u->val;
				v->left = v->right = NULL;
				delete u;
			}
			else {
				if (v->onLeft()) {
					parent->left = u;
				}
				else {
					parent->right = u;
				}
				delete v;
				u->parent = parent;
				if (uvBlack) {
					BBViolation(u);
				}
				else {
					u->color = BLACK;
				}
			}
			return;
		}

		swapValues(u, v);
		delNode(u);
	}

	void BBViolation(RBNode<T>* x) {
		if (x == root)
			return;

		RBNode<T>* neighbour = x->neighbour(), * parent = x->parent;
		if (neighbour == NULL) {
			BBViolation(parent);
		}
		else {
			if (neighbour->color == RED) {
				parent->color = RED;
				neighbour->color = BLACK;
				if (neighbour->onLeft()) {
					rightRotate(parent);
				}
				else {
					leftRotate(parent);
				}
				BBViolation(x);
			}
			else {
				if (neighbour->redChild()) {
					if (neighbour->left != NULL and neighbour->left->color == RED) {
						if (neighbour->onLeft()) {
							neighbour->left->color = neighbour->color;
							neighbour->color = parent->color;
							rightRotate(parent);
						}
						else {
							neighbour->left->color = parent->color;
							rightRotate(neighbour);
							leftRotate(parent);
						}
					}
					else {
						if (neighbour->onLeft()) {
							neighbour->right->color = parent->color;
							leftRotate(neighbour);
							rightRotate(parent);
						}
						else {
							neighbour->right->color = neighbour->color;
							neighbour->color = parent->color;
							leftRotate(parent);
						}
					}
					parent->color = BLACK;
				}
				else {
					neighbour->color = RED;
					if (parent->color == BLACK)
						BBViolation(parent);
					else
						parent->color = BLACK;
				}
			}
		}
	}

	void inorder(RBNode<T>* x) {
		if (x == NULL)
			return;
		inorder(x->left);
		cout << x->val << " ";
		inorder(x->right);
	}

	RBTree() { root = NULL; }

	RBNode<T>* getRoot() { return root; }

	RBNode<T>* search(T n) {
		RBNode<T>* temp = root;
		while (temp != NULL) {
			if (n < temp->val) {
				if (temp->left == NULL)
					break;
				else
					temp = temp->left;
			}
			else if (n == temp->val) {
				break;
			}
			else {
				if (temp->right == NULL)
					break;
				else
					temp = temp->right;
			}
		}

		return temp;
	}

	void insert(T n, int l, string loc) {
		fstream filee;
		RBNode<T>* newRBNode = new RBNode<T>(n);
		newRBNode->line.insert(l);
		newRBNode->location.insert(loc);
		if (root == NULL) {
			newRBNode->color = BLACK;
			filee.open("RBTree.txt", ios::out | ios::app);
			filee << n << "," << loc << "," << l << "," << endl;
			filee.close();
			root = newRBNode;
		}
		else {
			RBNode<T>* temp = search(n);

			if (temp->val == n) {
				temp->line.insert(l);
				temp->location.insert(loc);
				filee.open("RBTree.txt", ios::out | ios::app);
				filee << n << "," << loc << "," << l << "," << endl;
				filee.close();
				return;
			}

			newRBNode->parent = temp;

			if (n < temp->val)
			{
				temp->left = newRBNode;
				filee.open("RBTree.txt", ios::out | ios::app);
				filee << n << "," << loc << "," << l << "," << endl;
				filee.close();
			}
			else if (n > temp->val)
			{
				temp->right = newRBNode;
				filee.open("RBTree.txt", ios::out | ios::app);
				filee << n << "," << loc << "," << l << "," << endl;
				filee.close();
			}

			RRViolation(newRBNode);
		}
	}

	void deleteRecords(T key, RBNode<T>* ptr) {
		if (ptr != NULL)
		{
			if (ptr->val > key)
			{
				deleteRecords(key, ptr->left);
			}
			else if (ptr->val < key)
			{
				deleteRecords(key, ptr->right);
			}
			else {
				string temp1, lineInp, wordInp;
				RBNode<T>* temp = ptr;
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
				//ptr = deletion(ptr->val, ptr);
			}

		}
	}

	void deleteByVal(T n) {
		if (root == NULL)
			return;

		RBNode<T>* v = search(n), * u;

		if (v->val != n) {
			cout << "No RBNode found to delete with value:" << n << endl;
			return;
		}

		delNode(v);
		string temp1, lineInp, wordInp;
		RBNode<T>* temp = root;
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
	}

	void printInOrder() {
		cout << "Inorder: " << endl;
		if (root == NULL)
			cout << "Tree is empty" << endl;
		else
			inorder(root);
		cout << endl;
	}

	void displayLL(RBNode<T>* ptr)
	{
		if (ptr != nullptr)
		{
			displayLL(ptr->left);
			ptr->line.print();
			displayLL(ptr->right);
		}
	}

	void displayRecords(T key, RBNode<T>* ptr) {
		if (ptr != NULL)
		{
			if (ptr->val > key)
			{
				displayRecords(key, ptr->left);
			}
			else if (ptr->val < key)
			{
				displayRecords(key, ptr->right);
			}
			else {
				string temp1, lineInp, wordInp;
				RBNode<T>* temp = ptr;
				listNode<int>* linet = temp->line.head;
				listNode<string>* loct = temp->location.head;

				while (linet != NULL)
				{
					fstream file(loct->data, ios::in);

					for (int i = 0; i < linet->data; i++)
					{
						getline(file, lineInp);
					}
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

	void rangeSearch(T low, T high, RBNode<T>* ptr) {
		if (ptr == NULL)
		{
			return;
		}
		if (ptr->val > low)
		{
			rangeSearch(low, high, ptr->left);
		}
		if (ptr->val >= low && ptr->val <= high)
		{
			displayRecords(ptr->val, ptr);
		}
		if (ptr->val < high)
		{
			rangeSearch(low, high, ptr->right);
		}
	}

	void storeTree(RBNode<T>* ptr) {
		if (ptr != NULL)
		{
			storeTree(ptr->left);
			string fname = "RBTree/";

			if (to_string(ptr->val) != "-1") {


				fname += to_string(ptr->val);
				fname += ".txt";
				fstream file(fname, ios::out);
				listNode<int>* temp = ptr->line.head;
				listNode<string>* temp2 = ptr->location.head;
				while (temp != NULL)
				{
					file << temp->data << "," << temp2->data << "\n";
					temp2 = temp2->next;
					temp = temp->next;
				}

			}
			storeTree(ptr->right);
		}
	}


	void printRB(string prefix, RBNode<T>* node, bool isLeft)
	{
		if (node != NULL)
		{
			cout << prefix;
			if (isLeft)
			{
				cout << "|---->";
			}
			else {
				cout << "L---->";
			}
			// print the value of the node
			cout << node->val << endl;
			// enter the next tree level - left and right branch
			if (isLeft)
			{
				printRB(prefix + "|   ", node->right, true);
				printRB(prefix + "|   ", node->left, false);
			}
			else {
				printRB(prefix + "    ", node->right, true);
				printRB(prefix + "    ", node->left, false);
			}

		}
	}

};
