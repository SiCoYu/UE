#include "MyProject.h"
#include "MCondition.h"
#include "MMutex.h"
#include "MEvent.h"
#include "MLock.h"

#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"
#include "MyMemoryAlloc.h"
#include "SafePointer.h"

MY_BEGIN_NAMESPACE(MyNS)

MCondition::MCondition(std::string name)
{
    this->mMutex = MY_NEW MMutex();
	this->mEvent = MY_NEW MEvent();
	this->mCanEnterWait = true;      // 允许进入等待状态
}

MCondition::~MCondition()
{
	//this->dispose();
}

void MCondition::init()
{

}

void MCondition::dispose()
{
	MY_SAFE_DISPOSE(this->mMutex);
	MY_SAFE_DISPOSE(this->mEvent);
}

bool MCondition::getCanEnterWait()
{
    return this->mCanEnterWait;
}

void MCondition::wait()
{
	this->mMutex->Lock();

    if (this->mCanEnterWait)
    {
		this->mMutex->Unlock();   // 这个地方需要释放锁，否则 notifyAll 进不来
		this->mEvent->Wait();
		this->mEvent->Reset();      // 重置信号
    }
    else
    {
		this->mCanEnterWait = true;
		this->mMutex->Unlock();
    }
}

void MCondition::notifyAll()
{
	MLock mlock(this->mMutex);

    if (this->mCanEnterWait) // 如果 mCanEnterWait == false，必然不能进入等待
    {
		this->mCanEnterWait = false;
		this->mEvent->Set();        // 唤醒线程
    }
}

MY_END_NAMESPACE