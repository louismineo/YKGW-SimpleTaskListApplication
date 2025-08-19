#include "TaskManager.h"
#include "Task.h"
#include "Console.h"
#include "Error.h"

#include <iostream>
#include <sstream>




void TaskManager::printTaskListTable(int taskCount, int& completedTasksCount)
{
    std::cout << "TASKS" << std::endl;
	// opening headers
    // Header
    std::cout << "+" << std::string(idWidth, '-')
        << "+" << std::string(nameWidth, '-')
        << "+" << std::string(dateWidth, '-')
        << "+" << std::string(statusWidth, '-')
		<< "+"
        << std::endl;

    std::cout << "|"<< std::left << std::setw(idWidth) << "ID"
        << "|" << std::left << std::setw(nameWidth) << " Task Name"
        << "|" << std::left << std::setw(dateWidth) << "Due Date"
        << "|" << std::left << std::setw(statusWidth) << "Status"
        << "|"
        << std::endl;

    std::cout << "+" << std::string(idWidth, '-')
        << "+" << std::string(nameWidth, '-')
        << "+" << std::string(dateWidth, '-')
        << "+" << std::string(statusWidth, '-')
        << "+"
		<< std::endl;



	if (taskCount < 1)
	{
        std::string msg = "No Tasks Available";

        Console::setColor(CONSOLE_GRAY);
        std::cout << "|";
        Console::setColor(CONSOLE_YELLOW);
        std::cout << centerText(msg, idWidth + nameWidth + dateWidth + statusWidth + 3);
        Console::setColor(CONSOLE_GRAY);
        std::cout << "|";
        std::cout << std::endl;

	}
	else
	{
        std::cout << std::right; //reset to the right

        for(auto task: tasklist.taskListVector)
        {
            bool taskCompleted = task.getIsCompletedBool();

        	// increment count for the summary table to use
            if (taskCompleted)++completedTasksCount;

            std::vector<std::string> nameLines = wrapTextWithHyphen(task.getTaskName(), nameWidth);

            // determine the number of lines needed for this row
            int rowLines = nameLines.size();

            for (int lineNumber = 0; lineNumber < rowLines; ++lineNumber)
            {
                // print ID col
                std::cout << "|";
                Console::setColor(taskCompleted ? CONSOLE_BRIGHT_GREEN : CONSOLE_BRIGHT_RED);
                std::cout << std::setw(idWidth) << (lineNumber == 0 ? std::to_string(task.getTaskID()) : "");
                Console::setColor(CONSOLE_GRAY);

                // print name col
                std::cout << "|";
                Console::setColor(taskCompleted ? CONSOLE_BRIGHT_GREEN : CONSOLE_BRIGHT_RED);
                std::cout << std::left << std::setw(nameWidth) << (lineNumber < rowLines ? nameLines[lineNumber] : "");
                Console::setColor(CONSOLE_GRAY);

                // print due date col
                std::cout << "|";
                Console::setColor(taskCompleted ? CONSOLE_BRIGHT_GREEN : CONSOLE_BRIGHT_RED);
                std::cout << std::right << std::setw(dateWidth) << (lineNumber == 0 ? task.getDueDateInString() : "");
                Console::setColor(CONSOLE_GRAY);

                // print status col
                std::cout << "|";
                Console::setColor(taskCompleted ? CONSOLE_BRIGHT_GREEN : CONSOLE_BRIGHT_RED);
                std::cout << std::setw(statusWidth) << (lineNumber == 0 ? (taskCompleted ? "DONE" : "X"): "");
                Console::setColor(CONSOLE_GRAY);

                // close the row
                std::cout << "|" << std::endl;
            }
        }
	}


	//footer
    std::cout << "+" << std::string(idWidth, '-')
        << "+" << std::string(nameWidth, '-')
        << "+" << std::string(dateWidth, '-')
        << "+" << std::string(statusWidth, '-')
        << "+\n";

}

