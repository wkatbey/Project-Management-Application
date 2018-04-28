//
//  toolType.cpp
//  ProjectManagementApplication
//
//  Created by Wassim Katbey on 12/29/17.
//  Copyright © 2017 Wayne State University. All rights reserved.
//

#include "toolType.h"

ostream& operator<<(ostream& osObject, toolType& tool) {
	
	osObject << tool.toolName;
	
	(tool.toolStatus == 0) ?  osObject << "NOT_AVAILABLE"
		: (tool.toolStatus == 1) ? osObject << "WORKING" 
		: (tool.toolStatus == 2)?  osObject << "NEEDS_MAINTENANCE" : osObject << "DISMISSED";
	return osObject;
}

istream& operator>>(istream& isObject, toolType& tool) {

	string status;

	isObject >> tool.toolName;

	isObject >> status;

	(status == "NOT_AVAILABLE") ? tool.toolStatus = toolType::NOT_AVAILABLE
		: (status == "WORKING") ? tool.toolStatus = toolType::WORKING
		: (status == "NEEDS_MAINTENANCE") ? tool.toolStatus = toolType::NEEDS_MAINTENANCE 
		: tool.toolStatus = toolType::DISMISSED;

	return isObject;
}


toolType::toolType(string name, statusType i)
: toolName(name), toolStatus(i)
{}

void toolType::setName(string name) {
    toolName = name;
}

void toolType::setStatus(statusType i) {
    toolStatus = i;
}

void toolType::printSummary() const {
    cout << toolName << " ";
    
    (toolStatus == 0) ?  cout << "NOT AVAILABLE"
    : (toolStatus == 1) ? cout << "WORKING"
    : (toolStatus == 2)?  cout << "NEEDS MAINTENANCE" : cout << "DISMISSED";
    
    cout << endl;

}

string toolType::getName() const {
    return toolName;
}

toolType::statusType toolType::getStatus() const {
    return toolStatus;
}


