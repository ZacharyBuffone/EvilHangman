#ifndef VECTOR_STRING_H
#define VECTOR_STRING_H

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "boolean.h"
#include "status.h"

typedef void* VECTOR_STRING;

VECTOR_STRING vector_string_init_default();
void vector_string_shallow_destroy(VECTOR_STRING*);
void vector_string_deep_destroy(VECTOR_STRING*);

VECTOR_STRING vector_string_shallow_copy(VECTOR_STRING);

void vector_string_push_back(VECTOR_STRING, STRING);
void vector_string_pop_back(VECTOR_STRING);

STRING* vector_string_at(VECTOR_STRING, int);

int vector_string_get_size(VECTOR_STRING);
int vector_string_get_capacity(VECTOR_STRING);

#endif
