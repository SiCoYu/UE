#pragma once

#include "LockQueue.h"
#include "ITask.h"
#include <string>
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

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

MY_END_NAMESPACE