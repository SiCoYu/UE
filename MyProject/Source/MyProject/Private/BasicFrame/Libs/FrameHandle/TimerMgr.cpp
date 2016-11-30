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
	if (UtilVector::IndexOf(m_timerLists.getList(), timerItemBase) == -1)
	{
		if (bInDepth())
		{
			DelayHandleMgrBase::addObject(delayObject, priority);
		}
		else
		{
			m_timerLists.Add((TimerItemBase*)delayObject);
		}
	}
}

void TimerMgr::delObject(IDelayHandleItem* delayObject)
{
	// 检查当前是否在队列中
	TimerItemBase* timerItemBase = (TimerItemBase*)delayObject;
	if (UtilVector::IndexOf(m_timerLists.getList(), timerItemBase) != -1)
	{
		((TimerItemBase*)delayObject)->m_disposed = true;
		if (bInDepth())
		{
			DelayHandleMgrBase::delObject(delayObject);
		}
		else
		{
			for(TimerItemBase* item : m_timerLists.getList())
			{
				if (item == delayObject)
				{
					UtilVector::Remove(m_timerLists.getList(), item);
					break;
				}
			}
		}
	}
}

void TimerMgr::Advance(float delta)
{
	incDepth();

	for(TimerItemBase* timerItem : m_timerLists.getList())
	{
		if (!timerItem->getClientDispose())
		{
			timerItem->OnTimer(delta);
		}

		if (timerItem->m_disposed)        // 如果已经结束
		{
			delObject(timerItem);
		}
	}

	decDepth();
}