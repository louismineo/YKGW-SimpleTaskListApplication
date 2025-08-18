#pragma once
#include "Task.h"


// TaskList will hold the container of Tasks.

class TaskList
{
public:
	std::vector<Task> taskList;
	void addTask(Task newTask);
	void markTaskAsCompleted(int taskID);
	void deleteTask(int taskID);
};
