#pragma once
#include "date.h"
#include "Error.h"
#include <string>
#include <exception>
using std::string;
class Event {
private:
	Date eventDate;
	string description, name, sport;
public:
	Event();
	Event(Date _date, string _name, string _sport);
	Event(Date _date, string _name, string _description, string _sport);
	Date getDate();
	string getSport();
	string getName();
	void setDate(int,int,int);
	int getYear();
	int getMonth();
	int getDay();
	void setDescription(string);
	string getDescription();
	friend bool operator==(const Event&, const Event&);
};
