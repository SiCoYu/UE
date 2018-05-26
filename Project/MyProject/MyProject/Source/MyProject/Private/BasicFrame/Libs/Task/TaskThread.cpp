#include "MyProject.h"
#include "TaskThread.h"
#include "MCondition.h"
#include "TaskQueue.h"

TaskThread::TaskThread(std::string name, TaskQueue* taskQueue)
    : Super(name)
{
    mTaskQueue = taskQueue;
    mCondition = MY_NEW MCondition(name);
}

/**
 *brief 线程回调函数
 */
uint32 TaskThread::Run(void)
{
    while (!mIsExitFlag)
    {
        mCurTask = mTaskQueue->pop();
        if(mCurTask != nullptr)
        {
            mCurTask->runTask();
        }
        else
        {
            mCondition->wait();
        }
    }

	return 0;
}

bool TaskThread::notifySelf()
{
    if(mCondition->getCanEnterWait())
    {
        mCondition->notifyAll();
        return true;
    }

    return false;
}