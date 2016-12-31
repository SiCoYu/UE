#include "MyProject.h"
#include "TaskThreadPool.h"
#include "UtilStr.h"

TaskThreadPool::TaskThreadPool()
{

}

void TaskThreadPool::initThreadPool(int numThread, TaskQueue* taskQueue)
{
    mList = new MList<TaskThread>(numThread);
    int idx = 0;
    for(idx = 0; idx < numThread; ++idx)
    {
        mList.Add(new TaskThread(UtilStr::Format("TaskThread%d", idx), taskQueue));
        mList[idx]->start();
    }
}

void TaskThreadPool::notifyIdleThread()
{
    foreach(var item : mList)
    {
        if(item->notifySelf())       // 如果唤醒某个线程就退出，如果一个都没有唤醒，说明当前线程都比较忙，需要等待
        {
            break;
        }
    }
}