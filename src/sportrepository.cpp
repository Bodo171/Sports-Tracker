#include "sportrepository.h"


SportRepository::SportRepository() {

}

SportRepository::~SportRepository() {

}

bool SportRepository::isInRepository(string toCheck) {
	for (auto sport : sports)
		if (sport == toCheck)
			return true;
	return false;
}

void SportRepository::dumpToFile() {
	ofstream output(filePath);
	for (auto sport : sports)
		output << sport << '\n';
}

void SportRepository::loadFromFile() {
	sports.clear();
	ifstream input(filePath);
	string newSport;
	while (getline(input, newSport))
		sports.push_back(newSport);
}

vector<string> SportRepository::getSports() {
	loadFromFile();
	return sports;
}

void SportRepository::addSport(string newSport) {
	loadFromFile();
	sports.push_back(newSport);
	dumpToFile();
}

void SportRepository::removeSport(string toRemove) {
	loadFromFile();
	sports.erase(remove_if(sports.begin(), sports.end(),
		[toRemove](string toCheck) {return toRemove == toCheck; }),
		sports.end());
	dumpToFile();
}