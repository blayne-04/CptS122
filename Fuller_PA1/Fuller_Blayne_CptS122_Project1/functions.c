#include "header.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*	Description: Initialize array of structs with sentinel values to mitigate any errors that may occur
* later in the process, i.e not enough records are provided so sums read in garbage values or something similar
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void initData(FitbitData* data) {

	for (int i = 0; i < 1440; ++i) {

		data[i].patient[0] = '\0';
		data[i].minute[0] = '\0';
		data[i].calories = -1;
		data[i].distance = -1;
		data[i].floors = MISSING_UINT;
		data[i].heartRate = 0;
		data[i].steps = MISSING_UINT;
		data[i].sleepLevel = MISSING_UINT;

	}
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*	Description: Skips the first 2 lines of the program and stores the targetPatient
* identifier for data cleansing. Note: Helped Caroline Fischer with this function
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void initPatient(FILE* inputStream, char* targetPatient) {
	char buffer[100] = "";

	if (fgets(buffer, sizeof(buffer), inputStream) != NULL) {

		strtok(buffer, ","); // Throw away the first value

		char* target = strtok(NULL, ","); //Store id

		if (target != NULL) { //Check if id exists
			strcpy(targetPatient, target);
		}

	}
	else {
		printf("File Read Error!\n");
		return;
	}

	fgets(buffer, sizeof(buffer), inputStream); //Throw away the 2nd line
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*	Description: take in data from csv file, call line processor and store result in
* array of structs if ID matches target patient ID and no duplicate entries are found, 
* Empty fields are filtered inside of "processLine" and duplicate entries are found via "isDupe"
* If minute field is empty, record is also discarded
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void dataIntake(FILE* inputStream, char* targetPatient, FitbitData* data, int* recordCount) {
	char buffer[100] = "";

	while (fgets(buffer, sizeof(buffer), inputStream) != NULL) {
		FitbitData temp = processLine(buffer);

		if (strcmp(temp.patient, targetPatient) == 0)
		{
			if (!isDupe(data, &temp, *recordCount) && temp.minute[0] != '\0') {
				data[*recordCount] = temp;
				++(*recordCount);
			}
		}
	}

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*	Description: Takes in processed line and checks for duplicate entry, returns true if a duplicate is found, false if not
* this is called only with entries that pass the ID inspection within dataIntake.
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
bool isDupe(FitbitData* data, FitbitData* temp, int numEntries) {
	for (int i = 0; i < numEntries; ++i) {
		if (strcmp(data[i].minute, temp->minute) == 0) {
			return true;
		}
	}
	return false;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*	Description: take in the current line from dataIntake, if value is blank when parsed, 
return sentinel value for that field in the final copy.
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
FitbitData processLine(char* buffer) {
	int linePos = 0, substringPos = 0;
	char subString[50] = "";

	FitbitData temp = {
		.patient = "",
		.minute = "",
		.calories = -1,
		.distance = -1,
		.floors = MISSING_UINT,
		.heartRate = 0,
		.steps = MISSING_UINT,
		.sleepLevel = MISSING_UINT
	};

	for (int fieldIndex = 0; fieldIndex < NUM_FIELDS; fieldIndex++) {

		substringPos = 0;

		while (buffer[linePos] != ',' && buffer[linePos] != '\n' && buffer[linePos] != '\0') {
			subString[substringPos] = buffer[linePos];
			++linePos;
			++substringPos;
		}

		if (buffer[linePos] == ',') {
			linePos++;
		}

		subString[substringPos] = '\0';

		if (substringPos > 0) {
			switch (fieldIndex) {
				case ID:
					strcpy(temp.patient, subString);
					break;
				case MIN:
					strcpy(temp.minute, subString);
					break;
				case CAL:
					temp.calories = atof(subString);
					break;
				case DIST:
					temp.distance = atof(subString);
					break;
				case FLR:
					temp.floors = atoi(subString);
					break;
				case HR: 
					temp.heartRate = atoi(subString);
					break;
				case STEP:
					temp.steps = atoi(subString);
					break;
				case SLEEP:
					temp.sleepLevel = atoi(subString);
					break;
					
			}
		}
	}

	return temp;
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*	Description: Calculation functions, total calories, total distance, total floors, total steps, avg heartrate, max steps
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

double computeTotalCal(FitbitData* data) {
	double totalCal = 0;

	for (int i = 0; i < 1440; ++i) {
		if (data[i].calories != -1) {
			totalCal += data[i].calories;
		}
	}

	return totalCal;
}

double computeTotalDist(FitbitData* data) {
	double totalDist = 0;

	for (int i = 0; i < 1440; ++i) {
		if (data[i].distance != -1) {
			totalDist += data[i].distance;
		}
	}
	
	return totalDist;
}

unsigned int computeTotalFloors(FitbitData* data) {
	unsigned int totalFloors = 0;

	for (int i = 0; i < 1440; ++i) {
		if (data[i].floors != MISSING_UINT) {
			totalFloors += data[i].floors;
		}
	}

	return totalFloors;
}

unsigned int computeTotalSteps(FitbitData* data) {
	unsigned int totalSteps = 0;

	for (int i = 0; i < 1440; ++i) {
		if (data[i].steps != MISSING_UINT) {
			totalSteps += data[i].steps;
		}
	}
	
	return totalSteps;
}

unsigned int computeAvgHeartrate(FitbitData* data) {
	unsigned int sumHeartrate = 0;
	int numEntries = 0;

	for (int i = 0; i < 1440; ++i) {
		if (data[i].heartRate > 0) {
			sumHeartrate += data[i].heartRate;
			++numEntries;
		};
	}
	
	if (numEntries > 0) {
		return sumHeartrate / numEntries;
	}
	else {
		return 0;
	}
}

unsigned int computeMaxSteps(FitbitData* data) {
	unsigned int maxSteps = 0;

	for (int i = 0; i < 1440; ++i) {
		if (data[i].steps != MISSING_UINT && data[i].steps > maxSteps) {
			maxSteps = data[i].steps;
		}
	}

	return maxSteps;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*	Description: Find worst sleep period within the times 9:00 PM and 8:00 AM - by tracking tempStart, tempEnd, 
* and a sleep score for all consecutive entries, and return via ptr worstSleepScore, startMin, endMin, I believe a FSM is 
* the most applicable structure for this.
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void findSleepPeriod(FitbitData* data, int* worstSleepScore, char* startMin, char* endMin) {
	int tempScore = 0;
	*worstSleepScore = 0;
	bool inTimeWindow = false, badSleep = false;
	Sequence state = NOT_IN_SEQ;
	char tempStart[9] = "", tempEnd[9] = "";

	for (int i = 0; i < 1440; ++i) { //Loop through all entries
		inTimeWindow = sleeping(data[i].minute);
		badSleep = (data[i].sleepLevel > ASLEEP);

		switch (state) {

		case NOT_IN_SEQ:
			//If we're not in a sequence and we find a bad sleep level entry, that's a new start point, also initialize the end point for single minute run cases
			if (inTimeWindow && badSleep) {
				tempScore = data[i].sleepLevel;
				state = IN_SEQ;
				strcpy(tempStart, data[i].minute);
				strcpy(tempEnd, data[i].minute);
			}
			break;

		case IN_SEQ:
			//If we're in a sequence and we find a bad sleep level entry, we move our end point forward and leave sequence indicator alone, otherwise if
			//the sleep level is fine, we leave the previous entry as the endpoint and break out of sequence
			if (inTimeWindow && badSleep) {
				tempScore += data[i].sleepLevel;
				strcpy(tempEnd, data[i].minute);
			}
			else {
				if (tempScore >= *worstSleepScore) {
					*worstSleepScore = tempScore;
					strcpy(endMin, tempEnd);
					strcpy(startMin, tempStart);
				}
				state = NOT_IN_SEQ;
				tempScore = 0;
			}
			break;
		}
	}
	/* EDGE CASE:
	im flushing the FSM here with a quick check, For the edge case where the sequence wraps around the array, i.e from 23:59 : 00 -> 0 : 00 : 00
	youd need to combine a run from the beginning if it exists with the run from the end and combine them as one contiguous run, and only
	then check if the combined score is >= worstSleepScore and assign the start and end points accordingly. Possible but another layer of
	extra engineering that I dont see defined in the PA, the current implementation checks for runs from the previous nights sleep as well as
	runs from the current nights sleep, but doesnt wrap.
	*/
	if (state == IN_SEQ && tempScore >= *worstSleepScore) {
		strcpy(startMin, tempStart);
		strcpy(endMin, tempEnd);
		*worstSleepScore = tempScore;
	}
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*	Description: Check to see if we're within the sleeping window
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

bool sleeping(const char* timeStamp) {

	if (timeStamp == NULL || timeStamp[0] == '\0') {
		return false;
	}

	char tempHour[3] = { timeStamp[0], timeStamp[1], '\0' };
	int hour = atoi(tempHour);

	if (hour <= 8 || hour >= 21) {
		return true;
	}
	else {
		return false;
	}
}