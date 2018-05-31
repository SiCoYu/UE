#include "MyProject.h"
#include "TimerMgr.h"
#include "UtilContainers.h"
#include "TimerItemBase.h"

MY_BEGIN_NAMESPACE(MyNS)

TimerMgr::TimerMgr()
{

}

TimerMgr::~TimerMgr()
{

}

void TimerMgr::init()
{
	Super::init();
}

void TimerMgr::dispose()
{
	Super::dispose();
}

void TimerMgr::addObject(IDelayHandleItem* delayObject, float priority)
{
	// 检查当前是否已经在队列中
	TimerItemBase* timerItemBase = (TimerItemBase*)delayObject;

	if (UtilVector::IndexOf(mTimerList.getList(), timerItemBase) == -1)
	{
		if (this->isInDepth())
		{
			DelayHandleMgrBase::addObject(delayObject, priority);
		}
		else
		{
			this->mTimerList.add((TimerItemBase*)delayObject);
		}
	}
}

void TimerMgr::delObject(IDelayHandleItem* delayObject)
{
	// 检查当前是否在队列中
	TimerItemBase* timerItemBase = (TimerItemBase*)delayObject;

	if (UtilVector::IndexOf(this->mTimerList.getList(), timerItemBase) != -1)
	{
		((TimerItemBase*)delayObject)->mIsDisposed = true;
		if (isInDepth())
		{
			DelayHandleMgrBase::delObject(delayObject);
		}
		else
		{
			for(TimerItemBase* item : this->mTimerList.getList())
			{
				if (item == delayObject)
				{
					UtilVector::Remove(this->mTimerList.getList(), item);
					break;
				}
			}
		}
	}
}

void TimerMgr::Advance(float delta)
{
	this->incDepth();

	for(TimerItemBase* timerItem : this->mTimerList.getList())
	{
		if (!timerItem->isClientDispose())
		{
			timerItem->OnTimer(delta);
		}

		if (timerItem->mIsDisposed)        // 如果已经结束
		{
			delObject(timerItem);
		}
	}

	this->decDepth();
}

MY_END_NAMESPACE