#include "TaskList.h"
#include "Error.h"

void TaskList::addTask(Task newTask)
{
	taskList.push_back(newTask);
}

void TaskList::markTaskAsCompleted(int taskID)
{
	for(int idx = 0; idx < taskList.size(); ++idx)
	{
		if(taskList[idx].getTaskID() == taskID)
		{
			taskList[idx].markAsCompleted();
			return;
		}
	}

	//if id is invalid or cannot be found in the vector, it will reach this part of the code
	throw Error::InvalidTaskIDException();
}

void TaskList::deleteTask(int taskID)
{
	//find the task and its ID
	for (int idx = 0; idx < taskList.size(); ++idx)
	{
		if (taskList[idx].getTaskID() == taskID)
		{
			taskList.erase(taskList.begin() + idx);
			return;
		}
	}

	//if id is invalid or cannot be found in the vector, it will reach this part of the code
	throw Error::InvalidTaskIDException();
}
