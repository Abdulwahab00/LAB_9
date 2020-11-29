#include<iostream>
#define SPACE 10
using namespace std;
#include<cstdio>
#include<sstream>
#include<algorithm>
#define pow2(n) (1 << (n))
class Node
{
public:
	int data;
	Node* left;
	Node* right;
	Node()
	{
		data = 0;
		left = NULL;
		right = NULL;
	}
};
class avlTree
{
public:
	static int alpha;
	Node* root;
	int leftHeight;
	int rightHeight;
	int balanceFactor;
	int maxHeight;
	avlTree()
	{
		root = NULL;
		leftHeight = 0;
		rightHeight = 0;
		balanceFactor = 0;
		maxHeight = 0;
	}
	Node* deleteNode(Node* root, int a)
	{
		if (root == NULL)
		{
			return NULL;
		}
		if (a < root->data)
		{
			root->left = deleteNode(root->left, a);
		}
		else if (a > root->data)
		{
			root->right = deleteNode(root->right, a);
		}
		else
		{
			if (root->left == NULL)
			{
				Node* temp = root;
				alpha = root->data;
				delete root;
				return temp;
			}
			else if (root->right == NULL)
			{
				Node* temp = root;
				alpha = root->data;
				delete root;
				return temp;
			}
			Node* temp = MiniOnRight(root->right);
			root->data = temp->data;
			root->right = deleteNode(root->right, temp->data);
		}
		return root;
	}
	Node* MiniOnRight(Node* root)
	{
		if (root == NULL)
		{
			return NULL;
		}
		while (root->left != NULL)
		{
			root = root->left;
		}
		return root;
	}
	int height(Node* t)
	{
		int h = 0;
		if (t != NULL)
		{
			int l_height = height(t->left);
			int r_height = height(t->right);
			int max_height = max(l_height, r_height);
			h = max_height + 1;
		}
		return h;
	}
	int difference(Node* t)
	{
		int l_height = height(t->left);
		int r_height = height(t->right);
		int b_factor = l_height - r_height;
		return b_factor;
	}
	Node* rr_rotat(Node* parent)
	{
		Node* t;
		t = parent->right;
		parent->right = t->left;
		t->left = parent;

		return t;
	}
	Node* ll_rotat(Node* parent)
	{
		Node* t;
		t = parent->left;
		parent->left = t->right;
		t->right = parent;

		return t;
	}
	Node* lr_rotat(Node* parent)
	{
		Node* t;
		t = parent->left;
		parent->left = rr_rotat(t);

		return ll_rotat(parent);
	}
	Node* rl_rotat(Node* parent)
	{
		Node* t;
		t = parent->right;
		parent->right = ll_rotat(t);

		return rr_rotat(parent);
	}
	Node* balance(Node* t)
	{
		int bal_factor = difference(t);
		if (bal_factor > 1)
		{
			if (difference(t->left) > 0)
				t = ll_rotat(t);
			else
				t = lr_rotat(t);
		}
		else if (bal_factor < -1)
		{
			if (difference(t->right) > 0)
				t = rl_rotat(t);
			else
				t = rr_rotat(t);
		}
		return t;
	}
	void insertNode(int a)
	{
		Node* ptr;
		Node* temp;
		ptr = new Node;
		temp = new Node;
		ptr->data = a;
		if (root == NULL)
		{
			root = new Node;
			root->data = a;
		}
		else
		{
			temp = root;
			while (temp != NULL)
			{
				if (ptr->data == temp->data)
				{
					cout << "Value Already exists:";
					return;
				}
				else if (ptr->data < temp->data && temp->left == NULL)
				{
					temp->left = ptr;
					root = balance(root);
					return;
				}
				else if (ptr->data < temp->data)
				{
					temp = temp->left;
				}
				else if (ptr->data > temp->data && temp->right == NULL)
				{
					temp->right = ptr;
					root = balance(root);
					return;
				}
				else
				{
					temp = temp->right;
				}
			}
		}
	}
	void display(Node* r, int space)
	{
		if (r == NULL)
		{
			return;
		}
		space += SPACE;
		display(r->right, space);
		cout << endl;
		for (int i = SPACE; i < space; i++)
		{
			cout << " ";
		}
		cout << r->data << "\n";
		display(r->left, space);
	}
};
int avlTree::alpha = 0;
int main()
{
	int c, i;
	avlTree avl, avl1;
	int d = 0;
	int val = 0;
	while (1)
	{
		cout << "1) Insert\n2) Merge\n3) Display\n4) Exit" << endl;

		cin >> c;
		switch (c)
		{
		case 1:
		{
			int a = 0;


			cout << "Enter in First AVL Tree" << endl;
			while (val != -222)
			{

				cout << "Enter the Element You want to insert/ Enter -222 To exit: " << endl;
				cin >> val;
				if (val != -222)
				{


					avl.insertNode(val);
				}
			}
			val = 0;
			cout << "Enter in 2nd AVL Tree" << endl;
			while (val != -222)
			{

				cout << "Enter the Element You want to insert/ Enter -222 To exit: " << endl;
				cin >> val;
				if (val != -222)
				{


					avl1.insertNode(val);
					d = d + 1;
				}
			}

			break;
		}
		case 2:
		{
			while (d != 0)
			{
				avl1.deleteNode(avl1.root, avl1.root->data);
				avl.insertNode(avl.alpha);
				d = d - 1;
			}
			break;
		}
		case 3:
		{
			avl.display(avl.root, 5);
			cout << endl;
			break;
		}
		case 4:
		{
			exit(1);
			break;
		}
		default:
			cout << "Wrong Choice" << endl;
		}
	}
	return 0;
}