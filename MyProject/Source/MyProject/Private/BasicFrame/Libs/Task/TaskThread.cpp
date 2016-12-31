#include "MyProject.h"
#include "TaskThread.h"

TaskThread::TaskThread(std::string name, TaskQueue taskQueue)
    : base(null, null)
{
    mTaskQueue = taskQueue;
    mCondition = new MCondition(name);
}

/**
 *brief 线程回调函数
 */
void TaskThread::threadHandle()
{
    while (!mIsExitFlag)
    {
        mCurTask = mTaskQueue.pop();
        if(mCurTask != default(ITask))
        {
            mCurTask.runTask();
        }
        else
        {
            mCondition.wait();
        }
    }
}

bool TaskThread::notifySelf()
{
    if(mCondition.canEnterWait)
    {
        mCondition.notifyAll();
        return true;
    }

    return false;
}