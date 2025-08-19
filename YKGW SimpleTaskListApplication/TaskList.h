#pragma once
#include "Task.h"

enum class SORTING_FIELD
{
	ID,
	DUE_DATE,
	COMPLETED
};

enum class SORTING_ORDER
{
	ASC,
	DESC
};

// TaskList will hold the container of Tasks.

class TaskList
{
public:
	std::vector<Task> taskListVector;
	void addTask(Task newTask);
	void markTaskAsCompleted(int taskID);
	void deleteTask(int taskID);
	void sortTasks(SORTING_FIELD columnToSort, SORTING_ORDER ordertToSort);
	int getTaskListCount();
};
