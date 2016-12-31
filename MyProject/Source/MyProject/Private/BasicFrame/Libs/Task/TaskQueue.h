#pragma once

#include "LockQueue.h"
#include "ITask.h"
#include <string>

class TaskThreadPool;

class TaskQueue : public LockQueue<ITask*>
{
	typedef class LockQueue<ITask*> Super;

public:
    TaskThreadPool* mTaskThreadPool;

public:
	TaskQueue(std::string name);

public:
	void push(ITask* item);
};