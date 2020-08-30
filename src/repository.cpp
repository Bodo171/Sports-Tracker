#include "repository.h"
static int emptyCallback(void* data, int argc, char** argv, char** azColName) {
	return 0;
}

int getElementCallback(void* data, int argc, char** argv, char** azColName) {
	Repository* myRepository=(Repository*) data;
	myRepository->getEventFromDatabase(argc,argv,azColName);
	return 0;
}

Repository::Repository() {
	sqlite3_open(databaseName.c_str(), &database);
	char* errorMessage=0;

	string command = "CREATE TABLE IF NOT EXISTS " + tableName + " " + " ( " + nameColumn + " TEXT, " + sportColumn + " TEXT, " + dateColumn + " TEXT, " + descriptionColumn+ " TEXT );";
	int exitCode=sqlite3_exec(database, command.c_str(), emptyCallback, 0, &errorMessage);
	if (exitCode != SQLITE_OK) {
		throw Error("Please restart");
	}
}

void Repository::getEventFromDatabase(int numberOfArguments, char** argumentValues, char** argumentNames) {
	string name, description, sport;
	Date date;
	for (int i = 0; i < numberOfArguments; i++) {
		string currentColumn(argumentNames[i]), currentValue(argumentValues[i]);
		if (currentColumn == nameColumn)
			name = currentValue;
		if (currentColumn == descriptionColumn)
			description = currentValue;
		if (currentColumn == sportColumn)
			sport = currentValue;
		if (currentColumn == dateColumn)
			date.fromString(currentValue);
	}
	events.push_back(Event(date,name,description,sport));
}

void Repository::addEvent(Event toAdd) {
	string columns = " (" + nameColumn + "," + sportColumn + ", " +descriptionColumn+", "+dateColumn+")";
	string values = "('"+toAdd.getName()+"', '"+toAdd.getSport()+"', '"+toAdd.getDescription()+"', '"+toAdd.getDate().toString()+"')";
	string command = "INSERT INTO " + tableName +" "+columns+ " VALUES "+values+" ;";
	char* errorMessage = 0;
	int exitCode=sqlite3_exec(database, command.c_str(), emptyCallback, this,&errorMessage);
	if (exitCode!=SQLITE_OK) {
		string myErrorMessage(errorMessage);
		sqlite3_free(errorMessage);
		throw Error(myErrorMessage);
	}
}

void Repository::removeEvent(Event toRemove) {
	string nameCondition = nameColumn+" = '"+toRemove.getName()+"'";
	string sportCondition = sportColumn+" = '"+toRemove.getSport()+"'";
	string dateCondition = dateColumn+" = '"+toRemove.getDate().toString()+"'";
	char* errorMessage = 0;

	string command = "DELETE FROM " + tableName+" WHERE "+nameCondition+" AND "+sportCondition+ " AND "+dateCondition+" ;";

	int exitCode = sqlite3_exec(database, command.c_str(), emptyCallback, this, &errorMessage);
	if (exitCode!=SQLITE_OK) {
		string myErrorMessage(errorMessage);
		sqlite3_free(errorMessage);
		throw Error(myErrorMessage);
	}

}


bool Repository::isInRepository(Event toCheck) {
	string nameCondition = nameColumn + " = " + "'"+toCheck.getName()+"'";
	string sportCondition = sportColumn + " = " + "'"+toCheck.getSport()+"'";
	string dateCondition = dateColumn + " = " + "'"+toCheck.getDate().toString()+"'";
	char* errorMessage = 0;

	string command = "SELECT * FROM " + tableName + " WHERE " + nameCondition + " AND " + sportCondition + " AND " + dateCondition+" ;";

	int exitCode = sqlite3_exec(database, command.c_str(), getElementCallback, this, &errorMessage);
	if (exitCode != SQLITE_OK) {
		string myErrorMessage(errorMessage);
		sqlite3_free(errorMessage);
		throw Error(myErrorMessage);
	}
	bool toReturn = (events.size()>0);
	events.clear();
	return toReturn;
}

vector<Event> Repository::getAllEventsFromSport(string sport) {
	char* errorMessage = 0;
	string sportCondition = sportColumn + " = " + "'"+sport+"'";
	string command = "SELECT * from " + tableName+ " WHERE "  + sportCondition +" ;";

	int exitCode = sqlite3_exec(database, command.c_str(), getElementCallback, this, &errorMessage);
	if (exitCode != SQLITE_OK) {
		string myErrorMessage(errorMessage);
		sqlite3_free(errorMessage);
		throw Error(myErrorMessage);
	}
	vector<Event> toReturn = events;
	events.clear();
	return toReturn;
}

Repository::~Repository() {
	sqlite3_close(database);
}
/*
void Repository::addEvent(Event toAdd) {
	events.push_back(toAdd);

}

void Repository::removeEvent(Event toRemove) {
	events.erase(remove_if(events.begin(), events.end(),
		[toRemove](Event toCheck) {return toRemove == toCheck; }),
		events.end());
}


bool Repository::isInRepository(Event toCheck) {
	for (auto Event : events)
		if (Event == toCheck)
			return true;
	return false;
}

vector<Event> Repository::getAllEventsFromSport(string sport) {
	vector<Event> toReturn(events.size());
	auto newEnd = copy_if(events.begin(), events.end(), toReturn.begin(),
		[sport](Event toCheck) {return toCheck.getSport() == sport; });
	toReturn.resize(newEnd - toReturn.begin());
	return toReturn;
}
*/