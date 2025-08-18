#pragma once
#include <stdexcept>


class Error : public std::runtime_error
{
public:
	//CTOR
	explicit Error(const std::string msg) : runtime_error(msg){}

	static Error DateFormatException()
	{
		return Error("Invalid due date. Please enter the Task's due date in DD/MM/YYYY format");
	}

	static Error InvalidTaskIDException()
	{
		return Error("Invalid Task ID entered. Please enter a valid Task ID from the list above");
	}
};
