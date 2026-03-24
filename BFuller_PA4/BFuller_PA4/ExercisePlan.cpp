#include "ExercisePlan.h"
#include "FitnessAppWrapper.h"

ExercisePlan::~ExercisePlan(){}

/*
*	Description: Default Constructor
*	Input: No args
*	Output: set member data defaults to empty/sentinel values
*/
ExercisePlan::ExercisePlan()
{
	mSteps = -1;
	mName = "";
	mDate = "";
}


/*
*	Description: Paramaterized Constructor
*	Input: <int> steps, <string> name, <string> date
*	Output: set member data to mSteps: steps, mName: name, mDate: date
*/
ExercisePlan::ExercisePlan(int steps, const std::string& name, const std::string& date)
{
	mSteps = steps;
	mName = name;
	mDate = date;
}


/*
*	Description: Copy Constructor
*	Input: Object of type ExercisePlan
*	Output: Copy internal member data from srcObject to calling object
*/
ExercisePlan::ExercisePlan(const ExercisePlan& srcObject)
{
	this->mSteps = srcObject.getSteps();
	this->mName = srcObject.getName();
	this->mDate = srcObject.getDate();
}


/*
*	Description: Getters and Setters
*	Inputs: Getters - N/A, Setters - <int> steps, <string> name, <string> date
*	Output: Getters - returns calling objects member data, Setters - assigns calling objects member data to input
*/
int ExercisePlan::getSteps() const
{
	return mSteps;
}

void ExercisePlan::setSteps(int steps) {
	mSteps = steps;
}

std::string ExercisePlan::getName() const
{
	return mName;
}

void ExercisePlan::setName(const std::string& name)
{
	mName = name;
}

std::string ExercisePlan::getDate() const
{
	return mDate;
}

void ExercisePlan::setDate(const std::string& date)
{
	mDate = date;
};


/*
*	Description: Edit goal
*	Input: N/A
*	Output: Prompt user for field to edit,
*/
void ExercisePlan::editGoal()
{	
	int newSteps = -1, option = 0;

	while (option != 4) {
		system("cls");
		do {
			std::cout << "~~~ EDIT PLAN ~~~" << std::endl;
			std::cout << "1. Edit Step Goal" << std::endl;
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
				std::cout << "Enter new step goal" << std::endl;
				std::cin >> newSteps;
			} while (newSteps < 0);

			mSteps = newSteps;
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
bool ExercisePlan::isMalformed() const
{
	if (mName == "")
	{
		std::cout << "No name inside exercise plan" << std::endl;
		return true;
	}
	if (mDate == "")
	{
		std::cout << "No date inside exercise plan" << std::endl;
		return true;
	}
	if (mSteps < 0)
	{
		std::cout << "No step goal inside exercise plan" << std::endl;
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
std::ostream& operator<<(std::ostream& out, const ExercisePlan& plan)
{
	out << plan.getName() << std::endl;
	out << plan.getSteps() << std::endl;
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
std::istream& operator>>(std::istream& in, ExercisePlan& plan)
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
	plan.setSteps(stoi(goalStr));
	plan.setDate(date);

	return in;
}