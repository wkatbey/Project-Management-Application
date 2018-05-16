#ifndef ProjectType_H
#define ProjectType_H
#include "toolType_.h"
#include <map>
using namespace std;

class projectType : public toolType {

	friend ostream& operator<<(ostream& osObject, projectType project);
	friend istream& operator >> (istream& isObject, projectType project);

public:

	enum projectInfo { INCOMPLETE, COMPLETE, ABANDONED };

	projectType(string name = "", string desc = "", projectInfo i = INCOMPLETE,
		string start = "", string end = "");

	void setProjectName(string name);
	void writeDescription(string desc);

	void setStartDate(string start);
	void setEndDate(string end);

	void completeProject();
	void abandonProject();

	void printSummary() const;
	void printProjectInfo(); //Marked for Removal

	string getProjectName() const;
	string getDescription() const;

	string getStartDate() const;
	string getEndDate() const;

	projectInfo getProgress() const;


	//Employee Functions//

	void printEmployeeDatabase();

	void employ(toolType employee);
	void dismiss(string employeeName);

	bool doesEmployeeExist(string employeeName);

	statusType getEmployeeStatus(string employeeName) const;

	//Tool Functions//

	void printToolDatabase() const;  //Change to printToolDatabase

	void addTool(toolType tool);
	void removeTool(string tool);

	void markForMaintenance(string tool);
	void markMaintained(string tool);

	bool doesToolExist(string tool) const;

	statusType getToolStatus(string tool);


private:

	void setProjectIncomplete();

	string projectName;
	string description;
	projectInfo progress;

	string startDate;
	string endDate;

	map<string, toolType> employeeMap;
	map<string, toolType> toolMap;

};


#endif /* ProjectType_hpp */
