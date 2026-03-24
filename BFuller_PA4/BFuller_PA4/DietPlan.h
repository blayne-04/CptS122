#pragma once

#include <string>
#include <iostream>

class DietPlan {
public:
	DietPlan();
	DietPlan(int calories, const std::string& name, const std::string& date);
	DietPlan(const DietPlan& srcObject);
	~DietPlan();

	int getCalories() const;
	void setCalories(int calories);

	std::string getName() const;
	void setName(const std::string& name);

	std::string getDate() const;
	void setDate(const std::string &date);

	void editGoal();

	bool isMalformed() const;

private:
	int mCalories;
	std::string mName;
	std::string mDate;
};

std::ostream& operator<<(std::ostream& out, const DietPlan &plan);
std::istream& operator>>(std::istream& in, DietPlan& plan);