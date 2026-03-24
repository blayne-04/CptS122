#include "test.h"

/*
Insert Test, has 3 tests, one with invalid times plated and rating, one with valid data, and one with invalid seconds
passes to function, and tests head Ptr expecting NULL for invalid data and != NULL for valid data, diagnostic messages
come from inside the insert function
*/
void testInsert() {
	Node* pHead = NULL;

	Music test1 = {
	.artist = "Perry, Katy",
	.albumTitle = "Witness",
	.songTitle = "Chained to the Rhythm",
	.genre = "pop",
	.songLen = {.minutes = 4, .seconds = 36},
	.timesPlayed = -1,
	.rating = 6
	};

	Music test2 = {
	.artist = "Perry, Katy",
	.albumTitle = "Witness",
	.songTitle = "Chained to the Rhythm",
	.genre = "pop",
	.songLen = {.minutes = 4, .seconds = 36},
	.timesPlayed = 3,
	.rating = 4
	};

	Music test3 = {
	.artist = "",
	.albumTitle = "Witness",
	.songTitle = "Chained to the Rhythm",
	.genre = "pop",
	.songLen = {.minutes = 4, .seconds = 77},
	.timesPlayed = 0,
	.rating = 3
	};

	printf("-------- INSERT TEST 1 ------------- \n");
	printf("Head Location Pre Insertion %p\n", pHead);
	insertFront(&pHead, test1);
	printf("Head Location Post Insertion %p\n\n", pHead);
	if (pHead == NULL) {
		printf("Test 1 Passed\n");
	}
	else {
		printf("Test 1 Failed\n");
	}
	printf("-------- INSERT TEST 2 ------------- \n");
	printf("Head Location Pre Insertion %p\n", pHead);
	insertFront(&pHead, test2);
	printf("Head Location Post Insertion %p\n\n", pHead);
	if (pHead != NULL) {
		printf("Test 2 Passed\n");
	}
	else {
		printf("Test 2 Failed\n");
	}
	printf("-------- INSERT TEST 3 ------------- \n");
	printf("Head Location Pre Insertion %p\n", pHead);
	insertFront(&pHead, test3);
	printf("Head Location Post Insertion %p\n", pHead);
	if (pHead->pNext == NULL) {
		printf("Test 3 Passed\n");
	}
	else {
		printf("Test 3 Failed\n");
	}

}


/*
Delete test, Initializes a list, deletes the front node and tests if it deletes successfully
Also tests what happens when a NULL list is passed
*/
void testDelete() {
	Node* pHead = NULL;
	Music test1 = {
	.artist = "Perry, Katy",
	.albumTitle = "Witness",
	.songTitle = "Chained to the Rhythm",
	.genre = "pop",
	.songLen = {.minutes = 4, .seconds = 36},
	.timesPlayed = 3,
	.rating = 5
	};

	insertFront(&pHead, test1);

	printf("---------- DELETE TEST ------------- \n");
	printf("Head Location Pre Insertion %p\n", pHead);
	deleteEntry(&pHead, "Chained to the Rhythm");
	if (pHead == NULL) {
		printf("Test Passed, Head updated to NULL\n");
	}
	else {
		printf("Didn't update head\n");
	}
	printf("Head Location Post Insertion %p\n\n", pHead);

	if(!deleteEntry(&pHead, "Chained to the Rhythm")) printf("Delete Test 2 failed as expected, Passed\n");
}

/*
Hard codes an exact order, and then plays a few declared songs in the specified order
Outputs to the console, so you can check with visual inspection whether the output is correct
*/
void testShuffle() {
	Node* pHead = NULL;

	Music one = { .songTitle = "One" };
	Music two = { .songTitle = "Two" };
	Music three = { .songTitle = "Three" };

	insertFront(&pHead, three);
	insertFront(&pHead, two);
	insertFront(&pHead, one);
	
	// I free this in the play function so I declare it here as memory on the heap
	int* forcedOrder = malloc(3 * sizeof(int));
	forcedOrder[0] = 2;
	forcedOrder[1] = 0;
	forcedOrder[2] = 1;

	printf("Expected Output: Three, One, Two\n");
	printf("Output:\n");
	system("Pause");
	playShuffled(&pHead, forcedOrder, 3);
}