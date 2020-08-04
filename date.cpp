#include "date.h"

Date::Date() {
	internalDate.setDate(2000, 1, 1);
}

Date::Date(int _year, int _month, int _day) {
	if (!internalDate.setDate(_year, _month, _day))
		throw Error("Invalid date");
}

bool Date::setDate(int _year, int _month, int _day) {
	return internalDate.setDate(_year, _month, _day);
}

int Date::getYear() {
	return internalDate.year();
}

int Date::getMonth() {
	return internalDate.month();
}

int Date::getDay() {
	return internalDate.day();
}

void Date::fromString(string dateString) {
	int _year, _month, _day;
	char separator;
	istringstream input(dateString);
	input >> _year;
	input >> separator;
	input >> _month;
	input >> separator;
	input >> _day;
	setDate(_year, _month, _day);
}

string Date::toString() {
	return to_string(getYear()) + "-" + to_string(getMonth()) + "-"+to_string(getDay());
}
bool operator==(const Date& firstDate, const Date& secondDate) {
	return firstDate.internalDate == firstDate.internalDate;
}