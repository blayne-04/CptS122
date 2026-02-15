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
void display(Node* pHead, char* artist);

/**************************************
*           OPERATIONS
***************************************/
//bool editNode(char* target, Node** pHead, char* editData);
bool load(Node** pHead);
bool store(Node* pHead);
bool editNode(Node* target);
bool rate(Node** pHead);
bool play(Node* targetNode);
bool deleteEntry(Node** pHead, char* targetSong);

/**************************************
*		   CONTROL FLOW
***************************************/
int findMatches(char* target, Node** pHead, Node* Addresses[]);
bool editInteraction(Node** pHead);
void clearBuffer();
void clearScreen(int n);
void delay(int ms);
bool playInteraction(Node** pHead);
bool exit(Node* pHead);

#endif