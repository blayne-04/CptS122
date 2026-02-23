## Header
```
#ifndef PEERPROGRAMMING
#define PEERPROGRAMMING

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct data {
	char string[100];
	char* string2;
	char character;
	int integer;
	double decimal;
} Data;

typedef struct node {
	Data data;
	struct node* pNext;
	struct node* pPrev;
} Node;

Node* createNode(Data data);
bool insertAtFront(Data data, Node** pHead);
bool insertAtBack(Data data, Node** pHead);


#endif

```

## Basic Node Operations

```
#include "test1Prac.h"

Node* createNode(Data data) {
	Node* pNew = malloc(sizeof(Node));

	if (pNew != NULL) {
		pNew->data = data;
		pNew->pNext = pNew->pPrev = NULL;
	}

	return pNew;
}

bool insertAtFront(Data data, Node**pHead) {
	Node* pNew = createNode(data);
	
	if (pNew != NULL) {
		if (*pHead == NULL) {
			*pHead = pNew;
		}
		else {
			pNew->pNext = *pHead;
			(*pHead)->pPrev = pNew;
			*pHead = pNew;
		}
		return true;
	}
	
	return false;
}
```

## Insert at Back

```
bool insertAtBack(Data data, Node** pHead) {
	Node* pNew = createNode(data);
	Node* pCur = *pHead;

	if (pNew != NULL) {

		if (pCur == NULL) {
			*pHead = pNew;
			return true;
		}

		while (pCur->pNext != NULL) {
			pCur = pCur->pNext;
		}

		pCur->pNext = pNew;
		pNew->pPrev = pCur;
		return true;
	}

	return false;
}
```

## Destroy All

```
int destroyAllOccurences(Node** pHead, char* target) {
	Node* pCur = *pHead;
	Node* pPrev = NULL;
	int count = 0;

	if (pHead == NULL || target == NULL || pCur->data.string == NULL) { //if nulls
		return 0;
	}

	while (pCur != NULL) {

		if (strcmp(pCur->data.string, target) == 0) {
			Node* pTemp = pCur;

			//at the beginning
			if (*pHead == pCur) {
				*pHead = pCur->pNext;
				pCur = *pHead;
			}
			//in the middle or end
			else{
				pPrev->pNext = pCur->pNext;
				pCur = pCur->pNext;
			}

			free(pTemp);
			count++;
		}
		else {
			pPrev = pCur;
			pCur = pCur->pNext;
		}

	}

	return count;
}
```

## JANKY STACK CODE

```
#include "Stack.h"

bool isEmpty(Stack *pTop) {
	if (pTop) return true;
	return false;
}

Node* createNode(Data newData) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	
	if (!newNode) return false;

	return newNode;
}

bool push(Stack* pHead, Data newData) {

	Node* newNode = createNode(newData);
	if (newNode) {

		newNode->pNext = pHead->pTop;
		pHead->pTop = newNode->pNext;

		return true;
	}

	return false;
}

bool pop(Stack* pHead) {
	if (pHead) {
		Node* pTemp = pHead->pTop;
		pHead->pTop = pHead->pTop->pNext;
		free(pTemp);
		return true;
	}

	return false;
}

Data* peek(Stack* pHead) {
	if (!pHead) return;
	return pHead->pTop->data;
}
```