#include "ProjectType.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

void listMenu();


int main() {

	vector<projectType> projectDatabase; //Database that holds all project objects

	//Indexing variable(s)
	int c;
	
	//Menu Variables
	char aMenu;
	char bMenu;
	char menuIndex;
	
	//File IO Variables
	ifstream readProject;
	ofstream writeProject;

	//Temporary Project File
	projectType *tempProject;

	make_heap(projectDatabase.begin(), projectDatabase.end(), projectType::getPriority); //Converts the project database into a max-heap
	
	readProject.open("Projects.txt");
	c = 0;
	while (!readProject.eof() && c < projectDatabase.size()) {
		tempProject = new projectType;
		readProject >> *tempProject;
		projectDatabase.push_back(*tempProject);
		push_heap(projectDatabase.begin(), projectDatabase.end());
	}
	readProject.close();









	return 0;
}

void listMenu() {

	cout << "List Menu" << endl
		<< "P  - List all projects" << endl
		<< "iP - Manage project 'i'" << endl
		<< "i+ - Increase project i's priority" << endl
		<< "M  - Display this menu again" << endl
		<< "Q  - Exit menu" << endl;

}

void projectMenu() {

	cout << "Project Menu" << endl
		<< "P  - Display project information" << endl
		<< "T  - Enter tool menu" << endl
		<< "N  - Edit Name " << endl
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