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
void projectCreationTool();

int main() {

	map<string, projectType> projectDatabase; //Database that holds all project object

											  //Indexing variable(s) & iterators
	int c;
	map<string, string>::iterator itrMod;
	map<string, string>::iterator itrAdmin;
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
	bool error;

	//Variables used to edit information
	//and create temporary variables
	string newName;
	string newDesc;

	int descriptionLines;
	string *projDescription;
	string startDate;
	string endDate;
	int tempProjStatus;
	projectType::projectInfo projStatus;

	enum statusType { NOT_AVAILABLE, WORKING, NEEDS_MAINTENANCE, DISMISSED };
	statusType toolStatus;

	//Variables used to access a project/tool from the database
	string projIndex;
	string toolIndex;

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


	//make_heap(projectDatabase.begin(), projectDatabase.end(), projectType::getPriority); //Converts the project database into a max-heap

	readProject.open("Projects.txt");
	c = 0;
	while (!readProject.eof() && c < projectDatabase.size()) {
		tempProject = new projectType;
		readProject >> *tempProject;
		projectDatabase.insert(pair<string, projectType>(tempProject->getProjectName(), *tempProject));
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
		cin >> adminMenu;

		//User inputs 'E' and the Project Name
		if (adminMenu == 'E')
			getline(cin, projIndex);

		switch (adminMenu) {
		case 'I':
			//Requires the creation of an Administrator Object
			break;
		case 'P':
			for (auto itr : projectDatabase) {
				itr.second.printSummary();
			}
			break;
		case 'C':

			projectCreationTool();

			cin.ignore();
			getline(cin, projIndex);
			cin >> descriptionLines;
			projDescription = new string[descriptionLines];

			for (int i = 0; i < descriptionLines; i++) {
				cin.ignore();
				getline(cin, projDescription[i]);
			}
				
			cin >> startDate;

			cin >> endDate;

			cin >> tempProjStatus;

			do {

				error = false;

				if (tempProjStatus == 0)
					projStatus = projectType::INCOMPLETE;
				else if (tempProjStatus == 1)
					projStatus = projectType::COMPLETE;
				else if (tempProjStatus == 2)
					projStatus = projectType::COMPLETE;
				else {
					error = true;
					cout << "Incorrect Status, Input 0,1,2: ";
					cin >> tempProjStatus;
				}
	
			} while (error == true);

			tempProject = new projectType(projIndex, *projDescription, projStatus, startDate, endDate);

			projectDatabase.insert(pair<string, projectType>(projIndex, *tempProject));

			//delete tempProject;

			break;
		case 'E':


			//Checks if project name is in the database.

			projectFound = false;

			do {
				if (projectDatabase.count(projIndex) != 0)
					projectFound = true;

				if (projectFound == false) {
					cout << "Error: Project Not Found" << endl;
					cin >> projIndex;
					//Throw an exception here, so that the user can exit this cycle
				}

			} while (projectFound == false);

			//Administrator has chosen to manage a project
			//Project Menu
			projectMenu();
			cin >> projMenu;

			if (projMenu == 'N')
				getline(cin, newName);

			switch (projMenu) {
			case 'P':
				cout << projectDatabase[projIndex];
				break;
			case 'T':

				//Administrator has entered the tool menu
				toolMenu();
				cin >> tMenu;

				if (tMenu == 'D' || tMenu == 'M' || tMenu == 'A')
					getline(cin, toolIndex);

				switch (tMenu) {
				case 'P':
					projectDatabase[projIndex].printToolDatabase();
					break;
				case 'A':

					tempTool = new toolType(toolIndex); //NOT_AVAILABLE by default, placeholder

					projectDatabase[projIndex].addTool(*tempTool);

					delete tempTool;

					break;
				case 'D':

					projectDatabase[projIndex].doesToolExist(toolIndex);
					projectDatabase[projIndex].removeTool(toolIndex);

					break;
				case 'M':

					projectDatabase[projIndex].doesToolExist(toolIndex);
					projectDatabase[projIndex].markForMaintenance(toolIndex);

					break;
				}
				break;
			case 'N':
				projectDatabase[projIndex].setProjectName(newName);
				break;
			case 'D':
				getline(cin, newDesc);
				projectDatabase[projIndex].writeDescription(newDesc);
				break;
			case 'A':
				projectDatabase[projIndex].abandonProject();
				break;
			case 'C':
				projectDatabase[projIndex].completeProject();
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
		<< "C  - Create a Project" << endl
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

void projectCreationTool() {
	cout << "Project Creation Tool" << endl
		<< "To create a project, input the project" << endl
		<< "variables in the following manner:" << endl
		<< "(1) Input Project Name" << endl
		<< "(2) Input the description line number" << endl
		<< "(3) Input the description with variable number of lines" << endl
		<< "(4) Input the start date DD-MM-YY (w/o dashes)" << endl
		<< "(5) Input the end date DD-MM-YY (w/o dashes)" << endl
		<< "(6) If project is incomplete: Input 0" << endl
		<< "    If project is complete: Input 1" << endl
		<< "    If project is abandoned: Input 2" << endl
		<< "Input 'M' to repeat this meessage" << endl;

	cout << endl;

}