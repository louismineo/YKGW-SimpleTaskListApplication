#include "TaskManager.h"
#include "Task.h"
#include "Error.h"

#include <iostream>
#include <sstream>

#include "Console.h"


SORTING_FIELD TaskManager::convertToSortingFieldEnum(std::string field)
{
    if (field == "ID")
        return SORTING_FIELD::ID;
    else if (field == "DueDate")
        return SORTING_FIELD::DUE_DATE;
    else if (field == "Status")
        return SORTING_FIELD::COMPLETED;
    else
        throw Error::InvalidSortingFieldException();

}

SORTING_ORDER TaskManager::convertToSortingOrderEnum(std::string field)
{
    if (field == "ASC")
        return SORTING_ORDER::ASC;
    else if (field == "DESC")
        return SORTING_ORDER::DESC;
    else
        throw Error::InvalidSortingOrderException();
}

void TaskManager::handleCommand(std::vector<std::string> commandLineParams)
{
    if(commandLineParams[0] == "/add")
    {
        // concatenate the string tokens to form the task name
        std::string concatenatedTaskName = "";
        for (int idx = 1; idx < commandLineParams.size() - 1; ++idx)
            concatenatedTaskName += (commandLineParams[idx] + " ");

        addCommand(concatenatedTaskName, commandLineParams[commandLineParams.size()-1]);
    }
    else if (commandLineParams[0] == "/complete")
    {
        completeCommand(std::stoi(commandLineParams[1]));
    }
    else if (commandLineParams[0] == "/delete")
    {
        deleteCommand(std::stoi(commandLineParams[1]));
    }
    else if (commandLineParams[0] == "/exit")
    {
    	exitCommand();
    }
    else if (commandLineParams[0] == "/sort")
    {
        sortCommand(commandLineParams[1], commandLineParams[2]);
    }
    else
    {
        throw Error::InvalidCommandException();
    }
}

void TaskManager::addCommand(std::string taskName, std::string dueDateinDDMMYYY)
{
    Console::clearConsole();
    Console::setColor(CONSOLE_BRIGHT_BLUE);
    std::cout << "**********************************************" << std::endl;
    std::cout << "Adding Task to the list. (" << taskName << " - " << dueDateinDDMMYYY<<")"<< std::endl;
    std::cout << "**********************************************" << std::endl;
    Console::setColor(CONSOLE_GRAY);


    taskList.addTask(Task{taskIDCounter, taskName , dueDateinDDMMYYY });
	++taskIDCounter;
}

void TaskManager::completeCommand(int taskID)
{
    Console::clearConsole();
    Console::setColor(CONSOLE_BRIGHT_BLUE);
    std::cout << "**********************************************" << std::endl;
    std::cout << "Marking Task as complete. (TaskID: " << taskID << ")" << std::endl;
    std::cout << "**********************************************" << std::endl;
    Console::setColor(CONSOLE_GRAY);

    taskList.markTaskAsCompleted(taskID);
}

void TaskManager::deleteCommand(int taskID)
{
    Console::clearConsole();
    Console::setColor(CONSOLE_BRIGHT_BLUE);
    std::cout << "**********************************************" << std::endl;
    std::cout << "Deleting Task as from List. (TaskID: " << taskID << ")" << std::endl;
    std::cout << "**********************************************" << std::endl;
    Console::setColor(CONSOLE_GRAY);

    taskList.deleteTask(taskID);
}

void TaskManager::sortCommand(std::string columnToSort, std::string ascOrDesc)
{
    Console::clearConsole();
    Console::setColor(CONSOLE_BRIGHT_BLUE);
    std::cout << "**********************************************" << std::endl;
    std::cout << "Sorting Tasks. By (columnToSort: " << columnToSort << " & ascOrDesc: " << ascOrDesc << ")" << std::endl;
    std::cout << "**********************************************" << std::endl;
    Console::setColor(CONSOLE_GRAY);

    taskList.sortTasks(convertToSortingFieldEnum(columnToSort), convertToSortingOrderEnum(ascOrDesc));
}

void TaskManager::exitCommand()
{
    exitMainLoopBool = true;
}

void TaskManager::print()
{
    int taskCount = taskList.getTaskListCount();
    int completedTasksCount = 0;

    std::cout << std::endl;
    taskPrinter.printTaskListTable(taskList,taskCount, completedTasksCount);

	if (taskCount > 0)
    {
        std::cout << std::endl;
        taskPrinter.printSummaryCountTable(taskCount, completedTasksCount);
    }

	std::cout << std::endl;
    taskPrinter.printPrimaryChoices();
}

void TaskManager::mainLoop()
{
    // every while loop iteration is 1 input;
    while(exitMainLoopBool == false)
    {
	    try
        {
		    print();

	    	std::cout << "\n>";
	    	std::string commandLine;
	    	std::getline(std::cin, commandLine);  // reads the line

	    	std::istringstream iss(commandLine);
	    	std::vector<std::string> inputTokens;
	    	std::string word;

	    	while (iss >> word) {  // split by whitespace
	    		inputTokens.push_back(word);
	    	}

	    	handleCommand(inputTokens);
	    }
        catch (const std::runtime_error& e) {
            Console::clearConsole();
            Console::setColor(CONSOLE_RED);
            std::cerr << "[Runtime error] " << e.what() << "\n";
            Console::setColor(CONSOLE_GRAY);
        }
        catch (...) {
            Console::clearConsole();
            Console::setColor(CONSOLE_RED);
            std::cerr << "[Unknown error occurred]\n";
            Console::setColor(CONSOLE_GRAY);
        }
    }

    std::cout << "Exiting SimpleTaskListApplication..... " << std::endl;
    std::cout << "Goodbye" << std::endl;
}
