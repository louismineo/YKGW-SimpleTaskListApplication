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
		return Error("Invalid Task ID entered. Please enter a valid Task ID from the list below");
	}

	static Error InvalidCommandException()
	{
		return Error("Invalid Command entered. Please enter a valid command listed");
	}

	static Error InvalidSortingFieldException()
	{
		return Error("Invalid Sorting Field entered. Please enter a valid field to sort by, from the command");
	}

	static Error InvalidSortingOrderException()
	{
		return Error("Invalid Sorting Order entered. Please enter a valid order to sort by, from the command");
	}
};
