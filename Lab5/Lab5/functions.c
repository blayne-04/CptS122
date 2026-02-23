#include "header.h"

char* copyStrToHeap(char* pStr) {
	char* str = malloc(sizeof(str));

	if (str != NULL) {
		strcpy(str, pStr);
		return str;

	}

	return NULL;
}

