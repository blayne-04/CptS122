#ifndef EXAMPRAC
#define EXAMPRAC

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node {
	int data;
	struct node* pNext;
} Node;

int countNodesRec(Node* pNode);
int printListRec(Node* pNode);
int sumListRec(Node* pNode);
int deleteList(Node** pC);
int deleteTarget(Node** pC, int target);

#endif