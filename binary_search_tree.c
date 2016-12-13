#include "binary_search_tree.h"

void recursive_destroy_root(Node*);
Node* recursive_find_largest(Node*);
void recursive_traverse(Node*);
BST bst_init_default()
{
	Node* root = node_init_default();

	return (BST) root;
}

void bst_destroy(BST* phRoot)
{
	Node** ppRoot = (Node**) phRoot;
	Node*  pRoot  = *ppRoot;
	if(!pRoot)
		return;

	recursive_destroy_root(pRoot);
	*ppRoot = NULL;
	return;
}

void recursive_destroy_root(Node* root)
{
	if(root->left)
		recursive_destroy_root(root->left);
	if(root->right)
		recursive_destroy_root(root->right);

	node_destroy(&root);
	return;

}

Node* bst_insert_key(BST hRoot, STRING new_key)
{
	Node* root = (Node*)hRoot;

	if(root->key == NULL)
	{
		root->key = new_key;
		return root;
	}
	Node* new_node = node_init_default();
	new_node->key = new_key;

	Node* temp = root;
	int compare = string_compare(root->key, new_key);
	while(1)
	{
		if(compare > 1)
		{
			if(temp->right)
			{
				temp = temp->right;
			}
			else
			{
				temp->right = new_node;
				break;
			}

		}
		else
		{
			if(temp->left)
			{
				temp = temp->left;
			}
			else
			{
				temp->left = new_node;
				break;
			}

		}
	}

	return new_node;
}

Node* bst_at_key(BST hRoot, STRING key)
{
	Node* root = (Node*) hRoot;

	if(root->key == NULL)
		return NULL;

	Node* curr = root;
	int compare = string_compare(curr->key, key);
	while(compare != 0)
	{
		if(compare > 0)
			curr = curr->right;
		else
			curr = curr->left;

		//if curr is null, key does not exist in tree
		if(!curr)
			return NULL;
		compare = string_compare(curr->key, key);
	}

	return curr;
}

Node* bst_at_root(BST hRoot)
{
	return (Node*)hRoot;
}

Node* bst_at_largest_key(BST hRoot)
{
	Node* root = (Node*)hRoot;
	return recursive_find_largest(root);
}

Node* recursive_find_largest(Node* root)
{
	Node* largest = root;
	
	Node* right_largest = NULL;
	Node* left_largest = NULL;
	Node* child_largest = NULL;
	int left_size;
	int right_size;
	int root_size = vector_string_get_size(root->value);
	if(root->right)
	{
		right_largest = recursive_find_largest(root->right);
		right_size = vector_string_get_size(right_largest->value);
	}
	if(root->left)
	{
		left_largest = recursive_find_largest(root->left);
		left_size = vector_string_get_size(left_largest->value);
	}

	//compare children to root
	if(left_largest && right_largest)
	{
		child_largest =
			((right_size > left_size) ? right_largest : left_largest);
		if(vector_string_get_size(child_largest->value) > root_size)
			largest = child_largest;
	}
	if(!left_largest && right_largest)
	{
		if(right_size > root_size)
			largest = right_largest;
	}
	if(!right_largest && left_largest)
	{
		if(left_size > root_size)
			largest = left_largest;
	}

	return largest;
}

void bst_traverse(BST hRoot)
{
	Node* root = (Node*)hRoot;
	recursive_traverse(root);
	return;
}

void recursive_traverse(Node* root)
{
	string_insertion(root->key, stdout);
	printf(": %d\n", vector_string_get_size(root->value));
	if(root->right)
		recursive_traverse(root->right);
	if(root->left)
		recursive_traverse(root->left);
	return;
}
