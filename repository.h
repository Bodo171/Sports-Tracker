#pragma once
#include "event.h"
#include <sqlite3.h>
#include <algorithm>
using std::copy_if;
using std::remove_if;
class Repository {
private:
	sqlite3* database = 0;

	const string  databaseName = "repository.db";

	const string nameColumn = "NAME";
	const string descriptionColumn="DESCRIPTION";
	const string sportColumn="SPORT";
	const string dateColumn = "DATE";

	const string tableName = "EVENTS";

	vector<Event> events;
	void getEventFromDatabase(int argc, char** argv, char** azColName);
public:

	Repository();
	void addEvent(Event);
	void removeEvent(Event);
	bool isInRepository(Event);
	vector<Event> getAllEventsFromSport(string);
	~Repository();
	///static? we'll check
	friend int getElementCallback(void* data, int argc, char** argv, char** azColName);
};