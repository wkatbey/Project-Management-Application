//
//  toolType.cpp
//  ProjectManagementApplication
//
//  Created by Wassim Katbey on 12/29/17.
//  Copyright © 2017 Wayne State University. All rights reserved.
//

#include "toolType.h"

toolType::toolType(string name, statusType i)
: toolName(name), toolStatus(i)
{}

void toolType::setName(string name) {
    toolName = name;
}

void toolType::setStatus(statusType i) {
    toolStatus = i;
}

string toolType::getName() const {
    return toolName;
}

toolType::statusType toolType::getStatus() const {
    return toolStatus;
}


