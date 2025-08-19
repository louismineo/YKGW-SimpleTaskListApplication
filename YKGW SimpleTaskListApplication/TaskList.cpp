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

void TaskList::sortTasks(SORTING_FIELD columnToSort, SORTING_ORDER ordertToSort)
{
	std::sort(taskListVector.begin(), taskListVector.end(),
		[columnToSort, ordertToSort](Task& a,Task& b) {
			switch (columnToSort) {
			case SORTING_FIELD::ID:
				return (ordertToSort == SORTING_ORDER::ASC)
					? (a.getTaskID() < b.getTaskID())
					: (a.getTaskID() > b.getTaskID());

			case SORTING_FIELD::DUE_DATE:
				return (ordertToSort == SORTING_ORDER::ASC)
					? (a.getDueDateInYMD() < b.getDueDateInYMD())
					: (a.getDueDateInYMD() > b.getDueDateInYMD());

			case SORTING_FIELD::COMPLETED:
				return (ordertToSort == SORTING_ORDER::ASC)
					? (a.getIsCompletedBool() < b.getIsCompletedBool())
					: (a.getIsCompletedBool() > b.getIsCompletedBool());
			}
			return false; // fallback, shouldn't hit
		}
	);
}

int TaskList::getTaskListCount()
{
	return static_cast<int>(taskListVector.size());
}
