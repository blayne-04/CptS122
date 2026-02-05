#include "header.h"

/*
NOTE: Doubly linked list setup is heavily based off of references from class, although I am
personally writing the code for it, and writing most of it from memory/intuition
*/

// Allocate space on the heap for a new node, if its allocated correctly, assign NULL to next and prev ptrs
Node* makeNode(Music data) {
	Node* newNode = malloc(sizeof(Node));

	if (newNode != NULL) {
		newNode->data = data;
		newNode->pNext = newNode->pLast = NULL;
	}

	return newNode;
}

// Insert node at front of list
bool insertFront(Node** pHead, Music data) {
	bool success = false;
	Node* pIn = makeNode(data);

	if (pIn != NULL) { //If there's memory on the heap for our node
		success = true; //Then we made a node.

		if (*pHead == NULL) { // if the list is empty
			*pHead = pIn;
		}
		else { // else list isnt empty so..
			//assign node were inserting next ptr to current head
			pIn->pNext = *pHead;
			//assign current head last ptr to node were inserting
			(*pHead)->pLast = pIn;
			//overwrite the current head with the node were inserting, we didn't lose it
			//because we stored the next link in the chain in pIn->pNext;
			*pHead = pIn;
		}
	}

	return success; //returns if it was inserted or not
}

// Simple function, just print out the list, if user specifies by artist, print by artist instead
// Precondition: if no artist is present,
void display(Node* pHead, char* artist) {
	Node* pCur = pHead;
	int counter = 0;

	//Print a single entry at a time while current node != NULL and the target artist matches current artist
	while (pCur != NULL && strcmp(artist, pCur->data.artist) == 0) {
		printf("----------------------\n");
		printf("  ENTRY NUM: %d\n", counter);
		printf("  Artist: %s\n", pCur->data.artist);
		printf("  Album: %s\n", pCur->data.albumTitle);
		printf("  Song: %s\n", pCur->data.songTitle);
		printf("  Genre: %s\n", pCur->data.genre);
		printf("  Song Len: %d:%d\n", pCur->data.songLen.minutes, pCur->data.songLen.seconds);
		printf("  Times Played: %d\n", pCur->data.timesPlayed);
		printf("  Rating: %d\n", pCur->data.rating);
		printf("----------------------\n\n");

		pCur = pCur->pNext; // move it along
		counter++;
	}
}

// Process line, returns a music struct, this function has become slightly dense so comments are inline
// Repurposing csv parsing func from last week to handle parentheses and music
Music processLine(char* buffer) {
	int linePos = 0, substringPos = 0; //Allocate a position tracker for our place in the line and our place in a single substring
	char subString[100] = ""; //Allocate a buffer for our substring, (this will be how we store values)

	//Allocatae memory for when we're ready to store, these should be sentinel values
	Music temp = {
		.artist = "",
		.albumTitle = "",
		.songTitle = "",
		.genre = "",
		.songLen = {.minutes = -1, .seconds = -1 },
		.timesPlayed = -1,
		.rating = -1
	};

	//track if were inside parentheses for each line..
	bool openParentheses = false;

	//Iterate through all the fields of the struct
	for (int fieldIndex = 0; fieldIndex < NUM_FIELDS; fieldIndex++) {
		//reset our substring position to 0, this preserves our place in the line but indicates
		//that we're beginning a new substring
		substringPos = 0;

		//this is just a big delimiter check including comma, newline, null, : and OR'D with our parentheses check
		//because if we hit a delimiter, i.e comma while were reading a name we want to ignore it, I'm making an 
		//assumption that the csv input is well formed per the spec
		while ((buffer[linePos] != ',' && buffer[linePos] != '\n' && buffer[linePos] != '\0'
			&& buffer[linePos] != ':') || openParentheses) {

			//I think handling the parentheses with a simple toggle makes the most sense here
			if (buffer[linePos] == '"') {
				openParentheses = !openParentheses;
				++linePos;
			}
			else { //if were not on the edge case with parentheses just copy from the buffer into
				//our substring container, overwriting whatever's stored in there
				subString[substringPos] = buffer[linePos];
				++linePos;
				++substringPos;
			}
		}

		// If we're on a delimiter, move it along
		if (buffer[linePos] == ',' || buffer[linePos] == ':') {
			linePos++;
		}

		// Cut off the string with a null char, this ensures that even if there's something already stored
		//in substring, our strcpy in the next bits of code will only read the parts we copied.
		subString[substringPos] = '\0';

		//Store the data we've collected into the struct, get it ready for return
		if (substringPos > 0) {
			switch (fieldIndex) {
			case ARTIST:
				strcpy(temp.artist, subString);
				break;
			case ALBUM:
				strcpy(temp.albumTitle, subString);
				break;
			case SONG:
				strcpy(temp.songTitle, subString);
				break;
			case GENRE:
				strcpy(temp.genre, subString);
				break;
			case MIN:
				temp.songLen.minutes = atoi(subString);
				break;
			case SEC:
				temp.songLen.seconds = atoi(subString);
				break;
			case TIMES_PLAYED:
				temp.timesPlayed = atoi(subString);
				break;
			case RATE:
				temp.rating = atoi(subString);
				break;

			}
		}
	}

	return temp;
}

