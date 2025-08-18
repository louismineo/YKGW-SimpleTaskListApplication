#include "TaskList.h"
#include "Error.h"

void TaskList::addTask(Task newTask)
{
	taskListVector.push_back(newTask);
}

void TaskList::markTaskAsCompleted(int taskID)
{
	for(int idx = 0; idx < taskListVector.size(); ++idx)
	{
		if(taskListVector[idx].getTaskID() == taskID)
		{
			taskListVector[idx].markAsCompleted();
			return;
		}
	}

	//if id is invalid or cannot be found in the vector, it will reach this part of the code
	throw Error::InvalidTaskIDException();
}

void TaskList::deleteTask(int taskID)
{
	//find the task and its ID
	for (int idx = 0; idx < taskListVector.size(); ++idx)
	{
		if (taskListVector[idx].getTaskID() == taskID)
		{
			taskListVector.erase(taskListVector.begin() + idx);
			return;
		}
	}

	//if id is invalid or cannot be found in the vector, it will reach this part of the code
	throw Error::InvalidTaskIDException();
}

int TaskList::getTaskListCount()
{
	return static_cast<int>(taskListVector.size());
}
