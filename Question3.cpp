#include<iostream>
using namespace std;
class node
{
public:
	int data;
	node* leftchild;
	node* rightchild;
	int height;
	node()
	{
		data = 0;
		leftchild = NULL;
		rightchild = NULL;
		height = 0;
	}
};
class AVL_Trees
{
	const int s = 5;
	int* arr;
	int count;
public:
	node* root;
	AVL_Trees()
	{
		root = NULL;
		count = 0;
	}
	void Display(node* r, int space)
	{
		if (r == NULL)
		{
			return;
		}
		space = space + s;
		Display(r->rightchild, space);
		cout << endl;
		for (int i = s; i < space; i++)
		{
			cout << " ";
		}
		cout << r->data << endl;
		Display(r->leftchild, space);
	}
	int count_nodes(node* r)
	{
		if (r == NULL)
		{
			return 0;
		}
		int l_tree = count_nodes(r->leftchild);
		int r_tree = count_nodes(r->rightchild);
		return 1 + l_tree + r_tree;
	}
	void Filling_arr(node* r)
	{
		if (r == NULL)
		{
			return;
		}
		Filling_arr(r->leftchild);
		arr[count] = r->data;
		count++;
		Filling_arr(r->rightchild);
	}
	node* get_root()
	{
		return root;
	}
	void make_array(int size)
	{
		arr = new int[size];
	}
	int height(node* N)
	{
		if (N == NULL)
		{
			return 0;
		}
		return N->height;
	}
	int max(int a, int b)
	{
		if (a > b)
		{
			return a;
		}
		else
		{
			return b;
		}
	}
	node* newNode(int d)
	{
		node* ptr = new node;
		ptr->data = d;
		ptr->leftchild = NULL;
		ptr->rightchild = NULL;
		ptr->height = 1;
		return ptr;
	}
	node* rightRotate(node* y)
	{
		node* x = y->leftchild;
		node* T2 = x->rightchild;
		x->rightchild = y;
		y->leftchild = T2;
		y->height = max(height(y->leftchild), height(y->rightchild)) + 1;
		x->height = max(height(x->leftchild), height(x->rightchild)) + 1;
		return x;
	}
	node* leftRotate(node* x)
	{
		node* y = x->rightchild;
		node* T2 = y->leftchild;
		y->leftchild = x;
		x->rightchild = T2;
		x->height = max(height(x->leftchild), height(x->rightchild)) + 1;
		y->height = max(height(y->leftchild), height(y->rightchild)) + 1;
		return y;
	}
	int getBalance(node* N)
	{
		if (N == NULL)
		{
			return 0;
		}
		return height(N->leftchild) - height(N->rightchild);
	}
	node* insert_AVL(node* r, int d)
	{
		if (r == NULL)
		{
			return newNode(d);
		}

		if (d < r->data)
		{
			r->leftchild = insert_AVL(r->leftchild, d);
		}
		else if (d > r->data)
		{
			r->rightchild = insert_AVL(r->rightchild, d);
		}
		else
		{
			return r;
		}
		r->height = 1 + max(height(r->leftchild), height(r->rightchild));
		int balance = getBalance(r);
		if (balance > 1 && d < r->leftchild->data)
		{
			return rightRotate(r);
		}

		if (balance < -1 && d > r->rightchild->data)
		{
			return leftRotate(r);
		}
		if (balance > 1 && d > r->leftchild->data)
		{
			r->leftchild = leftRotate(r->leftchild);
			return rightRotate(r);
		}
		if (balance < -1 && d < r->rightchild->data)
		{
			r->rightchild = rightRotate(r->rightchild);
			return leftRotate(r);
		}
		return r;
	}
	void insert_BST(int val)
	{
		node* ptr = new node;
		ptr->data = val;
		if (root == NULL)
		{
			root = ptr;
			
			return;
		}
		else
		{
			node* temp = root;
			while (temp != NULL)
			{
				if (temp->data == ptr->data)
				{
					cout << " This Data already Exists! " << endl;
					return;
				}
				else if (ptr->data < temp->data && temp->leftchild == NULL)
				{
					temp->leftchild = ptr;
					
					return;
				}
				else if (ptr->data < temp->data)
				{
					temp = temp->leftchild;
				}
				else if (ptr->data > temp->data && temp->rightchild == NULL)
				{
					temp->rightchild = ptr;
					
					return;
				}
				else if (ptr->data > temp->data)
				{
					temp = temp->rightchild;
				}
			}
		}
	}
	void convert()
	{
		int size = count_nodes(get_root());
		root = NULL;
		for (int i = 0; i < size; i++)
		{
			root = insert_AVL(get_root(), arr[i]);
		}
	}
	
};
int main()
{
	const int spaces = 5;
	AVL_Trees t1;
	int a = 0, val;
	cout << "***********Insertion***********" << endl << endl;
	while (a != -222)
	{
		cout << "Insert the Data in your Bst Tree // Enter -222 to exit Insertion: ";;
		cin >> val;
		a = val;
		if (val != -222)
		{
			t1.insert_BST(val);
		}
	    
		
		
	}
	
	t1.Display(t1.get_root(), spaces);
	int size = t1.count_nodes(t1.get_root());
	t1.make_array(size);
	t1.Filling_arr(t1.get_root());
	t1.convert();
	cout <<" Your AVL Tree is:"<<endl;
	t1.Display(t1.get_root(), spaces);

	system("pause");
	return 0;

}