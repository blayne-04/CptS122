#ifndef MUSIC_MANAGER
#define MUSIC_MANAGER

// Imports
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_FIELDS 7

// Type declarations
typedef enum fields {
	ARTIST, ALBUM, SONG, GENRE, MIN, SEC, TIMES_PLAYED, RATE
} Fields;

typedef struct duration {
	int minutes;
	int seconds;
} Duration;

typedef struct movie {
	char artist[30];
	char albumTitle[50];
	char songTitle[50];
	char genre[20];
	Duration songLen;
	int timesPlayed;
	int rating;
}Music;

typedef struct node {
	Music data;
	struct node* pNext;
	struct node* pLast;
}Node;

//Core doubly linked list initialization functions
Node* makeNode(Music data);
bool insertFront(Node** pHead, Music data);
void printList(Node* pHead);

//Doubly linked list operations
bool editNode(char* target, Node** pHead, char* editData);

#endif