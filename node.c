#include "node.h"

Node* node_init_default()
{
	Node* node = (Node*) malloc(sizeof(Node));
	if(!node)
		return NULL;

	node->key = NULL;
	node->value = vector_string_init_default();
	node->right = NULL;
	node->left = NULL;

	return node;
}

void node_destroy(Node** ppNode)
{
	Node* pNode = *ppNode;
	if(!pNode)
		return;

	string_destroy(&(pNode->key));
	vector_string_shallow_destroy(&(pNode->value));
	free(pNode);
	*ppNode = NULL;

	return;
}
