#include "sport.h"

vector<Event> Sport::getEvents() {
	return events;
}

bool Sport::hasEvent(Event toCheck) {
	for (auto Event : events)
		if (Event == toCheck)
			return true;
	return false;
}
void Sport::addEvent(Event toAdd) {
	if (hasEvent(toAdd))
		throw - 1;
	events.push_back(toAdd);
}
void Sport::removeEvent(Event toRemove) {
	if (!hasEvent(toRemove))
		throw - 1;
	events.erase(remove_if(events.begin(), events.end(), [toRemove](Event toCheck) {return toRemove == toCheck; }),
		events.end());
}

bool operator==(const Sport& firstSport, const Sport& secondSport) {
	return (firstSport.name == secondSport.name);
}