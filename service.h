#pragma once
#include "sport.h"
#include "repository.h"
#include "sportrepository.h"
class Service {
private:
	Repository eventManager;
	SportRepository sportManager;
public:
	void addSport(string);
	void removeSport(string);
	void removeEvent(string name,string sport,int year,int month,int day);
	void addEvent(string name,string description,string sport,int year,int month,int day);
	void updateEvent(string name, string description, string sport, int year, int month, int day);
	vector<string> getSports();
	vector<Event> getEvents(string sport);
};