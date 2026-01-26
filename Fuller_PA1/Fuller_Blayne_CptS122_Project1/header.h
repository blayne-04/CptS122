#ifndef FITBIT_PARSER
#define FITBIT_PARSER

#define _CRT_SECURE_NO_WARNINGS 
#define NUM_FIELDS 8
#define MISSING_UINT UINT_MAX

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum seqCheck {
	IN_SEQ, NOT_IN_SEQ
} Sequence;

typedef enum fields {
	ID, MIN, CAL, DIST, FLR, HR, STEP, SLEEP
} Fields;

typedef enum sleep {
	NONE, ASLEEP, AWAKE, REALLYAWAKE
} Sleep;

typedef struct fitbit {
	char patient[10];
	char minute[9];
	double calories;
	double distance;
	unsigned int floors;
	unsigned int heartRate;
	unsigned int steps;
	Sleep sleepLevel;
} FitbitData;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*			   Initialization
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void initData(FitbitData* data);
void initPatient(FILE* inputStream, char* targetPatient);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*		   Data Intake and Parsing
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void dataIntake(FILE* inputStream, char* targetPatient, FitbitData* data, int* recordCount);
bool isDupe(FitbitData* data, FitbitData* temp, int numEntries);
FitbitData processLine(char* buffer);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*			Basic Computations
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
double computeTotalCal(FitbitData* data);
double computeTotalDist(FitbitData* data);
unsigned int computeTotalFloors(FitbitData* data);
unsigned int computeTotalSteps(FitbitData* data);
unsigned int computeAvgHeartrate(FitbitData* data);
unsigned int computeMaxSteps(FitbitData* data);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*		  Worst Sleep Period Logic
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void findSleepPeriod(FitbitData* data, int* worstSleepScore, char* startMin, char* endMin);
bool sleeping(const char* timeStamp);


#endif