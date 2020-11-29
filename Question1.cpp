#include<iostream>

using namespace std;

struct Node
{
	int data;
	Node* LeftChild, * RightChild;
};
Node* root;

class AVLTree 
{
public:
	


	AVLTree()
	{
		root = NULL;

	}
	Node* insert(Node* root, int value);
	Node* Delete(Node* root, int value);
	Node* minNode(Node* current);
	int height(Node* node);
	int BFactor(Node* node);
	Node* rightRotation(Node* P);
	Node* leftRotation(Node* P);
	Node* leftrightRotation(Node* P);
	Node* rightleftRotation(Node* P);
	Node* balancing(Node* node);
	void print(Node* root, int space= 0);



};
	Node* AVLTree:: insert(Node* root, int value)
	{

		if (root == NULL)
		{
			root = new Node;
			root->LeftChild = NULL;
			root->RightChild = NULL;
			root->data = value;
			return root;
		}
		
		if (value < root->data)
		{
			root->LeftChild = insert(root->LeftChild, value);
			root = balancing(root);
		}
		else if (value > root->data)
		{
			root->RightChild = insert(root->RightChild, value);
			root = balancing(root);
		}
		return root;
	}
	
	Node* AVLTree:: minNode(Node* current)
	{
		Node* min = current;
		while (min && min->LeftChild != NULL)
		{
			min = min->LeftChild;
		}
		return min;
	}
	Node* AVLTree:: Delete(Node* root, int value)
	{
		
		if (root == NULL)
		{
			cout << "Tree is empty\n";
			return root;
		}
		else if (value < root->data)
		{
			root->LeftChild = Delete(root->LeftChild, value);
		}
		else if (value > root->data)
		{
			root->RightChild = Delete(root->RightChild, value);
		}
		else
		{
			if (root->LeftChild == NULL && root->RightChild == NULL)
			{
				delete root;
				root = NULL;
			}
			else if (root->LeftChild == NULL)
			{
				Node* temp = root;
				root = root->RightChild;
				delete temp;
			}
			else if (root->RightChild == NULL)
			{
				Node* temp = root;
				root = root->LeftChild;
				delete temp;
			}
			else
			{
				Node* temp = minNode(root->RightChild);
				root->data = temp->data;
				root->RightChild = Delete(root->RightChild, temp->data);
			}
		}
		root = balancing(root);
		return root;
	}
	
	void AVLTree:: print(Node* root, int space)
	{

		if (root == NULL)
		{
			return;
		}
		space = space + 4;
		print(root->RightChild, space);
		for (int i = 0; i < space; i++)
		{
			cout << "   ";
		}
		cout << root->data << endl;
		cout << endl;
		print(root->LeftChild, space);


	}

Node* AVLTree:: leftrightRotation(Node* parent)
{
	Node* temp = parent->LeftChild;
	parent->LeftChild = rightRotation(temp);
	return leftRotation(parent);
}

//RL
Node* AVLTree:: rightleftRotation(Node* parent)
{
	Node* temp;
	temp = parent->RightChild;
	parent->RightChild = leftRotation(temp);
	return rightRotation(parent);
}
Node* AVLTree:: leftRotation(Node* parent)
{
	Node* temp = parent->LeftChild;
	parent->LeftChild = temp->RightChild;
	temp->RightChild = parent;
	return temp;
}
Node* AVLTree:: rightRotation(Node* parent)
{
	Node* temp = parent->RightChild;
	parent->RightChild = temp->LeftChild;
	temp->LeftChild = parent;
	return temp;
}
int AVLTree:: height(Node* node)
{
	if (node != NULL)
	{
		int leftHeight = height(node->LeftChild);
		int rightHeight = height(node->RightChild);
		int maxHeight = max(leftHeight, rightHeight);
		return 1 + maxHeight;
	}
}
int AVLTree:: BFactor(Node* node)
{
	int leftHeight = height(node->LeftChild);
	int rightHeight = height(node->RightChild);
	return (leftHeight - rightHeight);
}
Node* AVLTree:: balancing(Node* node)
{
	int factor = BFactor(node);
	if (factor > 1)
	{
		if (BFactor(node->LeftChild) > 0)
		{
			node = leftRotation(node);
		}
		else
		{
			node = leftrightRotation(node);
		}
	}
	else if (factor < -1)
	{
		if (BFactor(node->RightChild) > 0)
		{
			node = rightleftRotation(node);
		}
		else
		{
			node = rightRotation(node);
		}
	}
	return node;
}

int main()
{
	AVLTree obj;
	int opt, val = 1;
	do
	{


		cout << "Insert()	---> Press 1" << endl
			<< "Delete()	---> Press 2" << endl
			<< "Display()	---> Press 3" << endl
			
			<< "Exit()		---> Press 0" << endl;
		cin >> opt;
		switch (opt)
		{
		case 1:
		{
			while (val != -222)
			{

				cout << "Enter the Element You want to insert/ Enter -222 To exit: " << endl;
				cin >> val;
				if (val != -222)
				{

					
					root=obj.insert(root,val);
				}
			}

			break;
		}
		case 2:
		{
			int x;
			cout << "Enter the Value You want to Delete" << endl;
			cin >> x;
			obj.Delete(root, x);
			cout << "          DELETED!" << endl;
			break;
		}
		
		
		case 3:
		{
			cout << "*****Data in your tree*****" << endl;
			obj.print(root);
			cout << endl;
			break;
		}

		default:
		{
			cout << "Select the Correct Option" << endl;
		}


		}
	} while (opt != 0);
}