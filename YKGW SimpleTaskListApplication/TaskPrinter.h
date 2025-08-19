#pragma once
#include "TaskList.h"
#include <string>
#include <vector>


class TaskPrinter
{
private:
	// printing config
	int idWidth = 3;
	int nameWidth = 20;
	int dateWidth = 11;
	int statusWidth = 7;

	// helper functions
	std::string centerText(const std::string& text, int width);
	std::vector<std::string>wrapTextWithHyphen(std::string text, int width);

public:
	void printTaskListTable(TaskList& tasklist, int& taskCount, int& completedTasksCount);
	void printSummaryCountTable(int taskCount, int completedTasksCount);
	void printMenu();
};
