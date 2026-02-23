#pragma once

#include <iostream>
#include <vector>
#include <fstream>

class DietPlan {
private:

public:
	DietPlan();
	~DietPlan();
};

class ExercisePlan {
private:
	int calories;
	std::string name;
	std::string date;

public:
	ExercisePlan();
	~ExercisePlan();
};

class FitnessAppWrapper {
private:
	//********** LOAD FUNCS ************//
	void loadDailyPlan(ifstream& fileStream, DietPlan& dailyPlan);
	void loadWeeklyPlan(ifstream& fileStream, std::vector<DietPlan>& weeklyPlan);

	//********** DISP FUNCS ************//
	void displayDailyPlan(DietPlan& dailyPlan);
	void displayWeeklyPlan(DietPlan weeklyPlan[]);

	//********** STOR FUNCS ************//
	void storeDailyPlan(ofstream& outStream, DietPlan& dailyPlan);
	void storeWeeklyPlan(ofstream& outStream, std::vector<DietPlan>& weeklyPlan);

public:
	//********** CTRL FLOW ************//
	void runApp(void);
	void displayMenu(void);

	//********** CONSTRUCT/DESTRUCT ********** //
	FitnessAppWrapper();
	~FitnessAppWrapper();
};