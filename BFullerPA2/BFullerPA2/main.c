#include "header.h"

int main(void) {
	Node* pHead = NULL;

    //Example data for testing
    Music songs[10] = {
        {
            .artist = "Kanye West",
            .albumTitle = "Graduation",
            .songTitle = "Stronger",
            .genre = "Hip-Hop",
            .songLen = {.minutes = 5, .seconds = 12 },
            .timesPlayed = 42,
            .rating = 5
        },
        {
            .artist = "Radiohead",
            .albumTitle = "OK Computer",
            .songTitle = "No Surprises",
            .genre = "Alternative",
            .songLen = {.minutes = 3, .seconds = 49 },
            .timesPlayed = 17,
            .rating = 4
        },
        {
            .artist = "Daft Punk",
            .albumTitle = "Discovery",
            .songTitle = "Harder Better Faster Stronger",
            .genre = "Electronic",
            .songLen = {.minutes = 3, .seconds = 45 },
            .timesPlayed = 30,
            .rating = 5
        }
    };

    bool success = insertFront(&pHead, songs[0]);
    printf("Success Status1: %d\n", success);
    success = insertFront(&pHead, songs[1]);
    printf("Success Status2: %d\n", success);
    success = insertFront(&pHead, songs[2]);
    printf("Success Status3: %d\n", success);

    printList(pHead);

}