#include "MyProject.h"
#include "FrameTimerMgr.h"
#include "IDelayHandleItem.h"
#include "FrameTimerItem.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(FrameTimerMgr, DelayPriorityHandleMgrBase)

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

void FrameTimerMgr::_addObject(IDelayHandleItem* delayObject, float priority)
{
	// 检查当前是否已经在队列中
	FrameTimerItem* frameTimerItem = (FrameTimerItem*)delayObject;

	if (!this->mTimerList.contains(frameTimerItem))
	{
		if (this->_isInDepth())
		{
			Super::_addObject(delayObject, priority);
		}
		else
		{
			FrameTimerItem* ptr = (FrameTimerItem*)delayObject;
			this->mTimerList.add(ptr);
		}
	}
}

void FrameTimerMgr::_removeObject(IDelayHandleItem* delayObject)
{
	// 检查当前是否在队列中
	FrameTimerItem* frameTimerItem = (FrameTimerItem*)delayObject;

	if (this->mTimerList.contains(frameTimerItem))
	{
		((FrameTimerItem*)delayObject)->mIsDisposed = true;

		if (this->_isInDepth())
		{
			Super::_addObject(delayObject);
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

void FrameTimerMgr::addFrameTimer(FrameTimerItem* timer, float priority)
{
	this->_addObject(timer, priority);
}

void FrameTimerMgr::removeFrameTimer(FrameTimerItem* timer)
{
	this->_removeObject(timer);
}

void FrameTimerMgr::advance(float delta)
{
	this->_incDepth();

	for(FrameTimerItem* timerItem : this->mTimerList.getList())
	{
		if (!(GObject*)timerItem->isClientDispose())
		{
			timerItem->onFrameTimer();
		}
		if (timerItem->mIsDisposed)
		{
			this->_removeObject(timerItem);
		}
	}

	this->_decDepth();
}

MY_END_NAMESPACE