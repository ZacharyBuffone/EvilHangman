#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "vector_string.h"
#include "boolean.h"

typedef struct node Node;

struct node
{
	STRING key;
	VECTOR_STRING value;
	Node* left;
	Node* right;
};

Node* node_init_default();
void node_destroy(Node** ppNode);

#endif
