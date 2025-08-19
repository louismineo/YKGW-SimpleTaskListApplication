#pragma once
#include"TaskList.h"
#include "TaskPrinter.h"



//Task Manager will handle the public functions to print the tasks in a list and handle the different commands (add, view, complete, delete) 

class TaskManager
{
private:
	int taskIDCounter = 1;
	TaskList taskList;
	TaskPrinter taskPrinter;

	SORTING_FIELD convertToSortingFieldEnum(std::string field);
	SORTING_ORDER convertToSortingOrderEnum(std::string field);

	bool exitMainLoopBool = false;

	// input handling
	void handleCommand(std::vector<std::string> commandLineParams);
	void addCommand(std::string taskName, std::string dueDateinDDMMYYY);
	void completeCommand(int taskID);
	void deleteCommand(int taskID);
	void sortCommand(std::string columnToSort, std::string ascOrDesc);
	void exitCommand();
	void print();

public:
	void mainLoop();
};
