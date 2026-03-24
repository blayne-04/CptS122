#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class ExercisePlan {
public:
	ExercisePlan(int steps, const std::string &name, const std::string &date);
	ExercisePlan();
	ExercisePlan(const ExercisePlan& srcObject);
	~ExercisePlan(); 

	int getSteps() const;
	void setSteps(int steps);

	std::string getName() const;
	void setName(const std::string& name);

	std::string getDate() const;
	void setDate(const std::string& date);

	void editGoal();

	bool isMalformed() const;

private:
	int mSteps;
	std::string mName;
	std::string mDate;
};

std::ostream& operator<<(std::ostream& out, const ExercisePlan& plan);
std::istream& operator>>(std::istream& in, ExercisePlan& plan);