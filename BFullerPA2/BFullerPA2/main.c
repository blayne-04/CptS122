#include "header.h"
#include "test.h"

/****************************************
* Author: Blayne Fuller
* 
* Term: SPR26
* Course: CptS122 
* Assignment: MUSIC MANAGER - PA 2&3
* 
* Description: This program leverages doubly
* linked lists to store music data
****************************************/

int main(void) {
	Node* pHead = NULL;
	srand((unsigned)time(NULL));
	runMenu(&pHead);
	testInsert();
	testShuffle();
	return 0;
}