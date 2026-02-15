#include "header.h"

int countNodesRec(Node* pNode) {

	if (pNode == NULL) {
		return 0;
	}
	
	return 1 + countNodesRec(pNode->pNext);
}

void printListRec(Node* pNode) {

	if (pNode == NULL) {
		return 0;
	}

	printf("int: %d", pNode->data);
	printListRec(pNode->pNext);
}

int sumListRec(Node* pNode) {

	if (pNode == NULL) {
		return 0;
	}

	return pNode->data + sumListRec(pNode->pNext);
}

//deletes an entire list, returns count of how many nodes were deleted
int deleteList(Node** pC) {

	//If we reach the end of the list
	if (*pC == NULL) {
		return 0;
	}
	
	Node* pT = *pC;
	*pC = (*pC)->pNext;
	free(pT);

	return 1 + deleteList(pC);
}

Node* deleteTarget(Node* pC, int target)
{
	if (pC == NULL)
		return NULL;

	pC->pNext = deleteTarget(pC->pNext, target);

	if (pC->data == target)
	{
		Node* pT = pC;
		pC = pC->pNext;
		free(pT);
	}

	return pC;
}

Node* createNode(int data)
{
	Node* newNode = malloc(sizeof(Node));

	if (newNode == NULL)
		return NULL;

	newNode->data = data;
	newNode->pNext = NULL;

	return newNode;
}

bool insertAtEnd(Node** pHead) {
	Node* newNode = createNode(1), * pCur = *pHead;

	if (newNode != NULL) {

		if (pCur == NULL) {
			*pHead = newNode;
			return true;
		}

		while (pCur->pNext != NULL) {
			pCur = pCur->pNext;
		}

		pCur->pNext = newNode;
		return true;
	}
	
	return false;
}

bool reverseList(Node** pHead) {
	Node* pPrev, * pCur, * pTemp;
	pPrev = pTemp = NULL;
	pCur = *pHead;

	if (pCur == NULL || pCur->pNext == NULL) { //short circuit eval so it doesnt crash on pCur->pNexts
		return false; //theres no list to reverse if theres one node or the list is empty.
	}

	while (pCur->pNext != NULL) {
		// Get our pointers ready and in place for some stitching
		pPrev = pCur;
		pCur = pCur->pNext;
		pTemp = pCur->pNext;

		// Reverse 
		
	}

}