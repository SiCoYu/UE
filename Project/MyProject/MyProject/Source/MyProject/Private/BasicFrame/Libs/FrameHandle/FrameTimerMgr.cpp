#include "MyProject.h"
#include "FrameTimerMgr.h"
#include "IDelayHandleItem.h"
#include "FrameTimerItem.h"

MY_BEGIN_NAMESPACE(MyNS)

FrameTimerMgr::FrameTimerMgr()
{

}

FrameTimerMgr::~FrameTimerMgr()
{

}

void FrameTimerMgr::init()
{
	Super::init();
}

void FrameTimerMgr::dispose()
{
	Super::dispose();
}

void FrameTimerMgr::addObject(IDelayHandleItem* delayObject, float priority)
{
	// 检查当前是否已经在队列中
	FrameTimerItem* frameTimerItem = (FrameTimerItem*)delayObject;

	if (!this->mTimerList.contains(frameTimerItem))
	{
		if (isInDepth())
		{
			DelayHandleMgrBase::addObject(delayObject, priority);
		}
		else
		{
			this->mTimerList.add((FrameTimerItem*)delayObject);
		}
	}
}

void FrameTimerMgr::delObject(IDelayHandleItem* delayObject)
{
	// 检查当前是否在队列中
	FrameTimerItem* frameTimerItem = (FrameTimerItem*)delayObject;

	if (this->mTimerList.contains(frameTimerItem))
	{
		((FrameTimerItem*)delayObject)->mIsDisposed = true;

		if (isInDepth())
		{
			DelayHandleMgrBase::addObject(delayObject);
		}
		else
		{
			for(FrameTimerItem* item : this->mTimerList.getList())
			{
				if (item == delayObject)
				{
					this->mTimerList.remove(item);
					break;
				}
			}
		}
	}
}

void FrameTimerMgr::Advance(float delta)
{
	this->incDepth();

	for(FrameTimerItem* timerItem : this->mTimerList.getList())
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

	this->decDepth();
}

MY_END_NAMESPACE