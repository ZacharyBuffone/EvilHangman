#ifndef ARRAY_VECTOR_STRING
#define ARRAY_VECTOR_STRING

#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "vector_string.h"

#define ARRAY_VECTOR_STRING_MAX 29
#define ARRAY_VECTOR_STRING_MIN 2

VECTOR_STRING* array_vector_string_init()
{
	FILE* fp = fopen("dictionary.txt", "r");
	int i;
	if(!fp)
		return NULL;

	VECTOR_STRING* arr = (VECTOR_STRING*) malloc(sizeof(VECTOR_STRING) * 30);

	for(i = 0; i <= ARRAY_VECTOR_STRING_MAX; i++)
		arr[i] = vector_string_init_default();

	STRING next_string = string_initDefault();
	while(string_extraction(next_string, fp))
	{
		vector_string_push_back(arr[string_getSize(next_string)], next_string);
		next_string = string_initDefault();
	}
	string_destroy(&next_string);
	fclose(fp);
	return arr;
}

void array_vector_string_destroy(VECTOR_STRING** pArr)
{
	VECTOR_STRING* arr = *pArr;
	int i;
	for(i = 0; i <= ARRAY_VECTOR_STRING_MAX; i++)
	{
		//vector_string_deep_destroy destroys all element in vec, aswell as vec
		vector_string_deep_destroy(arr + i);
	}

	free(arr);

	return;
}



#endif
