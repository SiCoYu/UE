#include "MyProject.h"
#include "TimerMgr.h"
#include "TimerItemBase.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(TimerMgr, DelayPriorityHandleMgrBase)

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

	if (!this->mTimerList.contains(timerItemBase))
	{
		if (this->_isInDepth())
		{
			Super::_addObject(delayObject, priority);
		}
		else
		{
			this->mTimerList.add((TimerItemBase*)delayObject);
		}
	}
}

void TimerMgr::_removeObject(IDelayHandleItem* delayObject)
{
	// 检查当前是否在队列中
	TimerItemBase* timerItemBase = (TimerItemBase*)delayObject;

	if (this->mTimerList.contains(timerItemBase))
	{
		((TimerItemBase*)delayObject)->mIsDisposed = true;

		if (this->_isInDepth())
		{
			Super::_removeObject(delayObject);
		}
		else
		{
			for(TimerItemBase* item : this->mTimerList.getList())
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

void TimerMgr::addTimer(TimerItemBase* delayObject, float priority = 0.0f)
{
	if (!this->mTimerList.contains(delayObject))
	{
		this->_addObject(delayObject, priority);
	}
}

void TimerMgr::removeTimer(TimerItemBase* timer)
{
	if (this->mTimerList.contains(timer))
	{
		this->_removeObject(timer);
	}
}

void TimerMgr::advance(float delta)
{
	this->_incDepth();

	for(TimerItemBase* timerItem : this->mTimerList.getList())
	{
		if (!timerItem->isClientDispose())
		{
			timerItem->OnTimer(delta);
		}

		if (timerItem->mIsDisposed)        // 如果已经结束
		{
			this->_removeObject(timerItem);
		}
	}

	this->_decDepth();
}

MY_END_NAMESPACE