// load items from the csv file til its empty and store them in the list
bool load(Node **pHead) {
	char buffer[100];
	int index = 0;
	FILE* musicData = fopen("musicPlayList.csv", "r");

	if (musicData == NULL) {
		return false;
	}

	while (fgets(buffer, sizeof(buffer), musicData) != NULL) {
		insertFront(pHead, processLine(buffer)); //insert the struct data from the line into our linked list
		//It's important to note that processline returns a struct of data to be stored.
	}

	fclose(musicData);

	return true;
}

// loop through the list and print data to the output file
bool store(Node* pHead) {
	FILE* musicData = fopen("musicPlayList.csv", "w");
	Node* pCur = pHead;

	if (musicData == NULL) {
		return false;
	}

	while (pCur != NULL) {
		fprintf(musicData, "\"%s\",%s,%s,%s,%d:%d,%d,%d\n",
			pCur->data.artist,
			pCur->data.albumTitle,
			pCur->data.songTitle,
			pCur->data.genre,
			pCur->data.songLen.minutes,
			pCur->data.songLen.seconds,
			pCur->data.timesPlayed,
			pCur->data.rating
		);
		pCur = pCur->pNext;
	}

	fclose(musicData);
	return true;
}

bool editNode(char* target, Node** pHead) {
	Node* curNode = *pHead;
	int matchCounter = 0;
	Node* Addresses[100];
	char buffer[50];

	//If there's nothing in the list, were not editing so return false
	if (curNode == NULL) {
		return false;
	}

	//Iterate through the nodes, whenever a match is found, add it to the count and store the index
	while (curNode != NULL){

		if (strcmp(curNode->data.albumTitle, target) == 0) {
			++matchCounter;
			printf("Would you like to edit this entry (yes/no)?\nArtist: %s, Song: %s", curNode->data.artist, curNode->data.songTitle);
			scanf("%s", buffer);

			if (strcmp("yes", buffer) == 0) { // if user says yes
				printf("Which property?\n");
				printf("1. artist, 2. song title, 3. genre, 5. song len, 6. times played, 7. rating\n");
				scanf("%d", buffer);
				
			}

		}

		curNode = curNode->pNext;
	
	editAttribute();
	

}

/*
Potential Approaches

1. prompt the user, take in all data as strings, parse based on a user selected option, this isnt very nice..

2. prompt the user for what they want to update, call a specialized function for each type of update, this seems sort of
redundant, maybe couple the same type of fields together?

3. implement a UI to select which option, then have the same type of code running in the background
*/
//bool editAttribute()


/*
- What must “edit” do?
The “edit” command must allow the user to find a record in the list by artist. If there
are multiple records with the same artist, then your program must prompt the user
which one to edit. The user may modify all of the attributes in the record.

- What must “rate” do?
The “rate” command must allow the user to assign a value of 1 – 5 to a song; 1 is the
lowest rating and 5 is the highest rating. The rating will replace the previous rating.

- What must “play” do?
The “play” command must allow the user to select a song, and must start “playing”
each song in order from the current song. “Playing” the song for this assignment
means displaying the contents of the record that represents the song for a short
period of time, clearing the screen and showing the next record in the list, etc. This
continues until all songs have been played.

- What must “exit” do?
The “exit” command saves the most recent list to the musicPlayList.csv file.
This command will completely overwrite the previous contents in the file.
*/