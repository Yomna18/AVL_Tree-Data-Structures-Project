#include<iostream>
#include<cstdio>
#include<sstream>
#include<algorithm>
#define pow2(n) (1 << (n))
using namespace std;
typedef int DataType;

/*
 * Node Declaration
 */
struct avl_node                    //we used struct instead of class because we don't need functions
{
	DataType data;
	avl_node* left;
	avl_node* right;
};
avl_node* root;

/*
 * Class Declaration
 */
class avlTree
{
public:                                //Functions prototype
	int height(avl_node*);
	int diff(avl_node*);
	avl_node* LeftRotation(avl_node*);
	avl_node* RightRotation(avl_node*);
	avl_node* LeftRightRotation(avl_node*);
	avl_node* RightLeftRotation(avl_node*);
	avl_node* balance(avl_node*);
	avl_node* insert(avl_node*, int);
	avl_node* deleteNode(avl_node*, int, avlTree);
	void Empty(avl_node* t);
	avl_node* minValueNode(avl_node*);
	void display(avl_node*, int);
	void inorder(avl_node*);
	void preorder(avl_node*);
	void postorder(avl_node*);
	avlTree()
	{
		root = NULL;
	}
};

/*
 * Main Contains Menu
 */
int main()
{
	cout << "First: Our program will show the user a big tree which they can edit and then show the effect of their editing" << endl;
	avlTree avl;
	for (int i = 1; i <= 31; i++) {
		root = avl.insert(root, i);
	}
	cout << endl;
	cout << "Inorder Traversal:" << endl;
	avl.inorder(root);
	cout << endl;
	cout << "Balanced AVL Tree:" << endl;
	avl.display(root, 1);
	cout << endl;
	cout << endl;
	cout << "Now to edit in this big tree Choose one of the following numbers" << endl;
	cout << endl;
	int choice, item;
	while (1)
	{
		cout << "\n---------------------" << endl;
		cout << "AVL Tree Implementation" << endl;
		cout << "\n---------------------" << endl;
		cout << "1.Insert Element into the tree" << endl;
		cout << "2.Remove Element from the tree" << endl;
		cout << "3.Display Balanced AVL Tree" << endl;
		cout << "4.InOrder traversal" << endl;
		cout << "5.PreOrder traversal" << endl;
		cout << "6.PostOrder traversal" << endl;
		cout << "7.To empty your tree" << endl;
		cout << "8.Exit" << endl;
		cout << "Enter your Choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << endl;
			cout << "Enter value to be inserted: ";
			cin >> item;
			root = avl.insert(root, item);
			break;
		case 2:
			cout << endl;
			cout << "Enter value to be removed: ";
			cin >> item;
			root = avl.deleteNode(root, item, avl);
			break;
		case 3:
			cout << endl;
			if (root == NULL)
			{
				cout << "Tree is Empty" << endl;
				continue;
			}
			cout << "Balanced AVL Tree:" << endl;
			avl.display(root, 1);
			break;
		case 4:
			cout << endl;
			cout << "Inorder Traversal:" << endl;
			avl.inorder(root);
			cout << endl;
			break;
		case 5:
			cout << endl;
			cout << "Preorder Traversal:" << endl;
			avl.preorder(root);
			cout << endl;
			break;
		case 6:
			cout << endl;
			cout << "Postorder Traversal:" << endl;
			avl.postorder(root);
			cout << endl;
			break;
		case 7:
			cout << endl;
			cout << "Now you have emptied your old tree" << endl;
			avl.Empty(root);
			cout << endl;
			break;
		case 8:
			cout << endl;
			exit(1);
			break;
		default:
			cout << "Wrong Choice" << endl;
		}
	}
	return 0;
}


avl_node* avlTree::LeftRotation(avl_node* parent)
{
	avl_node* temp;
	temp = parent->right;
	parent->right = temp->left;
	temp->left = parent;
	return temp;
}

avl_node* avlTree::RightRotation(avl_node* parent)
{
	avl_node* temp;
	temp = parent->left;
	parent->left = temp->right;
	temp->right = parent;
	return temp;
}

/*
 * Left - Right Rotation
 */
avl_node* avlTree::LeftRightRotation(avl_node* parent)
{
	avl_node* temp;
	temp = parent->left;
	parent->left = LeftRotation(temp);
	return RightRotation(parent);
}

/*
 * Right- Left Rotation
 */
avl_node* avlTree::RightLeftRotation(avl_node* parent)
{
	avl_node* temp;
	temp = parent->right;
	parent->right = RightRotation(temp);
	return LeftRotation(parent);
}

/*
 * Height of AVL Tree
 */
