#pragma once
#include "Task.h"


// TaskList will hold the container of Tasks.

class TaskList
{
public:
	std::vector<Task> taskListVector;
	void addTask(Task newTask);
	void markTaskAsCompleted(int taskID);
	void deleteTask(int taskID);
	int getTaskListCount();
};
