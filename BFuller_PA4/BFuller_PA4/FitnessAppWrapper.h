#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "DietPlan.h"
#include "ExercisePlan.h"

#define DAYS_PER_WEEK 7

//********** ANSI COLORS ************//
#define RESET  "\033[0m"
#define WHITE  "\033[1;37m"
#define CYAN   "\033[1;36m"
#define GREEN  "\033[1;32m"
#define YELLOW "\033[1;33m"

class FitnessAppWrapper {

public:
	//********** CTRL FLOW ************//
	void runApp();

	//********** CONSTRUCT/DESTRUCT ********** //
	FitnessAppWrapper();
	~FitnessAppWrapper();

private:
	//********** MEMBER DATA ************//
	std::vector<DietPlan> dietPlans;
	std::vector<ExercisePlan> exercisePlans;

	//********** CTRL FLOW ************//
	void displayMenu();

	//********** LOAD FUNCS ************//
	void loadDailyPlan(std::ifstream& inStream, DietPlan& dailyPlan);
	void loadDailyPlan(std::ifstream& inStream, ExercisePlan& dailyPlan);
	void loadWeeklyPlan(std::ifstream& inStream, std::vector<DietPlan>& weeklyPlan);
	void loadWeeklyPlan(std::ifstream& inStream, std::vector<ExercisePlan>& weeklyPlan);

	//********** DISP FUNCS ************//
	void displayDailyPlan(const DietPlan& dailyPlan) const;
	void displayDailyPlan(const ExercisePlan& dailyPlan) const;
	void displayWeeklyPlan(const std::vector<DietPlan>& weeklyPlan) const;
	void displayWeeklyPlan(const std::vector<ExercisePlan>& weeklyPlan) const;

	//********** STOR FUNCS ************//
	void storeDailyPlan(std::ofstream& outStream, const DietPlan& dailyPlan) const;
	void storeDailyPlan(std::ofstream& outStream, const ExercisePlan& dailyPlan) const;
	void storeWeeklyPlan(std::ofstream& outStream, const std::vector<DietPlan>& weeklyPlan) const;
	void storeWeeklyPlan(std::ofstream& outStream, const std::vector<ExercisePlan>& weeklyPlan) const;

	//********** EDIT FUNCS ************//
	void editDietPlan();
	void editExercisePlan();
};

void clearBuffer(std::istream& stream);