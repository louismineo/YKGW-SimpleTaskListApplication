#include "TaskManager.h"
#include "Task.h"
#include "Error.h"
#include "Console.h"

#include <iostream>
#include <sstream>

std::vector<std::string> TaskManager::tokenize(const std::string& input)
{
    std::istringstream iss(input);
    std::vector<std::string> tokens;
    std::string word;

    while (iss >> word) 
        tokens.push_back(word);

	return tokens;
}

TaskManager::TaskManager() : commandHandler(this->taskList, exitMainLoopBool, taskIDCounter){
}

void TaskManager::mainLoop()
{
    int taskCount = taskList.getTaskListCount();
    int completedTasksCount = 0;


    // every while loop iteration is 1 input;
    while(exitMainLoopBool == false)
    {
	    try
        {
            taskPrinter.printTaskListTable(taskList, taskCount, completedTasksCount);
            if(taskCount > 0)
                taskPrinter.printSummaryCountTable(taskCount, completedTasksCount);
            taskPrinter.printMenu();

            std::cout << "\n>"; // clear the line for std::getline
            std::string inputLine;
            std::getline(std::cin, inputLine);

            std::vector<std::string> inputTokens = tokenize(inputLine);

            if (!inputTokens.empty()) {
                commandHandler.handleCommand(inputTokens);
            }

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

    std::cout << "Exiting SimpleTaskListApplication... Goodbye!\n";
}
