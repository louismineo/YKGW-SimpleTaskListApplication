#include "TaskPrinter.h"
#include "Console.h"

#include <iomanip>
#include <iostream>


std::string TaskPrinter::centerText(const std::string& text, int width)
{
    if (text.size() >= static_cast<size_t>(width))
        return text.substr(0, width); // this will truncate if longer than width

    int leftPadding = (width - text.size()) / 2;
    int rightPadding = width - text.size() - leftPadding;

    return std::string(leftPadding, ' ') + text + std::string(rightPadding, ' ');
}

std::vector<std::string> TaskPrinter::wrapTextWithHyphen(std::string text, int width)
{
    std::vector<std::string> lines;

    int start = 0;

    while (start < text.length())
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

void TaskPrinter::printTaskListTable(const TaskList& tasklist, int taskCount, int& completedTasksCount)
{
    int completedTasksCounter = 0;

    std::cout << "TASKS" << std::endl;
    // opening headers
    // Header
    std::cout << "+" << std::string(idWidth, '-')
        << "+" << std::string(nameWidth, '-')
        << "+" << std::string(dateWidth, '-')
        << "+" << std::string(statusWidth, '-')
        << "+"
        << std::endl;

    std::cout << "|" << std::left << std::setw(idWidth) << "ID"
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

        for (auto task : tasklist.taskListVector)
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
                std::cout << std::setw(statusWidth) << (lineNumber == 0 ? (taskCompleted ? "DONE" : "X") : "");
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

    completedTasksCount = completedTasksCounter;
}

void TaskPrinter::printSummaryCountTable(int taskCount, int completedTasksCount)
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

void TaskPrinter::printPrimaryChoices()
{
    std::cout << "What would you like to do today?" << std::endl;
    std::cout << "/add      <Task Name> <Due date in DD/MM/YYYY format>     --- Add a new task" << std::endl;
    std::cout << "/complete <Task ID>                                       --- Mark a task as completed" << std::endl;
    std::cout << "/delete   <Task ID>                                       --- Add a new task" << std::endl;
    std::cout << "/sort     <ID or DueDate or Status> <ASC or DESC>         --- Sort Task Table in various ways" << std::endl;
    std::cout << "/exit                                                     --- Exit Application" << std::endl;
}