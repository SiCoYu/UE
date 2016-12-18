#include "MyProject.h"
#include "TimerMgr.h"
#include "UtilContainers.h"
#include "TimerItemBase.h"

TimerMgr::TimerMgr()
{

}

void TimerMgr::addObject(IDelayHandleItem* delayObject, float priority)
{
	// 检查当前是否已经在队列中
	TimerItemBase* timerItemBase = (TimerItemBase*)delayObject;
	if (UtilVector::IndexOf(mTimerList.getList(), timerItemBase) == -1)
	{
		if (bInDepth())
		{
			DelayHandleMgrBase::addObject(delayObject, priority);
		}
		else
		{
			mTimerList.Add((TimerItemBase*)delayObject);
		}
	}
}

void TimerMgr::delObject(IDelayHandleItem* delayObject)
{
	// 检查当前是否在队列中
	TimerItemBase* timerItemBase = (TimerItemBase*)delayObject;
	if (UtilVector::IndexOf(mTimerList.getList(), timerItemBase) != -1)
	{
		((TimerItemBase*)delayObject)->mIsDisposed = true;
		if (bInDepth())
		{
			DelayHandleMgrBase::delObject(delayObject);
		}
		else
		{
			for(TimerItemBase* item : mTimerList.getList())
			{
				if (item == delayObject)
				{
					UtilVector::Remove(mTimerList.getList(), item);
					break;
				}
			}
		}
	}
}

void TimerMgr::Advance(float delta)
{
	incDepth();

	for(TimerItemBase* timerItem : mTimerList.getList())
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

	decDepth();
}