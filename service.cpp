#include "service.h"

void Service::addSport(string newSport) {
	if (sportManager.isInRepository(newSport))
		throw Error("Already existing sport");
	sportManager.addSport(newSport);
}

void Service::removeSport(string sportToRemove) {
	if (!sportManager.isInRepository(sportToRemove))
		throw Error("Non-existing sport");
	vector<Event> eventsToRemove = eventManager.getAllEventsFromSport(sportToRemove);
	for (auto currentEvent : eventsToRemove)
		eventManager.removeEvent(currentEvent);
	sportManager.removeSport(sportToRemove);
}
void Service::addEvent(string name,string description,string sport,int year,int month,int day) {
	Event newEvent(Date(year,month,day),name, description, sport);
	if (eventManager.isInRepository(newEvent))
		throw Error("Another event with the same name on the same date");
	eventManager.addEvent(newEvent);
}

void Service::removeEvent(string name,string sport,int year,int month,int day) {
	Event toRemove(Date(year, month, day), name ,sport);
	if (!eventManager.isInRepository(toRemove))
		throw Error("No such event");
	eventManager.removeEvent(toRemove);
}

void Service::updateEvent(string name, string description, string sport, int year, int month, int day) {
	Event toUpdate(Date(year, month, day), name, description, sport);
	if (!eventManager.isInRepository(toUpdate))
		throw Error("No such event");
	//removes the event on the same date with the same name
	eventManager.removeEvent(toUpdate);
	eventManager.addEvent(toUpdate);
}

vector < Event > Service::getEvents(string sport) {
	return eventManager.getAllEventsFromSport(sport);
}

vector<string> Service::getSports() {
	return sportManager.getSports();
}