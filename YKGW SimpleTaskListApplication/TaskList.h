#pragma once
#include "Task.h"


// TaskList will hold the container of Tasks.

class TaskList
{
private:
	std::vector<Task> taskList;

public:
	void addTask(Task newTask);
	void markTaskAsCompleted(int taskID);
	void deleteTask(int taskID);
};
