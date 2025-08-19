#pragma once
#include "CommandHandler.h"
#include"TaskList.h"
#include "TaskPrinter.h"



//Task Manager will handle the public functions to print the tasks in a list and handle the different commands (add, view, complete, delete) 

class TaskManager
{
private:
	bool exitMainLoopBool = false;
	int taskIDCounter = 1;

	TaskList taskList;
	TaskPrinter taskPrinter;
	CommandHandler commandHandler;

	

	// input handling
	
	//void print();

	std::vector<std::string> tokenize(const std::string& input);

public:
	TaskManager();
	void mainLoop();
};
