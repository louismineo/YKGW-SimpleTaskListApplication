#include "Task.h"

void Task::markAsCompleted()
{
	isCompleted = true;
}


std::chrono::year_month_day Task::convertStringDateToYMD(std::string date_param)
{
	//check if it is DD/MM/YYYY
	std::regex const date_pattern(R"(^(0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[0-2])/\d{4}$)");

	if (std::regex_match(date_param, date_pattern))
	{
		// split the string from "dd/mm/yyyy" into dd mm yyyy
		int intDay = std::stoi(date_param.substr(0, 2));
		int intMonth = std::stoi(date_param.substr(3, 2));
		int intYear = std::stoi(date_param.substr(6, 4));

		// convert them into the chrono types
		std::chrono::year y{ intYear };
		std::chrono::month m{ static_cast<unsigned> (intMonth) };
		std::chrono::day d{ static_cast<unsigned>(intDay) };

		std::chrono::year_month_day ymd{ y / m / d };
		return ymd;
	}
	else
	{
		// handle wrong date format
		throw Error::DateFormatException();
	}
}

int Task::getTaskID()
{
	return taskID;
}
