#pragma once

#include "MLockQueue.h"
#include "ITask.h"
#include <string>
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class TaskThreadPool;

class TaskQueue : public MLockQueue<ITask*>
{
	typedef class MLockQueue<ITask*> Super;

public:
    TaskThreadPool* mTaskThreadPool;

public:
	TaskQueue(std::string name);

public:
	void push(ITask* item);
};

MY_END_NAMESPACE