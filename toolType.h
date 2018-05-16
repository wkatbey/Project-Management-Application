#ifndef toolType__h
#define toolType__h

#include <string>
#include <iostream>
using namespace std;

class toolType {

	friend ostream& operator<<(ostream& osObject, toolType& tool);
	friend istream& operator >> (istream& isObject, toolType& tool);

public:
	enum statusType { NOT_AVAILABLE, WORKING, NEEDS_MAINTENANCE, DISMISSED };

	toolType(string name = "", statusType i = NOT_AVAILABLE);

	void setName(string name);
	void setStatus(statusType i);

	void printSummary() const;

	string getName() const;
	statusType getStatus() const;

private:
	string toolName;
	statusType toolStatus;

};






#endif 
