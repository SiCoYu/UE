#pragma once

#include "MList.h"

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