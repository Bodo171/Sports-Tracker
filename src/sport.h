#pragma once
#include <vector>
#include <algorithm>
#include "event.h"
#include "Error.h"
using std::vector;
using std::remove_if;
//this entity is not yet used, it may be used 
//only in the case the architecture is changed
class Sport {
private:
	string name,user;
	vector<Event> events;
public:
	vector<Event> getEvents();
	void addEvent(Event);
	void removeEvent(Event);
	bool hasEvent(Event);
	friend bool operator==(const Sport&, const Sport&);
};