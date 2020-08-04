#pragma once

#include <string>

using namespace std;
class Error {
protected:
	string messageToDisplay;
public:
	Error(string message);
	string getErrorMessage();
};
