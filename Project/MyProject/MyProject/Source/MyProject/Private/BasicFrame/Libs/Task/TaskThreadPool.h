#pragma once

#include "MList.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class TaskThread;
class TaskQueue;

class TaskThreadPool
{
protected:
	MList<TaskThread*> mList;

public:
	TaskThreadPool();

public:
	void initThreadPool(int numThread, TaskQueue* taskQueue);
	void notifyIdleThread();
};

MY_END_NAMESPACE