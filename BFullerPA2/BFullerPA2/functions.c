#include "header.h"

/****************************************
NOTE: Doubly linked list setup is heavily 
based off of references from class, although I am
personally writing the code for it, and 
writing most of it from memory/intuition
****************************************/

/****************************************
* Allocate space on the heap for a new 
* node, if its allocated correctly, assign 
* NULL to next and prev ptrs
****************************************/
Node* makeNode(Music data) {
	Node* newNode = malloc(sizeof(Node));

	if (newNode != NULL) {
		newNode->data = data;
		newNode->pNext = newNode->pLast = NULL;
	}

	return newNode;
}

/****************************************
* Insert node at front of list
****************************************/
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

/****************************************
* Delete a node based on a target song name
* if the song is not in the set, return false
****************************************/
bool deleteEntry(Node** pHead, char* targetSong) {
	Node* pCur = *pHead;

	//If the list is empty, exit
	if (*pHead == NULL) return false;

	// While the current node isnt null and we havent found a match move forward
	while (pCur != NULL && strcmp(pCur->data.songTitle, targetSong) != 0) {
		pCur = pCur->pNext;
	}
	// If no match at all exit
	if (pCur == NULL) return false;

	// At this point we have a match, so the question is does next exist? does last?, if so update them
	// If both exist, we implicitly handle that case just by writing individual cases for each. If we're at
	// The head, then last is null, so update pHead to pCur->pNext

	if (pCur->pLast != NULL) {
		pCur->pLast->pNext = pCur->pNext;
	}
	else {
		*pHead = pCur->pNext;
	}

	if (pCur->pNext != NULL) {
		pCur->pNext->pLast = pCur->pLast;
	}

	free(pCur); // Since we found something, we need to free at the end regardless of what happened
	return true;
}

/****************************************
* Simple function, just print out the list, 
* if user specifies by artist, print by 
* artist instead
*  Precondition: if no artist is present, 
* pass in NULL for artist
****************************************/
void display(Node* pHead, char* artist) {
	Node* pCur = pHead;
	int counter = 0;

	while (pCur != NULL) {
		if (artist == NULL || strcmp(pCur->data.artist,artist) == 0) { //if no artist is specified, or artist matches our target, print data
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
			counter++;
		}

		pCur = pCur->pNext; // move it along no matter what
	}
}

/****************************************
*	Process line, returns a music struct, 
* this function has become slightly dense 
* so comments are inline
*	Repurposing csv parsing func from 
* last week to handle parentheses and music
****************************************/

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

/****************************************
* load items from the csv file til its 
* empty and store them in the list
****************************************/
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

/****************************************
* loop through the list and print data to 
* the output file
****************************************/
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


/****************************************
* Control flow for editing an item
****************************************/
bool editInteraction(Node** pHead) {
	char targetArtist[100];
	Node* Addresses[100];
	int len = 0;
	int targetSong = 0;

	// Prompt user for artist name and find matches
	printf("Enter the name of an artist\n");
	fgets(targetArtist, sizeof(targetArtist), stdin);
	// remove trailing newline
	strtok(targetArtist, "\n");

	system('cls');
	len = findMatches(targetArtist, pHead, Addresses);
	if (len == 0) return false;

	for (int iterator = 0; iterator < len; iterator++) {
		printf("Song %d: %s, %s\n", iterator, Addresses[iterator]->data.songTitle, Addresses[iterator]->data.albumTitle);
	}
	
	// Prompt user for which song they'd like to edit, then call editNode
	do {
		printf("------------------------\n");
		printf("Enter a song num to edit\n");
		scanf("%d", &targetSong);
	} while (0 > targetSong || targetSong >= len);

	system('cls');

	Node* target = Addresses[targetSong];
	editNode(target);

	return true;
}

/****************************************
* Match finder, takes a target string, 
* compares it to artist names as well as
* song names and stores matches in an 
* array of pointers
****************************************/
int findMatches(char* target, Node** pHead, Node* Addresses[]) {
	Node* curNode = *pHead;
	int matchCounter = 0;

	//If there's nothing in the list, were not editing so return false
	if (curNode == NULL) {
		return 0;
	}

	//Iterate through the nodes, whenever a match is found, add it to the count and store the index
	while (curNode != NULL) {

		if (strcmp(curNode->data.artist, target) == 0 || strcmp(curNode->data.songTitle, target) == 0) {
			Addresses[matchCounter] = curNode;
			++matchCounter;
		}

		curNode = curNode->pNext;
	}

	return matchCounter;
}

