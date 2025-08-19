#pragma once
#include"TaskList.h"


//Task Manager will handle the public functions to print the tasks in a list and handle the different commands (add, view, complete, delete) 

class TaskManager
{
private:
	int taskIDCounter = 1;
	TaskList tasklist;

	// printing config
	int idWidth = 3;
	int nameWidth = 20;
	int dateWidth = 11;
	int statusWidth = 7;
	void printTaskListTable(int taskCount, int& completedTasksCount);
	void printSummaryCountTable(int taskCount, int completedTasksCount);
	void printPrimaryChoices();

	// helper functions
	std::string centerText(const std::string& text, int width);
	std::vector<std::string>wrapTextWithHyphen(std::string text, int width);

	bool exitMainLoopBool = false;

	// input handling
	void handleCommand(std::vector<std::string> commandLineParams);
	void addCommand(std::string taskName, std::string dueDateinDDMMYYY);
	void completeCommand(int taskID);
	void deleteCommand(int taskID);
	void exitCommand();
	void print();

public:
	void mainLoop();
};
