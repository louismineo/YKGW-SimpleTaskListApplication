#pragma once
#include"TaskList.h"

//Task Manager will handle the public functions to print the tasks in a list and handle the different commands (add, view, complete, delete) 

class TaskManager
{
private:
	int taskIDCounter = 1;
	TaskList tasklist;

	//printing config
	int idWidth = 3;
	int nameWidth = 20;
	int dateWidth = 11;
	int statusWidth = 7;
	void printTaskListTable(int taskCount, int& completedTasksCount);
	void printSummaryCountTable(int taskCount, int completedTasksCount);
	void printPrimaryChoices();

	//helper functions
	std::string centerText(const std::string& text, int width);

public:
	void print();
};
