//
//  toolType.hpp
//  ProjectManagementApplication
//
//  Created by Wassim Katbey on 12/29/17.
//  Copyright © 2017 Wayne State University. All rights reserved.
//

#ifndef toolType_h
#define toolType_h

#include <string>
#include <iostream>
using namespace std;

class toolType {
    
    friend ostream& operator<<(ostream& osObject, toolType& tool);
    friend istream& operator>>(istream& isObject, toolType& tool);
    
public:
    enum statusType {NOT_AVAILABLE, WORKING, NEEDS_MAINTENANCE, DISMISSED};
    
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






#endif /* toolType_hpp */
