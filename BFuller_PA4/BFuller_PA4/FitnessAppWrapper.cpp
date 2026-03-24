#include "FitnessAppWrapper.h"
//********** CONSTRUCTOR/DESTRUCTOR ************//
FitnessAppWrapper::FitnessAppWrapper(){}

FitnessAppWrapper::~FitnessAppWrapper(){}


//********** CTRL FLOW ************//
void FitnessAppWrapper::runApp()
{
	// Used vector as a fixed size array (7 days), for practice using std::vector, Though, normally they're used dynamically
	dietPlans.resize(7);
	exercisePlans.resize(7);

	int option = 0;
	while (option != 9) {
		do
		{
			displayMenu();
			std::cin >> option;
		} while (option < 1 || option > 9);

		switch (option) {
			case 1:
			{
				std::ifstream dietDataIn("dietPlans.txt");
				loadWeeklyPlan(dietDataIn, dietPlans);
				break;
			}
			case 2:
			{
				std::ifstream exerciseDataIn("exercisePlans.txt");
				loadWeeklyPlan(exerciseDataIn, exercisePlans);
				break;
			}
			case 3:
			{
				std::ofstream dietDataOut("dietPlans.txt");
				storeWeeklyPlan(dietDataOut, dietPlans);
				break;
			}
			case 4:
			{
				std::ofstream exerciseDataOut("exercisePlans.txt");
				storeWeeklyPlan(exerciseDataOut, exercisePlans);
				break;
			}
			case 5:
			{
				system("cls");
				displayWeeklyPlan(dietPlans);
				system("pause");
				break;
			}
			case 6:
			{
				system("cls");
				displayWeeklyPlan(exercisePlans);
				system("pause");
				break;
			}
			case 7:
			{
				system("cls");
				editDietPlan();
				break;
			}
			case 8:
			{
				system("cls");
				editExercisePlan();
				break;
			}
			case 9:
			{
				if (dietPlans[0].isMalformed()) return;
				std::ofstream dietDataOut("dietPlans.txt");
				std::ofstream exerciseDataOut("exercisePlans.txt");
				storeWeeklyPlan(dietDataOut, dietPlans);
				storeWeeklyPlan(exerciseDataOut, exercisePlans);
				break;
			}
		}
	}
}


//********** DISPLAY MENU ************//
void FitnessAppWrapper::displayMenu() 
{
	system("cls");
	std::cout << WHITE << "_.~\"~._.~\"~._.~\"~._.~\"~._.~" << std::endl;
	std::cout << "       FITNESS PLANNER" << std::endl;
	std::cout << "_.~\"~._.~\"~._.~\"~._.~\"~._.~"<< RESET << std::endl << std::endl;
	std::cout << CYAN << "       WEEKLY OPTIONS" << std::endl;
	std::cout << "_.~\"~._.~\"~._.~\"~._.~\"~._.~" << std::endl;
	std::cout << "1. Load weekly diet plan" << std::endl;
	std::cout << "2. Load weekly exercise plan" << std::endl;
	std::cout << "3. Store weekly diet plan" << std::endl;
	std::cout << "4. Store weekly exercise plan" << std::endl;
	std::cout << "5. Display weekly diet plan" << std::endl;
	std::cout << "6. Display weekly exercise plan" << RESET << std::endl << std::endl;
	std::cout << GREEN << "      DAILY OPTIONS" << std::endl;
	std::cout << "_.~\"~._.~\"~._.~\"~._.~\"~._.~" << std::endl;
	std::cout << "7. Edit daily diet plan" << std::endl;
	std::cout << "8. Edit daily exercise plan" << RESET << std::endl << std::endl;
	std::cout << YELLOW << "9. EXIT" << RESET << std::endl;
}


//********** LOAD FUNCS ************//
void FitnessAppWrapper::loadDailyPlan(std::ifstream& inStream, DietPlan& dailyPlan)
{
	inStream >> dailyPlan;
}

void FitnessAppWrapper::loadDailyPlan(std::ifstream& inStream, ExercisePlan& dailyPlan)
{
	inStream >> dailyPlan;
}

void FitnessAppWrapper::loadWeeklyPlan(std::ifstream& inStream, std::vector<DietPlan>& weeklyPlan)
{
	for (int i = 0; i < DAYS_PER_WEEK; i++) {

		loadDailyPlan(inStream, weeklyPlan[i]);

		if (weeklyPlan[i].isMalformed())
		{
			std::cout << "Not enough data in weekly diet plan!" << std::endl;
			return;
		}
	}
}

