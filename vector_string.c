#include "vector_string.h"

typedef struct vector_string
{
	int size;
	int capacity;
	STRING* data;

} VectorString;

void vector_string_resize(VectorString*);

VECTOR_STRING vector_string_init_default()
{
	VectorString* pVec = (VectorString*) malloc(sizeof(VectorString));
	if(!pVec)
		return NULL;

	pVec->size = 0;
	pVec->capacity = 7;
	pVec->data = (STRING*) calloc(pVec->capacity, sizeof(STRING));
	if(pVec->data == NULL)
	{
		free(pVec);
		return NULL;
	}

	return (VECTOR_STRING)pVec;
}

void vector_string_deep_destroy(VECTOR_STRING* phVec)
{
	VectorString** ppVec = (VectorString**) phVec;
	VectorString* pVec = *ppVec;
	int i;

	if(!pVec)  //if pVec is already free'd or NULL, do nothing
		return;


	//frees all string in vector
	for(i = 0; i < pVec->size; i++)
	{
		string_destroy(pVec->data + i);
	}

	free(pVec->data);
	free(pVec);
	*ppVec = NULL;

	return;
}

void vector_string_shallow_destroy(VECTOR_STRING* phVec)
{
	VectorString** ppVec = (VectorString**) phVec;
	VectorString* pVec = *ppVec;

	if(!pVec)  //if pVec is already free'd or NULL, do nothing
		return;

	free(pVec->data);
	free(pVec);
	*ppVec = NULL;

	return;
}

VECTOR_STRING vector_string_shallow_copy(VECTOR_STRING hOriginal)
{
	VectorString* original = (VectorString*)hOriginal;
	VECTOR_STRING copy = vector_string_init_default();
	int i;

	for(i = 0; i < original->size; i++)
	{
		vector_string_push_back(copy, (original->data)[i]);
	}

	return copy;
}

void vector_string_push_back(VECTOR_STRING hVec, STRING item)
{
	VectorString* pVec = (VectorString*) hVec;
	if(pVec->size >= pVec->capacity)
		vector_string_resize(pVec);

	(pVec->data)[pVec->size] = item;
	pVec->size = pVec->size + 1;
	return;
}

void vector_string_pop_back(VECTOR_STRING hVec)
{
	VectorString* pVec = (VectorString*) hVec;

	string_destroy(pVec->data + pVec->size - 1);
	(pVec->size)--;

	return;
}

STRING* vector_string_at(VECTOR_STRING hVec, int index)
{
	VectorString* pVec = (VectorString*) hVec;

	return pVec->data + index;
}

int vector_string_get_size(VECTOR_STRING hStr)
{
	return ((VectorString*)hStr)->size;
}

int vector_string_get_capacity(VECTOR_STRING hStr)
{
	return ((VectorString*)hStr)->capacity;
}

void vector_string_resize(VectorString* pVec)
{
	STRING* temp_data = calloc(pVec->capacity * 2 ,sizeof(STRING));
	STRING* data = pVec->data;
	int i;

	for(i = 0; i < pVec->size; i++)
	{
		//data is pVec->data and is garrenteed to be contiguous
		//so we can do this.
		temp_data[i] = data[i];
	}

	//STRINGs in orig data are not freed, and locations
	//is kept in temp_data now.
	free(pVec->data);
	pVec->data = temp_data;
	pVec->capacity = pVec->capacity * 2;
	return;
}
