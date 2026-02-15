#include "header.h"

/****************************************
* Author: Blayne Fuller
* 
* Term: SPR26
* Course: CptS122 
* Assignment: MUSIC MANAGER - PA 2&3
* 
* Description: This program leverages doubly
* linked lists to store music data on the
* backend and SDL for UI/UX and media
****************************************/

int main(void) {
	Node* pHead = NULL;

    //Example data for testing
    Music songs[10] = {
        {
            .artist = "Test1, Test1, Test1 Test 1 1 Test",
            .albumTitle = "Graduation",
            .songTitle = "Testing song title number 1",
            .genre = "Programming",
            .songLen = {.minutes = 5, .seconds = 12 },
            .timesPlayed = 42,
            .rating = 5
        },
        {
            .artist = "TEST2, TEST2",
            .albumTitle = "TEST2",
            .songTitle = "Testing song number 2",
            .genre = "Coding",
            .songLen = {.minutes = 3, .seconds = 49 },
            .timesPlayed = 17,
            .rating = 4
        },
        {
            .artist = "TEST3, TEST3",
            .albumTitle = "TEST3",
            .songTitle = "Testing a song title number 3",
            .genre = "Electronic",
            .songLen = {.minutes = 3, .seconds = 45 },
            .timesPlayed = 30,
            .rating = 5
        }
    };
}