#pragma once
#include <string>

#include "TaskList.h"

class CommandHandler
{
private:
	TaskList& m_taskList;			// ref from TaskManager
	bool& m_exitRequested;		// ref from TaskManager
	int& m_currentTaskID;		// ref from TaskManager

	SORTING_FIELD convertToSortingFieldEnum(std::string field);
	SORTING_ORDER convertToSortingOrderEnum(std::string field);

	
	void addCommand(std::string taskName, std::string dueDateinDDMMYYY);
	void completeCommand(int taskID);
	void deleteCommand(int taskID);
	void sortCommand(std::string columnToSort, std::string ascOrDesc);
	void exitCommand();
public:
	CommandHandler(TaskList& tasks, bool& exitFlag, int& currentTaskID);
	void handleCommand(std::vector<std::string> commandLineParams);
};