void FitnessAppWrapper::loadWeeklyPlan(std::ifstream& inStream, std::vector<ExercisePlan>& weeklyPlan)
{
	for (int i = 0; i < DAYS_PER_WEEK; i++) {

		loadDailyPlan(inStream, weeklyPlan[i]);

		if (weeklyPlan[i].isMalformed())
		{
			std::cout << "Not enough data in weekly exercise plan!" << std::endl;
			return;
		}
	}
}


//********** DISP FUNCS ************//
void FitnessAppWrapper::displayDailyPlan(const DietPlan& dailyPlan) const
{
	std::cout << dailyPlan;
}

void FitnessAppWrapper::displayDailyPlan(const ExercisePlan& dailyPlan) const
{
	std::cout << dailyPlan;
}

void FitnessAppWrapper::displayWeeklyPlan(const std::vector<DietPlan>& weeklyPlan) const
{
	for (int i = 0; i < DAYS_PER_WEEK; i++) {
		if (!weeklyPlan[i].isMalformed())
		{
			std::cout << "Day " << i + 1 << ".]" << std::endl << weeklyPlan[i];
		}
		else
		{
			std::cout << "Not enough data in weekly diet plan!" << std::endl;
			return;
		}
	}
}

void FitnessAppWrapper::displayWeeklyPlan(const std::vector<ExercisePlan>& weeklyPlan) const
{
	for (int i = 0; i < DAYS_PER_WEEK; i++) {
		if (!weeklyPlan[i].isMalformed())
		{
			std::cout << "Day " << i + 1 << ".]" << std::endl << weeklyPlan[i];
		}
		else
		{
			std::cout << "Not enough data in weekly exercise plan!" << std::endl;
			return;
		}
	}
}


//********** STOR FUNCS ************//
void FitnessAppWrapper::storeDailyPlan(std::ofstream& outStream, const DietPlan& dailyPlan) const
{
	outStream << dailyPlan;
}

void FitnessAppWrapper::storeDailyPlan(std::ofstream& outStream, const ExercisePlan& dailyPlan) const
{
	outStream << dailyPlan;
}

void FitnessAppWrapper::storeWeeklyPlan(std::ofstream& outStream, const std::vector<DietPlan>& weeklyPlan) const
{
	for (int i = 0; i < DAYS_PER_WEEK; i++) {
		if (!weeklyPlan[i].isMalformed())
		{
			outStream << weeklyPlan[i];
		}
		else
		{
			std::cout << "Not enough data in weekly diet plan!" << std::endl;
			return;
		}
	}
}

void FitnessAppWrapper::storeWeeklyPlan(std::ofstream& outStream, const std::vector<ExercisePlan>& weeklyPlan) const
{
	for (int i = 0; i < DAYS_PER_WEEK; i++) {
		if (!weeklyPlan[i].isMalformed())
		{
			outStream << weeklyPlan[i];
		}
		else
		{
			std::cout << "Not enough data in weekly exercise plan!" << std::endl;
			return;
		}
	}
}

void FitnessAppWrapper::editDietPlan()
{
	int day = 0;
	displayWeeklyPlan(dietPlans);

	if (dietPlans[day].isMalformed()) { // If empty, we don't need to run the code
		return;
	}

	do {
		std::cout << "Select which day you'd like to edit the goal of (1-7)" << std::endl;
		std::cin >> day;
	} while (day < 1 || day > 7);

	if (dietPlans[day - 1].isMalformed()) { // If particular entry is empty, we don't need to run the code
		return;
	}

	dietPlans[day - 1].editGoal();
}

void FitnessAppWrapper::editExercisePlan()
{
	int day = 0;
	displayWeeklyPlan(exercisePlans);

	do {
		std::cout << "Select which day you'd like to edit the goal of (1-7)" << std::endl;
		std::cin >> day;
	} while (day < 1 || day > 7);

	exercisePlans[day - 1].editGoal();
}

void clearBuffer(std::istream& stream) {
	if (stream.peek() == '\n') {
		// Clear input buffer until newline
		// numeric_limits<std::streamsize>::max() = large upper bound value 
		// Credit: cppreference.com
		stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}