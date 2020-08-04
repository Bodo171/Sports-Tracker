#include "event.h"

Event::Event(){
}

Event::Event(Date _eventDate,string _name,string _sport) {
	eventDate = _eventDate;
	name = _name;
	sport = _sport;
}

Event::Event(Date _eventDate, string _name, string _description, string _sport) {
	eventDate = _eventDate;
	name = _name;
	description = _description;
	sport = _sport;
}
//to do: exception
void Event::setDate(int newYear,int newMonth,int newDay){
	if (!eventDate.setDate(newYear, newMonth, newDay))
		throw Error("Invalid date");
}

string Event::getName() {
	return name;
}

Date Event::getDate() {
	return eventDate;
}

string Event::getDescription() {
	return description;
}

void Event::setDescription(string newDescription) {
	description = newDescription;
}

string Event::getSport() {
	return sport;
}

int Event::getYear() {
	return eventDate.getYear();
}

int Event::getMonth() {
	return eventDate.getMonth();
}

int Event::getDay() {
	return eventDate.getDay();
}

bool operator==(const Event& firstEvent, const Event& secondEvent) {
	return (firstEvent.eventDate == secondEvent.eventDate && firstEvent.name == secondEvent.name &&firstEvent.sport==secondEvent.sport);
}