void TaskManager::printSummaryCountTable(int taskCount, int completedTasksCount)
{
    //summary table
    int midPointCount = (idWidth + nameWidth + dateWidth + statusWidth + 3) / 2;
    std::cout << "SUMMARY TABLE" << std::endl;

	//header
    std::cout << "+"
        << std::string(midPointCount, '-')
        << "+"
        << std::string(midPointCount, '-')
        << "+\n";

	//total count
    std::cout << "|"
        << std::left << std::setw(midPointCount) << "Total Tasks"
        << "|"
        << std::right << std::setw(midPointCount) << taskCount
        << "|\n";
    std::cout << "+"
        << std::string(midPointCount, '-')
        << "+"
        << std::string(midPointCount, '-')
        << "+\n";

    //completed count
    std::cout << "|";
    Console::setColor(CONSOLE_BRIGHT_GREEN);  // green color
    std::cout << std::left << std::setw(midPointCount) << "COMPLETED TASKS";
    Console::setColor(CONSOLE_GRAY);          // reset for colour for border/other text
    std::cout << "|";
    Console::setColor(CONSOLE_BRIGHT_GREEN);
    std::cout << std::right << std::setw(midPointCount) << completedTasksCount;
    Console::setColor(CONSOLE_GRAY);
    std::cout << "|\n";

    //pending tasks count
    std::cout << "|";
    Console::setColor(CONSOLE_BRIGHT_RED);    // red color
    std::cout << std::left << std::setw(midPointCount) << "PENDING TASKS";
    Console::setColor(CONSOLE_GRAY);          // reset for colour for border/other text
    std::cout << "|";
    Console::setColor(CONSOLE_BRIGHT_RED);
    std::cout << std::right << std::setw(midPointCount) << taskCount - completedTasksCount;
    Console::setColor(CONSOLE_GRAY);
    std::cout << "|\n";

    std::cout << "+"
        << std::string(midPointCount, '-')
        << "+"
        << std::string(midPointCount, '-')
        << "+\n";

}

void TaskManager::printPrimaryChoices()
{
    std::cout << "What would you like to do today?" << std::endl;
    std::cout << "/add      <Task Name> <Due date in DD/MM/YYYY format>     --- Add a new task" << std::endl;
    std::cout << "/complete <Task ID>                                       --- Mark a task as completed" << std::endl;
    std::cout << "/delete   <Task ID>                                       --- Add a new task" << std::endl;
    std::cout << "/sort     <ID or DueDate or Status> <ASC or DESC>         --- Sort Task Table in various ways" << std::endl;
    std::cout << "/exit                                                     --- Exit Application" << std::endl;
}

std::string TaskManager::centerText(const std::string& text, int width)
{
    if (text.size() >= static_cast<size_t>(width))
        return text.substr(0, width); // this will truncate if longer than width

    int leftPadding = (width - text.size()) / 2;
    int rightPadding = width - text.size() - leftPadding;

    return std::string(leftPadding, ' ') + text + std::string(rightPadding, ' ');
}

std::vector<std::string> TaskManager::wrapTextWithHyphen(std::string text, int width)
{
    std::vector<std::string> lines;

    int start = 0;

    while (start< text.length())
    {
        int lengthRemaining = width;
        if (start + lengthRemaining < text.size()) {
            // check if the last char is mid-word
            if (!isspace(text[start + lengthRemaining - 1]) && !isspace(text[start + lengthRemaining])) {
                lengthRemaining--;  // leave space for hyphen
                lines.push_back(text.substr(start, lengthRemaining) + "-");
                start += lengthRemaining;
                continue;
            }
        }
        lines.push_back(text.substr(start, lengthRemaining));
        start += lengthRemaining;
    }

    return lines;
}

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
	    // todo:
        // throw invalid input command exception
    }
}

void TaskManager::addCommand(std::string taskName, std::string dueDateinDDMMYYY)
{
    tasklist.addTask(Task{taskIDCounter, taskName , dueDateinDDMMYYY });
	++taskIDCounter;
}

void TaskManager::completeCommand(int taskID)
{
    tasklist.markTaskAsCompleted(taskID);
}

void TaskManager::deleteCommand(int taskID)
{
    tasklist.deleteTask(taskID);
}

void TaskManager::sortCommand(std::string columnToSort, std::string ascOrDesc)
{
    tasklist.sortTasks(convertToSortingFieldEnum(columnToSort), convertToSortingOrderEnum(ascOrDesc));
}

void TaskManager::exitCommand()
{
    exitMainLoopBool = true;
}

void TaskManager::print()
{
    int taskCount = tasklist.getTaskListCount();
    int completedTasksCount = 0;

    std::cout << std::endl;
    printTaskListTable(taskCount, completedTasksCount);

	if (taskCount > 0)
    {
        std::cout << std::endl;
        printSummaryCountTable(taskCount, completedTasksCount);
    }

	std::cout << std::endl;
    printPrimaryChoices();
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
            std::cerr << "[Runtime error] " << e.what() << "\n";
        }
        catch (...) {
            std::cerr << "[Unknown error occurred]\n";
        }
    }

    std::cout << "Exiting SimpleTaskListApplication..... " << std::endl;
    std::cout << "Goodbye" << std::endl;
}
