//
//  ProjectType.hpp
//  ProjectManagementApplication
//
//  Created by Wassim Katbey on 12/29/17.
//  Copyright © 2017 Wayne State University. All rights reserved.
//

#ifndef ProjectType_H
#define ProjectType_H
#include "toolType.h"
#include <map>
using namespace std;

class projectType : public toolType {
  
    friend ostream& operator<<(ostream& osObject, projectType project);
    friend istream& operator>>(istream& isObject, projectType project);

public:
    
    enum projectInfo {INCOMPLETE, COMPLETE, ABANDONED};
    
    projectType(string name = "", string desc = "", projectInfo i = INCOMPLETE,
                int start[6] = 0, int end[6] = 0);
    
    void setProjectName(string name);
    void writeDescription(string desc);
    
    void setStartDate(int start[6]);
    void setEndDate(int end[6]);

    void completeProject();
    void abandonProject();
    
    void increasePriority();
    void decreasePriority();
    
    void printSummary() const;
    void printProjectInfo(); //Marked for Removal
    
    string getProjectName() const;
    string getDescription() const;
    
    string getStartDate() const;
    string getEndDate() const;
    
    projectInfo getProgress() const;
    
    int getPriority() const;
    
    //Employee Functions//
    
    void employ(toolType employee);
    void dismiss(toolType employee);
    
    void printEmployeeDatabase();
    
    statusType getEmployeeStatus(toolType employee) const;
    
    //Tool Functions//
    
    void printAllTools() const;
    
    void addTool(toolType tool);
    void removeTool(string tool);
    
    void markForMaintenance(string tool);
    void markMaintained(string tool);
    
    bool doesToolExist(string tool); //Cannot be const
    
    statusType getToolStatus(string tool); //Cannot be const
    
    
    
private:

	void setProjectIncomplete();
    
    string projectName;
	string description;
    projectInfo progress;
    
    string startDate;
    string endDate;

	int priority;

    map<string, toolType> employeeMap;
    map<string,toolType> toolMap;
    
};












#endif /* ProjectType_hpp */
