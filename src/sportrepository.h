#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;
using std::remove_if;
class SportRepository {
private:
	const string filePath = "sports.txt";
	vector<string> sports;
	void loadFromFile();
	void dumpToFile();
public:
	vector<string> getSports();
	SportRepository();
	~SportRepository();
	bool isInRepository(string toCheck);
	void addSport(string newSport);
	void removeSport(string sportToRemove);

};
