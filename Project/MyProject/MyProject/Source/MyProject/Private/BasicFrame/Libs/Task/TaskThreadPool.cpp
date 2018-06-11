#include "MyProject.h"
#include "TaskThreadPool.h"
#include "UtilStr.h"
#include "TaskThread.h"
#include "TaskQueue.h"

MY_BEGIN_NAMESPACE(MyNS)

TaskThreadPool::TaskThreadPool()
{

}

void TaskThreadPool::initThreadPool(int numThread, TaskQueue* taskQueue)
{
    //mList = new MList<TaskThread>(numThread);
    int index = 0;

    for(index = 0; index < numThread; ++index)
    {
		TaskThread* ptr = MY_NEW TaskThread(UtilStr::Format("TaskThread%d", index), taskQueue);
        this->mList.add(ptr);

		this->mList[index]->start();
    }
}

void TaskThreadPool::notifyIdleThread()
{
    for(auto item : this->mList.getList())
    {
        if(item->notifySelf())       // 如果唤醒某个线程就退出，如果一个都没有唤醒，说明当前线程都比较忙，需要等待
        {
            break;
        }
    }
}

MY_END_NAMESPACE