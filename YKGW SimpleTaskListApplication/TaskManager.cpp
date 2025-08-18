#include "TaskManager.h"

#include <iostream>

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

        std::cout << "|"
			<< centerText(msg, idWidth + nameWidth + dateWidth + statusWidth +3)
			<< "|"
			<< std::endl;

	}
	else
	{
        std::cout << "|" << std::right << std::setw(idWidth + 1)
            << "|" << std::right << std::setw(nameWidth + 1)
            << "|" << std::right << std::setw(dateWidth + 1)
            << "|" << std::right << std::setw(statusWidth + 1)
            << "|"
            << std::endl;
		//todo:
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
    std::cout << "|"
        << std::left << std::setw(midPointCount) << "COMPLETED TASKS"
        << "|"
        << std::right << std::setw(midPointCount) << completedTasksCount
        << "|\n";

    //pending tasks count
    std::cout << "|"
        << std::left << std::setw(midPointCount) << "PENDING TASKS"
        << "|"
        << std::right << std::setw(midPointCount) << taskCount - completedTasksCount
        << "|\n";
    std::cout << "+"
        << std::string(midPointCount, '-')
        << "+"
        << std::string(midPointCount, '-')
        << "+\n";

}

void TaskManager::printPrimaryChoices()
{
    std::cout << "What would you like to do today?" << std::endl;
    std::cout << "/add      --- Add a new task" << std::endl;
    std::cout << "/complete --- Mark a task as completed" << std::endl;
    std::cout << "/delete   --- Add a new task" << std::endl;
}

std::string TaskManager::centerText(const std::string& text, int width)
{
    if (text.size() >= static_cast<size_t>(width))
        return text.substr(0, width); // this will truncate if longer than width

    int leftPadding = (width - text.size()) / 2;
    int rightPadding = width - text.size() - leftPadding;

    return std::string(leftPadding, ' ') + text + std::string(rightPadding, ' ');
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
