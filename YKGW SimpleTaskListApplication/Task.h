#pragma once
#include <string>
#include <chrono>
#include <regex>
#include "Error.h"

class Task
{
private:
	int taskID; //simple running integer as ID
	std::string m_Name;
	std::chrono::year_month_day m_dueDate;
	bool isCompleted;

	
	std::chrono::year_month_day convertStringDateToYMD(std::string date_param);

public:
	void markAsCompleted();
};
