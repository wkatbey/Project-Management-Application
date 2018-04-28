#include "ProjectType.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

void administratorMenu();
void moderatorMenu();
void projectMenu();
void toolMenu();


int main() {

	map<string, projectType> projectDatabase; //Database that holds all project object

	//Indexing variable(s) & iterators
	int c;
	map<string, string>::iterator itrMod;
    map<string,string>::iterator itrAdmin;
    map<string, projectType>::iterator itrProj;
	
	//Menu Variables
	char loginMenu;
    char menuIndex;
	
	char adminMenu;
	char modMenu;

	char projMenu;
    char tMenu;

    
    //Booleans and Counters
    bool userCorrect;
    bool moderator;
    int loginCounter;
    
    bool projectFound;
    
   
    
    //Variables used to edit information
    //and create temporary variables
    string newName;
    string newDesc;
    
    enum statusType{NOT_AVAILABLE, WORKING, NEEDS_MAINTENANCE, DISMISSED};
    statusType toolStatus;
    
    
    
    
    
	//File IO Variables
	ifstream readProject;
	ofstream writeProject;

	//Temporary Project File
	projectType *tempProject;
    toolType *tempTool;

	//User variables
	map<string, string> adminMap;
	map<string, string> modMap;
	
	//map<string, int> maintenanceMap;
	//map<string, int> maintenancePassMap;
	
	string username;
	string password;
    
    //Variables used to access a database
    string projNameMenu;
	


	//make_heap(projectDatabase.begin(), projectDatabase.end(), projectType::getPriority); //Converts the project database into a max-heap
	
	readProject.open("Projects.txt");
	c = 0;
	while (!readProject.eof() && c < projectDatabase.size()) {
		tempProject = new projectType;
		readProject >> *tempProject;
		projectDatabase.insert(pair<string,projectType>(tempProject->getProjectName(),*tempProject));
		//push_heap(projectDatabase.begin(), projectDatabase.end());
    }
	readProject.close();

	//In this segment of code I'm inserting a new admin-user into the
	//username and password hash tables
	adminMap.insert(pair<string, string>("Admin", "password")); 
	modMap.insert(pair<string, string>("Moderator", "password"));


	//The following function asks the user for their username and password,
	//and then matches the combination with the specified account
	
	do {

        loginCounter = 0;
        
		moderator = false;
		userCorrect = false;

		cin.clear();
		cout << "Username: ";
        getline(cin, username);
        
		cin.clear();
		cout << "Password: ";
		getline(cin, password);
        
        
        

		itrAdmin = adminMap.find(username);
		
		if (itrAdmin == adminMap.end()) {
			
			itrMod = modMap.find(username);
	
			if (itrMod != modMap.end() && itrMod->second == password) {
				moderator = true;
				userCorrect = true;
			}
		}
		else
			if (itrAdmin->second == password)
				userCorrect = true;

		if (userCorrect == false) 
            cout << "Wrong username or password." << endl;
        
        loginCounter++;
		
	} while (userCorrect == 0 && loginCounter < 3);


	//The segment of code that follows the login takes the user 
	//through their respective menus

    //If moderator bool was true, user navigates through Moderator
    //Master Menu and subsequent menus.
	if (moderator == true) {
		moderatorMenu();
		cin >> modMenu;
	}
	else {
		administratorMenu();
        cin >> adminMenu >> projNameMenu;
        
        switch (adminMenu) {
            case 'I':
                break;
            case 'P':
                for (auto itr: projectDatabase) {
                    itr.second.printSummary();
                }
                break;
            case 'E':
                
                projectFound = false;
                
                do {
                    if (projectDatabase.count("projNameMenu") != 0)
                        projectFound = true;
                    
                    if (projectFound == false) {
                        cout << "Error: Project Not Found" << endl;
                        cin >> projNameMenu;
                    }
                    
                } while (projectFound == false);
                
                //Administrator has chosen to manage a project
                //Project Menu
                projectMenu();
                cin >> projMenu >> newName;
                
                switch (projMenu) {
                    case 'P':
                        cout << projectDatabase[projNameMenu];
                        break;
                    case 'T':
                        toolMenu();
                        cin >> tMenu >> newName;
                        
                        switch (tMenu) {
                            case 'P':
                                projectDatabase[projNameMenu].printAllTools();
                                break;
                            case 'A':
                                
                                tempTool = new toolType(newName); //NOT_AVAILABLE by default, placeholder
                                
                                projectDatabase[projNameMenu].addTool(*tempTool);
                                
                                delete tempTool;
                                break;
                            case 'D':
                                
                                //projectDatabase[projNameMenu].doesToolExist(newName);
                                projectDatabase[projNameMenu].removeTool(newName);
                                
                                break;
                            case 'M':
                                
                                projectDatabase[projNameMenu].markForMaintenance(newName);
                                
                                break;
                        }
                        
                        
                        break;
                    case 'N':
                        projectDatabase[projNameMenu].setProjectName(newName);
                        
                        //projNameMenu = newName;
                        break;
                    case 'D':
                        getline(cin, newDesc);
                        projectDatabase[projNameMenu].writeDescription(newDesc);
                        break;
                    case 'A':
                        projectDatabase[projNameMenu].abandonProject();
                        break;
                    case 'C':
                        projectDatabase[projNameMenu].completeProject();
                        break;
                }
                break;
            case 'M':
                administratorMenu();
                break;
            case 'Q':
                break;
        } //end administrator switch statement
        
        
        

	}



	return 0;
}

void administratorMenu() {

	cout << "Administrator Master Menu" << endl
		<< "I  - Inbox" << endl
		<< "P  - List all projects" << endl
		<< "================================" << endl
		<< "E - Manage project 'Name'" << endl
		<< "================================" << endl
		<< "M  - Display this menu again" << endl
		<< "Q  - Exit menu" << endl;

}

void projectMenu() {

	cout << "Admin Project Menu" << endl
		<< "P  - Display project information" << endl
		<< "T  - Enter tool menu" << endl
        << "E  - Enter employee menu" << endl
		<< "N + Name  - Edit Name " << endl
		<< "D  - Edit Description" << endl
		<< "================================" << endl
		<< "A  - Abandon Project" << endl
		<< "C  - Complete Projet" << endl
		<< "Q  - Return" << endl;

}

void toolMenu() {
	cout << "Tool Menu" << endl
		<< "P  - List all tools" << endl
		<< "A  - Add tool" << endl
		<< "Di - Dismiss tool 'i'" << endl
		<< "Mi - Tool 'i' needs maintenance" << endl
		<< "Q  - Return" << endl;
		
}

void moderatorMenu() {

	cout << "Maintenance Master Menu" << endl
	<< "M  - Maintenance List" << endl
	<< "Mi - Tool 'i' needs maintenance" << endl
	<< "Ri - Tool 'i' has been repaired" << endl
	<< "Di - Mark tool 'i' for dismissal" << endl
	<< "Q  - Return" << endl;

}

