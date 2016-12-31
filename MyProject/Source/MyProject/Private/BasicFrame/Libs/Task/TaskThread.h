#pragma once

#include "MThread.h"
#include <string>

class TaskQueue;
class MCondition;
class ITask;

class TaskThread : public MThread
{
	typedef class MThread Super;

protected:
    TaskQueue* mTaskQueue;
    MCondition* mCondition;
    ITask* mCurTask;

public:
	TaskThread(std::string name, TaskQueue* taskQueue);

public:
    /**
     *brief 线程回调函数
     */
	virtual void threadHandle() override;
	bool notifySelf();
};