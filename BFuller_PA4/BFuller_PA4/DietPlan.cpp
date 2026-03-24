#include "DietPlan.h"
#include "FitnessAppWrapper.h"

DietPlan::~DietPlan(){}

/*
*	Description: Default Constructor
*	Input: No args
*	Output: set member data defaults to empty/sentinel values
*/
DietPlan::DietPlan() 
{
	mCalories = -1;
	mName = "";
	mDate = "";
}


/*
*	Description: Paramaterized Constructor
*	Input: <int> calories, <string> name, <string> date
*	Output: set member data to mCalories: calories, mName: name, mDate: date
*/
DietPlan::DietPlan(int calories, const std::string& name, const std::string& date) 
{
	mCalories = calories;
	mName = name;
	mDate = date;
}


/*
*	Description: Copy Constructor
*	Input: Object of type DietPlan
*	Output: Copy internal member data from srcObject to calling object
*/
DietPlan::DietPlan(const DietPlan& srcObject) 
{
	this->mCalories = srcObject.getCalories();
	this->mName = srcObject.getName();
	this->mDate = srcObject.getDate();
}


/*
*	Description: Getters and Setters
*	Inputs: Getters - N/A, Setters - <int> calories, <string> name, <string> date
*	Output: Getters - returns calling objects member data, Setters - assigns calling objects member data to input
*/
int DietPlan::getCalories() const 
{
	return mCalories;
}

void DietPlan::setCalories(int calories) {
	mCalories = calories;
}

std::string DietPlan::getName() const
{
	return mName;
}

void DietPlan::setName(const std::string& name) 
{
	mName = name;
}

std::string DietPlan::getDate() const 
{
	return mDate;
}

void DietPlan::setDate(const std::string& date)
{
	mDate = date;
};


/*
*	Description: Edit goal
*	Input: N/A
*	Output: Prompt user for a new goal, store it in struct, print struct to terminal
*/
void DietPlan::editGoal() 
{
	int newCalories = -1, option = 0;

	while (option != 4) {
		system("cls");
		do {
			std::cout << "~~~ EDIT PLAN ~~~" << std::endl;
			std::cout << "1. Edit Calorie Goal" << std::endl;
			std::cout << "2. Edit Name" << std::endl;
			std::cout << "3. Edit Date" << std::endl;
			std::cout << "4. <- Menu" << std::endl;
			std::cin >> option;
		} while (option < 1 || option > 4);

		// Clear input buffer until newline
		// numeric_limits<std::streamsize>::max() = large upper bound value 
		// Credit: cppreference.com
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		switch (option) {
		case 1:
			do {
				std::cout << "Enter new calorie goal" << std::endl;
				std::cin >> newCalories;
			} while (newCalories < 0);

			mCalories = newCalories;
			break;

		case 2:
			std::cout << "Enter new name" << std::endl;
			getline(std::cin, mName);
			break;

		case 3:
			std::cout << "Enter new date" << std::endl;
			getline(std::cin, mDate);
			break;

		case 4:
			break;
		}

		system("cls");
		std::cout << *this << std::endl;
		system("pause");
	}
}


/*
*	Description: Empty object check
*	Input: N/A
*	Output: Returns true if empty, false if not
*/
bool DietPlan::isMalformed() const 
{
	if (mName == "") 
	{
		std::cout << "No name inside diet plan" << std::endl;
		return true;
	}
	if (mDate == "")
	{
		std::cout << "No date inside diet plan" << std::endl;
		return true;
	}
	if (mCalories < 0)
	{
		std::cout << "No calorie goal inside diet plan" << std::endl;
		return true;
	}

	return false;
}


/*
*	Description: Overload outstream operator
*	Input: Outstream, Exercise plan
*	Output: Read data from an exercise plan, store it in the outstream
*	in the format specified by the project spec.
*/
std::ostream& operator<<(std::ostream& out, const DietPlan& plan)
{
	out << plan.getName() << std::endl;
	out << plan.getCalories() << std::endl;
	out << plan.getDate() << std::endl;
	out << std::endl;

	return out;
}


/*
*	Description: Overload instream operator
*	Input: Instream, Exercise plan
*	Output: Read data from a file, store it in the plan object
*	in the format specified by the project spec.
*/
std::istream& operator>>(std::istream& in, DietPlan& plan)
{
	clearBuffer(in);

	std::string name = "";
	std::string goalStr = "";
	std::string date = "";
	std::string whitespace = "";

	std::getline(in, name);
	std::getline(in, goalStr);
	std::getline(in, date);

	clearBuffer(in);

	plan.setName(name);
	if (goalStr.empty()) {
		std::cout << "ERROR: DATA MALFORMED" << std::endl;
		std::cout << "stoi guard: The input data is misaligned" << std::endl;
		system("pause");
		return in;
	}
	plan.setCalories(stoi(goalStr));
	plan.setDate(date);

	return in;
}