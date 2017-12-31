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

ostream& operator<<(ostream& osObject, projectType project) {
    
    osObject << project.projectName << endl;
    osObject << project.getStartDate() << " - " << project.getEndDate() << endl;
    osObject << project.getDescription() << endl;
    
    (project.getStatus() == 0)? osObject << "Incomplete" :
    (project.getStatus() == 1)? osObject << "Complete" : osObject << "Abandoned";
    osObject << endl;
    
    for (auto itr: project.employeeMap)
        osObject << itr.second;
    
    return osObject;
}

istream& operator>>(istream& isObject, projectType project) {
    
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

void projectType::employ(toolType employee) {
    employeeMap[employee.getName()].setStatus(WORKING);
}


void projectType::dismiss(toolType employee) {
    employeeMap[employee.getName()].setStatus(DISMISSED);
}

toolType::statusType projectType::getEmployeeStatus(toolType employee) const {
     return employeeMap.at(employee.getName()).getStatus();
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

void projectType::printEmployeeDatabase() {
    for (auto itr: employeeMap)
        std::cout << itr.second;
}

void projectType::printProjectInfo() {
    cout << *this;
}



