#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>
#include "vector_string.h"
#include "string.h"
#include "node.h"
#include "boolean.h"

typedef Node* BST;

BST bst_init_default();
void bst_destroy(BST*);

Node* bst_insert_key(BST, STRING);
Node* bst_at_key(BST, STRING);

Node* bst_at_root(BST);

Node* bst_at_largest_key(BST);
void bst_traverse(BST);

#endif