int avlTree::height(avl_node* temp)                // Gets height for a certin node so we can use this height to get balance factor 
{                                                  //for example if we have node a has two subtrees b,c 
												   // we get height diff:  b(left) - c(right)= balance factor at node a
	int h = 0;
	if (temp != NULL)
	{
		int l_height = height(temp->left);
		int r_height = height(temp->right);
		int max_height = max(l_height, r_height);
		h = max_height + 1;
	}
	return h;
}

/*
 * Height Difference
 */
int avlTree::diff(avl_node* temp)                  //Function to get height difference which is equal to balance fator at certin node
{
	int l_height = height(temp->left);
	int r_height = height(temp->right);
	int b_factor = l_height - r_height;
	return b_factor;
}
void avlTree::Empty(avl_node* t)
{
	if (t == NULL)
		return;
	Empty(t->left);
	Empty(t->right);
	delete t;
	root = NULL;
}




/*
 * Balancing AVL Tree
 */
avl_node* avlTree::balance(avl_node* temp)
{
	int bal_factor = diff(temp);
	if (bal_factor > 1)
	{
		if (diff(temp->left) > 0)
			temp = RightRotation(temp);
		else
			temp = LeftRightRotation(temp);
	}
	else if (bal_factor < -1)
	{
		if (diff(temp->right) > 0)
			temp = RightLeftRotation(temp);
		else
			temp = LeftRotation(temp);
	}
	return temp;
}

/*
 * Insert Element into the tree
 */
avl_node* avlTree::insert(avl_node* root, int value)
{
	if (root == NULL)
	{
		root = new avl_node;
		root->data = value;
		root->left = NULL;
		root->right = NULL;
		return root;
	}
	else if (value < root->data)
	{
		root->left = insert(root->left, value);
		root = balance(root);
	}
	else if (value > root->data)
	{
		root->right = insert(root->right, value);
		root = balance(root);
	}
	else
		cerr << "Item already in the tree" << endl;
	return root;
}

/*
 * Display AVL Tree
 */


/*
 * Inorder Traversal of AVL Tree
 */
void avlTree::inorder(avl_node* tree)  //LNR
{
	if (tree == NULL)
		return;
	inorder(tree->left);
	cout << tree->data << "  ";
	inorder(tree->right);
}
/*
 * Preorder Traversal of AVL Tree
 */
void avlTree::preorder(avl_node* tree)  //NLR
{
	if (tree == NULL)
		return;
	cout << tree->data << "  ";
	preorder(tree->left);
	preorder(tree->right);

}

/*
 * Postorder Traversal of AVL Tree
 */
void avlTree::postorder(avl_node* tree)  //LRN
{
	if (tree == NULL)
		return;
	postorder(tree->left);
	postorder(tree->right);
	cout << tree->data << "  ";
}

/*
 * minValueNode
 */
avl_node* avlTree::minValueNode(avl_node* node)
{
	avl_node* current = node;

	/* loop down to find the leftmost leaf */
	while (current->left != NULL)
		current = current->left;

	return current;
}

/*
 * remove
 */
avl_node* avlTree::deleteNode(avl_node* root, int key, avlTree tree)
{

	// STEP 1: PERFORM STANDARD BST DELETE  
	if (root == NULL)
		return root;

	// If the key to be deleted is smaller  
	// than the root's key, then it lies 
	// in left subtree  
	if (key < root->data)
		root->left = deleteNode(root->left, key, tree);

	// If the key to be deleted is greater  
	// than the root's key, then it lies  
	// in right subtree  
	else if (key > root->data)
		root->right = deleteNode(root->right, key, tree);

	// if key is same as root's key, then  
	// This is the node to be deleted  
	else
	{
		// node with only one child or no child  
		if ((root->left == NULL) ||
			(root->right == NULL))
		{
			avl_node* temp = root->left ?
				root->left :
				root->right;

			// No child case  
			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else // One child case  
				*root = *temp; // Copy the contents of  
							   // the non-empty child  
			free(temp);
		}
		else
		{
			// node with two children: Get the inorder  
			// successor (smallest in the right subtree)  
			avl_node* temp = tree.minValueNode(root->right);

			// Copy the inorder successor's  
			// data to this node  
			root->data = temp->data;

			// Delete the inorder successor  
			root->right = deleteNode(root->right,
				temp->data, tree);
		}
	}

	// If the tree had only one node 
	// then return  
	if (root == NULL) 
		return root;

	// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE  

	tree.height(root);
	/*root->height = 1 + max(height(root->left),
		height(root->right));*/

		// STEP 3:balance

	tree.balance(root);
	return root;
}


void avlTree::display(avl_node* ptr, int level)
{
	int i;
	if (ptr != NULL)
	{
		display(ptr->right, level + 1);
		printf("\n");
		if (ptr == root)
			cout << "Root -> ";
		for (i = 0; i < level && ptr != root; i++)
			cout << "        ";
		cout << ptr->data;
		display(ptr->left, level + 1);
	}
}