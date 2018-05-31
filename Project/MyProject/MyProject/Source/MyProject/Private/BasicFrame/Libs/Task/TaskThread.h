#pragma once

#include "MThread.h"
#include <string>
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

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
	virtual uint32 Run(void) override;
	bool notifySelf();
};

MY_END_NAMESPACE