#ifndef STRING_H
#define STRING_H

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "boolean.h"
#include "status.h"

typedef void* STRING;

STRING string_initDefault();
STRING string_initCString(char*);
STRING string_copy(STRING);
void string_destroy(STRING*);
int string_compare(STRING, STRING);

Status string_extraction(STRING, FILE*);
Status string_insertion(STRING, FILE*);

Status string_pushBack(STRING, char);
Status string_popBack(STRING);

char* string_at(STRING, int);
char* string_cStr(STRING);

Status string_concat(STRING, STRING);
Boolean string_empty(STRING);

Boolean string_contains(STRING, char);

int string_getSize(STRING);
int string_getCapacity(STRING);


void string_print(STRING);		 //for debugging

#endif
