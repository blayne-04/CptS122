#include "header.h"

int main(void) {
	FitbitData data[1440];
	int recordCount = 0;
	char targetPatient[20] = "";

	FILE* inputStream = fopen("FitbitData.csv", "r");
	FILE* outputStream = fopen("Results.csv", "w");

	initData(data);

	//Input stream verification
	if (inputStream == NULL) {
		printf("ERROR: FitbitData.csv was not found\n");
		return 1;
	}

	initPatient(inputStream, targetPatient);

	dataIntake(inputStream, targetPatient, data, &recordCount);

	/*
	NOTE: I could do this final print in a separate function, but I honestly just dont want to write the 8 variables 3 times here, 
	in the header and in functions to achieve the same thing...
	*/

	double totalCal = computeTotalCal(data);
	double totalDist = computeTotalDist(data);
	unsigned int totalFloors = computeTotalFloors(data);
	unsigned int totalSteps = computeTotalSteps(data);
	unsigned int avgHr = computeAvgHeartrate(data);
	unsigned int maxSteps = computeMaxSteps(data);
	char startMin[9] = "", endMin[9] = "";
	int worstSleepScore = 0;
	findSleepPeriod(data, &worstSleepScore, startMin, endMin);

	// Output header lines
	printf("Total Calories,Total Distance,Total Floors,Total Steps,Avg Heartrate,Max Steps,Sleep\n");
 	fprintf(outputStream, "Total Calories,Total Distance,Total Floors,Total Steps,Avg Heartrate,Max Steps,Sleep\n");
	//Terminal
	printf( "%.2f,%.2f,%u,%u,%u,%u,%s-%s\n",
		totalCal,
		totalDist,
		totalFloors,
		totalSteps,
		avgHr,
		maxSteps,
		startMin,
		endMin
	);
	// Output CSV File
	fprintf(outputStream,
		"%.2f,%.2f,%u,%u,%u,%u,%s-%s\n",
		totalCal,
		totalDist,
		totalFloors,
		totalSteps,
		avgHr,
		maxSteps,
		startMin,
		endMin
	);

	//Write data loop
	for (int i = 0; i < 1440; ++i) {
		if (data[i].minute[0] != '\0') {
			//Terminal
			printf( "%s,%s,%.2f,%.2f,%u,%u,%u,%d\n",
				data[i].patient,
				data[i].minute,
				data[i].calories,
				data[i].distance,
				data[i].floors,
				data[i].heartRate,
				data[i].steps,
				data[i].sleepLevel
			);
			//Output CSV File
			fprintf(outputStream,
				"%s,%s,%.2f,%.2f,%u,%u,%u,%d\n",
				data[i].patient,
				data[i].minute,
				data[i].calories,
				data[i].distance,
				data[i].floors,
				data[i].heartRate,
				data[i].steps,
				data[i].sleepLevel
			);

		}
	}

	fclose(inputStream);
	fclose(outputStream);
}