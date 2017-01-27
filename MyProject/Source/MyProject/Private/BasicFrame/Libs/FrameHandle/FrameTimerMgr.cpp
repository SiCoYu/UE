#include "MyProject.h"
#include "FrameTimerMgr.h"
#include "IDelayHandleItem.h"
#include "FrameTimerItem.h"
#include "UtilContainers.h"

FrameTimerMgr::FrameTimerMgr()
{

}

void FrameTimerMgr::addObject(IDelayHandleItem* delayObject, float priority)
{
	// 检查当前是否已经在队列中
	FrameTimerItem* frameTimerItem = (FrameTimerItem*)delayObject;
	if (UtilVector::IndexOf(mTimerList, frameTimerItem) == -1)
	{
		if (isInDepth())
		{
			DelayHandleMgrBase::addObject(delayObject, priority);
		}
		else
		{
			mTimerList.push_back((FrameTimerItem*)delayObject);
		}
	}
}

void FrameTimerMgr::delObject(IDelayHandleItem* delayObject)
{
	// 检查当前是否在队列中
	FrameTimerItem* frameTimerItem = (FrameTimerItem*)delayObject;
	if (UtilVector::IndexOf(mTimerList, frameTimerItem) != -1)
	{
		((FrameTimerItem*)delayObject)->mIsDisposed = true;
		if (isInDepth())
		{
			DelayHandleMgrBase::addObject(delayObject);
		}
		else
		{
			for(FrameTimerItem* item : mTimerList)
			{
				if (item == delayObject)
				{
					UtilVector::Remove(mTimerList, item);
					break;
				}
			}
		}
	}
}

void FrameTimerMgr::Advance(float delta)
{
	incDepth();

	for(FrameTimerItem* timerItem : mTimerList)
	{
		if (!timerItem->isClientDispose())
		{
			timerItem->OnFrameTimer();
		}
		if (timerItem->mIsDisposed)
		{
			delObject(timerItem);
		}
	}

	decDepth();
}