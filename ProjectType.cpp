//
//  ProjectType.cpp
//  ProjectManagementApplication
//
//  Created by Wassim Katbey on 12/29/17.
//  Copyright © 2017 Wayne State University. All rights reserved.
//

#include "ProjectType.h"
#include <iostream>
using namespace std;

projectType::projectType(string name, string desc, projectInfo i,
	int start[6], int end[6]) 
	:projectName(name), description(desc), progress(i) {

	setStartDate(start);
	setEndDate(end);

}

ostream& operator<<(ostream& osObject, projectType project) {
    
    osObject << project.projectName << endl;
    osObject << project.getStartDate() << " - " << project.getEndDate() << endl;
    osObject << project.getDescription() << endl;
    
    (project.getStatus() == 0)? osObject << "INCOMPLETE" :
    (project.getStatus() == 1)? osObject << "COMPLETE" : osObject << "ABANDONED";
    osObject << endl;
    
    for (auto itr: project.employeeMap)
        osObject << itr.second;
    
    return osObject;
}

istream& operator>>(istream& isObject, projectType project) {

	string status;
	char c;

	isObject >> project.projectName;
	isObject >> project.startDate >> c >> project.endDate; 

	isObject >> project.description;

	isObject >> status;

	(status == "INCOMPLETE") ? project.progress = projectType::INCOMPLETE : 
		(status == "COMPLETE") ? project.completeProject() : project.abandonProject();

	for (auto itr : project.employeeMap)
		isObject >> itr.second;

	return isObject;
}

void projectType::setProjectName(string name) {
    projectName = name;
}

void projectType::writeDescription(string desc) {
	description = desc;
}

void projectType::setStartDate(int start[6]) {
    
	int i = 0, j = 0;
	while (i < 8) {
		if (i == 2 || i == 5)
			startDate[i++] = '/';
		else
			startDate[i++] = start[j++];
	}
	
    
}

void projectType::setEndDate(int end[6]) {
    int i = 0, j = 0;
    while (i < 8) {
        if (i == 2 || i == 5)
            endDate[i++] = '/';
        else
            endDate[i++] = end[j++];
    }
}

void projectType::completeProject() {
    progress = COMPLETE;
}

void projectType::abandonProject() {
    progress = ABANDONED;
}

void projectType::setProjectIncomplete() {
	progress = INCOMPLETE;
}



void projectType::printSummary() const {
    cout << getProjectName() << endl;
    cout << getDescription() << endl;
    cout << getStartDate() << " - "
    << getEndDate() << endl;
}


string projectType::getProjectName() const {
    return projectName;
}

projectType::projectInfo projectType::getProgress() const {
    return progress;
}

string projectType::getStartDate() const {

    return startDate;
}

string projectType::getEndDate() const {
    
    return endDate;
    
}

string projectType::getDescription() const {
	return description;
}

void projectType::printProjectInfo() {
    cout << *this;
}

//Tool Functions//

void projectType::printToolDatabase() const {
    for (auto itr: toolMap)
        itr.second.printSummary();
}

void projectType::addTool(toolType tool) {
    toolMap.insert(pair<string,toolType>(tool.getName(),tool));

	toolMap[tool.getName()].setStatus(WORKING);
    
}
void projectType::removeTool(string toolName) {
	toolMap[toolName].setStatus(DISMISSED);
}

void projectType::markForMaintenance(string toolName) {
    toolMap[toolName].setStatus(NEEDS_MAINTENANCE);
}

void projectType::markMaintained(string toolName) {
    toolMap[toolName].setStatus(WORKING);
}

bool projectType::doesToolExist(string toolName) const {
    if (toolMap.count(toolName) == 0)
        return false;
	
	if (toolMap.at(toolName).getStatus() == DISMISSED)
		return false;

    return true;
}

toolType::statusType projectType::getToolStatus(string toolName) {
	return toolMap.at(toolName).getStatus();
}

//Employee Functions//

void projectType::printEmployeeDatabase() {
	for (auto itr : employeeMap)
		std::cout << itr.second;
}


void projectType::employ(toolType employee) {

	employeeMap.insert(pair<string, toolType>(employee.getName(), employee));

	employeeMap[employee.getName()].setStatus[WORKING];
}


void projectType::dismiss(string employeeName) {
	employeeMap[employeeName].setStatus(DISMISSED);
}

bool projectType::doesEmployeeExist(string employeeName) {
	if (employeeMap.count(employeeName) == 0)
		return false;

	if (employeeMap.at(employeeName).getStatus() == DISMISSED)
		return false;

	return true;

}

toolType::statusType projectType::getEmployeeStatus(string employeeName) const {
	return employeeMap.at(employeeName).getStatus();
}