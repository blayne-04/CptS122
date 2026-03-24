#ifndef MUSIC_MANAGER
#define MUSIC_MANAGER

#define _CRT_SECURE_NO_WARNINGS

/*************************
*        IMPORTS
*************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define NUM_FIELDS 7

/*************************
*    TYPE DECLARATIONS
*************************/
typedef enum sortParams {
	SORT_ARTIST, SORT_ALBUM, SORT_RATING, SORT_TIMES_PLAYED
} SortParams;

typedef enum fields {
	ARTIST, ALBUM, SONG, GENRE, MIN, SEC, TIMES_PLAYED, RATE
} Fields;

typedef struct duration {
	int minutes;
	int seconds;
} Duration;

typedef struct movie {
	char artist[50];
	char albumTitle[50];
	char songTitle[50];
	char genre[50];
	Duration songLen;
	int timesPlayed;
	int rating;
}Music;

typedef struct node {
	Music data;
	struct node* pNext;
	struct node* pLast;
}Node;

/**************************************
*           INITIALIZATION
***************************************/
Node* makeNode(Music data);
bool insertFront(Node** pHead, Music data);
bool display(Node* pHead, char* artist);

/**************************************
*           OPERATIONS
***************************************/
//bool editNode(char* target, Node** pHead, char* editData);
Music processLine(char* buffer);
bool load(Node** pHead);
bool store(Node* pHead);
bool editNode(Node* target);
bool rate(Node** pHead);
bool play(Node* targetNode);
bool deleteEntry(Node** pHead, char* targetSong);
Node* sortSongs(Node** pHead, int parameter);
bool playShuffled(Node** pHead, int* arr, int count);
int* randomArrGen(int count);

/**************************************
*		   CONTROL FLOW
***************************************/
int findMatches(char* target, Node** pHead, Node* Addresses[]);
bool insertInteraction(Node** pHead);
bool editInteraction(Node** pHead);
void clearScreen(int n);
void delay(int ms);
void displayInteraction(Node* pHead);
bool playInteraction(Node** pHead);
bool exitProg(Node* pHead);
bool deleteInteraction(Node** pHead);
bool sortInteraction(Node** pHead);
void runMenu(Node** pHead);
bool shuffleWrapper(Node** pHead);

#endif