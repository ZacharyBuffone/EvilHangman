#include "string.h"

struct string
{
	char* charArr;
	int size;
	int capacity; 		//number of characters string can hold (not
				//including the null-terminator)
};
typedef struct string String;

int getStringSize(char*);
void string_resize(STRING);


STRING string_initDefault()
{
	String* pStr = (String*) calloc(1, sizeof(String));
	if(pStr == NULL)
		return NULL;

	pStr->capacity = 7;
	pStr->size = 0;
	pStr->charArr = (char*) calloc(pStr->capacity, sizeof(char));
	if(pStr->charArr == NULL)
	{
		free(pStr);
		return NULL;
	}

	return pStr;
}


STRING string_initCString(char* cString)
{
	String* pStr = (String*) malloc(sizeof(String));

	int cStringSize = getStringSize(cString);
	int i;

	pStr = (String*) malloc(sizeof(String));
	if(pStr == NULL)

		return NULL;

	pStr->capacity = cStringSize;
	pStr->size = cStringSize;
	pStr->charArr = (char*) malloc(sizeof(char) * (cStringSize));
	if(pStr->charArr == NULL)
	{
		free(pStr);
		return NULL;
	}

	for(i = 0; i < cStringSize; i++)
		pStr->charArr[i] = cString[i];

	return pStr;
}

STRING string_copy(STRING copyOf)
{
	String* pCopyOf = (String*) copyOf;
	STRING copy = string_initDefault();

	int i;

	if(!copyOf)
		return NULL;


	for(i = 0; i < pCopyOf->size; i++)
	{
		string_pushBack(copy, (pCopyOf->charArr)[i]);
	}

	return copy;
}

void string_destroy(STRING* phStr)
{
	String** ppStr = (String**) phStr;
	String* pStr = *ppStr;

	if(!pStr)
		return;

	free(*ppStr);
	*phStr = NULL;

	return;
}


int string_compare(STRING hStr1, STRING hStr2)
{
	int i = 0;
	int compare = 0;
	String* str1 = (String*) hStr1;
	String* str2 = (String*) hStr2;

	while(compare == 0 && i != str1->size && i != str2->size)
	{
		compare = (int)(str1->charArr)[i] - (int)(str2->charArr)[i];
		i++;
	}

	return compare;
}


int string_getSize(STRING hStr)
{
	return ((String*)hStr)->size;
}


int string_getCapacity(STRING hStr)
{
	return ((String*)hStr)->capacity;
}


void string_print(STRING hStr)
{
	String string = *((String*) hStr);
	int i;
	for(i = 0; i < string.size; i++)
		printf("%c", string.charArr[i]);

	printf("\n");
	return;
}

Status string_extraction(STRING hStr, FILE* fp)
{
	String* pStr = (String*)hStr;

	//fp must be opened prior to running function
	char next_char;
	int num_of_conversions;
	pStr->size = 0;

	num_of_conversions = fscanf(fp, "%c", &next_char);
	while(!feof(fp) && !isspace(next_char))
	{
		if(pStr->size >= pStr->capacity)
			string_resize(hStr);

		(pStr->charArr)[pStr->size] = next_char;
		(pStr->size)++;
		num_of_conversions = fscanf(fp, "%c", &next_char);
	}

	if(feof(fp) || !num_of_conversions)
		return FAILURE;

	return SUCCESS;
}

Status string_insertion(STRING hStr, FILE* fp)
{
	if(!fp)
		return FAILURE;
	String* str = (String*)hStr;
	int i;
	for(i = 0; i < str->size; i++)
		fprintf(fp, "%c", (str->charArr)[i]);
	return SUCCESS;
}

Status string_pushBack(STRING hStr, char item)
{
	String* pStr = (String*) hStr;

	if(pStr->size >= pStr->capacity)
	{
		string_resize(hStr);
	}
	pStr->charArr[pStr->size] = item;
	pStr->size++;

	return SUCCESS;
}


Status string_popBack(STRING hStr)
{
	String* pStr = (String*) hStr;
	pStr->size--;
	return SUCCESS;
}

char* string_at(STRING hStr, int index)
{

	String* pStr = (String*) hStr;
	if(index >= 0 && index < pStr->size)
	{
		return pStr->charArr + index;
	}

	return NULL;
}

char* string_cStr(STRING hStr)
{
	String* pStr = (String*) hStr;

	if(pStr->size >= pStr->capacity)
		string_resize(hStr);

	pStr->charArr[pStr->size] = '\0';

	return pStr->charArr;
}

Status string_concat(STRING hResult, STRING hAppend)
{
	String* pResult = (String*) hResult;
	String* pAppend = (String*) hAppend;
	int i;

	while((pResult->size + pAppend->size) > pResult->capacity)
	{
		string_resize(hResult);
	}
	for(i = 0; i < pAppend->size; i++)
	{
		pResult->charArr[i + pResult->size] = pAppend->charArr[i];
	}

	pResult->size = pResult->size + pAppend->size;

	return SUCCESS;
}

Boolean string_empty(STRING hStr)
{
	String* pStr = (String*) hStr;
	if(pStr->size == 0)
		return TRUE;
	return FALSE;
}

Boolean string_contains(STRING hStr, char c)
{
	String* pStr = (String*) hStr;
	int i;

	for(i = 0; i < pStr->size; i++)
	{
		if((pStr->charArr)[i] == c)
			return TRUE;
	}
	return FALSE;

}

void string_resize(STRING hStr)
{
	String* pStr = (String*) hStr;
	int i;

	char* temp = (char*) malloc(sizeof(char) * (pStr->capacity*2));
	if(temp == NULL);

	for(i = 0; i < pStr->size; i++)
		temp[i] = pStr->charArr[i];

	free(pStr->charArr);
	pStr->charArr = temp;
	pStr->capacity *= 2;

	return;
}

int getStringSize(char* cString)
{
	int i = 0;
	while(cString[i] != '\0')
		i++;

	return i;
}
