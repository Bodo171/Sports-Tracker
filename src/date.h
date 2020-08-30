#pragma once
#include <QDate>
#include <sstream>
#include "Error.h"
//adaptor pattern style -> just a wrapper for QDate
using std::stoi;
using std::string;
using std::to_string;
class Date {
private:
	QDate internalDate;
public:
	bool setDate(int,int,int);
	Date(int,int,int);
	Date();
	friend bool operator==(const Date&, const Date&);
	int getYear();
	int getMonth();
	int getDay();
	void fromString(string);
	string toString();
};