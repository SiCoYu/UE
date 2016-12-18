#include "MyProject.h"
#include "MCondition.h"
#include "MMutex.h"
#include "MEvent.h"
#include "MLock.h"

MCondition::MCondition(std::string name)
{
    mMutex = new MMutex();
    mEvent = new MEvent();
    mCanEnterWait = true;      // 允许进入等待状态
}

MCondition::~MCondition()
{
	delete mMutex;
	delete mEvent;
}

bool MCondition::getCanEnterWait()
{
    return mCanEnterWait;
}

void MCondition::wait()
{
	mMutex->Lock();
    if (mCanEnterWait)
    {
		mMutex->Unlock();   // 这个地方需要释放锁，否则 notifyAll 进不来
        mEvent->Wait();
        mEvent->Reset();      // 重置信号
    }
    else
    {
        mCanEnterWait = true;
		mMutex->Unlock();
    }
}

void MCondition::notifyAll()
{
	MLock mlock(mMutex);

    if (mCanEnterWait) // 如果 mCanEnterWait == false，必然不能进入等待
    {
        mCanEnterWait = false;
        mEvent->Set();        // 唤醒线程
    }
}