/****************************************
* Edit a target node, supports editing
* of all properties
****************************************/
bool editNode(Node* target) {
	int option;

	if (target == NULL) {
		printf("Edit Node Target Is Empty");
		return false;
	}

	system('cls');
	printf("Which property would you like to edit\n");
	printf("1. Artist Name\n");
	printf("2. Song Title\n");
	printf("3. Genre\n");
	printf("4. Song Length\n");
	printf("5. Times Played\n");
	printf("6. Rating\n");

	do {
		scanf("%d", &option);
	} while (1 > option || option > 6);

	system('cls');
	
	// IF YOU HAVE ANY RECOMMENDATIONS ABOUT HOW TO DO THIS IN A SHORTER FORMAT PLEASE LET ME KNOW
	switch (option) {
	case 1: // ARTIST
		printf("Update artist:\n");
		clearBuffer();
		fgets(target->data.artist, 50, stdin);
		strtok(target->data.artist, "\n");
		break;

	case 2: // EDIT SONG TITLE
		printf("Update song title:\n");
		clearBuffer();
		fgets(target->data.songTitle, 50, stdin);
		strtok(target->data.songTitle, "\n");
		break;

	case 3: // EDIT GENRE
		printf("Update genre:\n");
		clearBuffer();
		fgets(target->data.genre, 50, stdin);
		strtok(target->data.genre, "\n");
		break;

	case 4: //EDIT SONG LENGTH
		printf("Update minutes:\n");
		scanf("%d", &target->data.songLen.minutes);
		printf("Update seconds:\n");
		do {
		scanf("%d", &target->data.songLen.seconds);
		} while (target->data.songLen.seconds > 59 || target->data.songLen.seconds < 0);
		break;

	case 5: //EDIT TIMES PLAYED
		printf("Update times played:\n");
		scanf("%d", &target->data.timesPlayed);
		break;

	case 6: // EDIT RATING
		do {
			printf("Update rating (1–5):\n");
			scanf("%d", &target->data.rating);
		} while (target->data.rating < 1 || target->data.rating > 5);
		break;

	default: // IF NO OPTION SOMEHOW EVEN AFTER THE EARLIER FILTER, BREAK
		break;
	}

	return true;
}

/****************************************
* Used in scenarios where I call fgets
* after scanf, clear the newline and prevent
* fgets from reading an empty line
****************************************/
void clearBuffer() {
	while (getchar() != '\n');
}

/****************************************
* Rate song, takes user inputted song name
* Allows the user to update their rating
* 1-5, supports duplicate song names
****************************************/
bool rate(Node** pHead) {
	char targetSong[100];
	Node* Addresses[100];
	int len = 0;
	int selection = 0;

	// Prompt user for song name and find matches
	printf("Enter the name of which song you'd like to rate\n");
	fgets(targetSong, sizeof(targetSong), stdin);
	// remove trailing newline
	strtok(targetSong, "\n");

	system('cls');

	len = findMatches(targetSong, pHead, Addresses);

	if (len == 0) {
		printf("That song doesn't exist!\n");
		return false;
	}

	// Print out songs and allow user to select if more than one song found, 
	// otherwise just skip and update index 0 of addresses, i.e the only song found
	if (len > 1) {
		for (int iterator = 0; iterator < len; iterator++) {
			printf("Song %d: %s, %s\n", iterator, Addresses[iterator]->data.albumTitle, Addresses[iterator]->data.songTitle);
		}

		// Prompt user for which song they'd like to rate, then update rating
		do {
			printf("------------------------\n");
			printf("Enter which song you'd like to rate\n");
			scanf("%d", &selection);
		} while (0 > selection || selection >= len);
	}

	system('cls');

	do {
		printf("Enter rating (1–5):\n");
		scanf("%d", &Addresses[selection]->data.rating);
	} while (Addresses[selection]->data.rating < 1 || Addresses[selection]->data.rating > 5);

	return true;
}

/****************************************
* Clear terminal helper function from 
* previous project, supports clearing n lines
****************************************/
void clearScreen(int n) {

	for (int i = 0; i < n; i++) {
		printf("\x1b[1A\x1b[2K\r");
	}

}

/****************************************
* Delay helper function from previous project
****************************************/
void delay(int ms) {

	clock_t start = clock();

	//Storing start time + inputted milliseconds * the number of ticks per second / 1000 for milliseconds type:clock_t var:end
	clock_t end = start + ms * (CLOCKS_PER_SEC / 1000);

	while (clock() < end) {}
}

bool playInteraction(Node** pHead) {
	char targetSong[100];
	Node* Addresses[100];
	int len = 0;
	int selection = 0;

	// Prompt user for song name and find matches
	printf("Enter the name of which song you'd like to play\n");
	fgets(targetSong, sizeof(targetSong), stdin);
	// remove trailing newline
	strtok(targetSong, "\n");

	system('cls');

	len = findMatches(targetSong, pHead, Addresses);
	if (len == 0) {
		printf("That song doesn't exist!\n");
		return false;
	}

	// If there's more than 1 match, ask which one they want to play
	if (len > 1) {
		for (int iterator = 0; iterator < len; iterator++) {
			printf("Song %d: %s, %s\n", iterator, Addresses[iterator]->data.albumTitle, Addresses[iterator]->data.songTitle);
		}

		// Prompt user for which song they'd like to play, then play it
		do {
			printf("------------------------\n");
			printf("Enter which song you'd like to play\n");
			scanf("%d", &selection);
		} while (0 > selection || selection >= len);
	}

	system("cls");

	play(Addresses[selection]);

	return true;
}

/****************************************
* Display song details and waste some time
****************************************/
bool play(Node* targetNode) {

	Node* pCur = targetNode;

	if (pCur == NULL) return false;

	while (pCur != NULL) {
		printf("Playing: %s\n Artist: %s\n Album: %s\n", pCur->data.songTitle, pCur->data.artist, pCur->data.albumTitle);
		// A small delay animation, just printing . . . . with 200 ms gaps 3 times
		for (int j = 0; j < 3; j++) {

			for (int i = 0; i < 5; i++) {
				printf(".");
				delay(200);
			}

			clearScreen(1);
		}

		system("cls");
		pCur = pCur->pNext;
	}

	return true;
}

bool exit(Node* pHead) {
	return store(pHead);
}