#pragma once
#include <string>
#include <chrono>
#include <regex>

class Task
{
private:
	int taskID; //simple running integer as ID
	std::string m_Name;
	std::chrono::year_month_day m_dueDate;
	bool isCompleted = false;

	
	std::chrono::year_month_day convertStringDateToYMD(std::string date_param);

public:
	Task(int newTaskID, std::string newTaskName, std::string newTaskDueDateString);
	void markAsCompleted();
	int getTaskID();
};
