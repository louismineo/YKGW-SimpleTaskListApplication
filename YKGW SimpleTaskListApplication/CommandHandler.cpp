#include "CommandHandler.h"

#include <iostream>

#include "Console.h"
#include "Error.h"

SORTING_FIELD CommandHandler::convertToSortingFieldEnum(std::string field)
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

SORTING_ORDER CommandHandler::convertToSortingOrderEnum(std::string field)
{
    if (field == "ASC")
        return SORTING_ORDER::ASC;
    else if (field == "DESC")
        return SORTING_ORDER::DESC;
    else
        throw Error::InvalidSortingOrderException();
}

void CommandHandler::addCommand(std::string taskName, std::string dueDateinDDMMYYY)
{
    Console::clearConsole();
    Console::setColor(CONSOLE_BRIGHT_BLUE);
    std::cout << "**********************************************" << std::endl;
    std::cout << "Adding Task to the list. (" << taskName << " - " << dueDateinDDMMYYY << ")" << std::endl;
    std::cout << "**********************************************" << std::endl;
    Console::setColor(CONSOLE_GRAY);


    m_taskList.addTask(Task{ m_currentTaskID, taskName , dueDateinDDMMYYY });
    ++m_currentTaskID;
}

void CommandHandler::completeCommand(int taskID)
{
    Console::clearConsole();
    Console::setColor(CONSOLE_BRIGHT_BLUE);
    std::cout << "**********************************************" << std::endl;
    std::cout << "Marking Task as complete. (TaskID: " << taskID << ")" << std::endl;
    std::cout << "**********************************************" << std::endl;
    Console::setColor(CONSOLE_GRAY);

    m_taskList.markTaskAsCompleted(taskID);
}

void CommandHandler::deleteCommand(int taskID)
{
    Console::clearConsole();
    Console::setColor(CONSOLE_BRIGHT_BLUE);
    std::cout << "**********************************************" << std::endl;
    std::cout << "Deleting Task as from List. (TaskID: " << taskID << ")" << std::endl;
    std::cout << "**********************************************" << std::endl;
    Console::setColor(CONSOLE_GRAY);

    m_taskList.deleteTask(taskID);
}

void CommandHandler::sortCommand(std::string columnToSort, std::string ascOrDesc)
{
    Console::clearConsole();
    Console::setColor(CONSOLE_BRIGHT_BLUE);
    std::cout << "**********************************************" << std::endl;
    std::cout << "Sorting Tasks. By (columnToSort: " << columnToSort << " & ascOrDesc: " << ascOrDesc << ")" << std::endl;
    std::cout << "**********************************************" << std::endl;
    Console::setColor(CONSOLE_GRAY);

    m_taskList.sortTasks(convertToSortingFieldEnum(columnToSort), convertToSortingOrderEnum(ascOrDesc));
}

void CommandHandler::exitCommand()
{
    m_exitRequested = true;
}

CommandHandler::CommandHandler(TaskList& tasks, bool& exitFlag, int& currentTaskID)
	:m_taskList(tasks), m_exitRequested(exitFlag), m_currentTaskID(currentTaskID)
{}

void CommandHandler::handleCommand(std::vector<std::string> commandLineParams)
{
    if (commandLineParams[0] == "/add")
    {
        // concatenate the string tokens to form the task name
        std::string concatenatedTaskName = "";
        for (int idx = 1; idx < commandLineParams.size() - 1; ++idx)
            concatenatedTaskName += (commandLineParams[idx] + " ");

        addCommand(concatenatedTaskName, commandLineParams[commandLineParams.size() - 1]);
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
