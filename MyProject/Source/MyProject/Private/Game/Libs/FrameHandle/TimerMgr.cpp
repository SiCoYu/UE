#include "MyProject.h"
#include "TimerMgr.h"

TimerMgr::TimerMgr()
{

}

void TimerMgr::addObject(IDelayHandleItem* delayObject, float priority = 0.0f)
{
	// 检查当前是否已经在队列中
	if (m_timerLists.IndexOf((TimerItemBase*)delayObject) == -1)
	{
		if (bInDepth())
		{
			base.addObject(delayObject, priority);
		}
		else
		{
			m_timerLists.Add(delayObject as TimerItemBase);
		}
	}
}

void TimerMgr::delObject(IDelayHandleItem* delayObject)
{
	// 检查当前是否在队列中
	if (m_timerLists.IndexOf((TimerItemBase*)delayObject) != -1)
	{
		(delayObject as TimerItemBase).m_disposed = true;
		if (bInDepth())
		{
			base.delObject(delayObject);
		}
		else
		{
			foreach(TimerItemBase item in m_timerLists)
			{
				if (UtilApi.isAddressEqual(item, delayObject))
				{
					m_timerLists.Remove(item);
					break;
				}
			}
		}
	}
}

void TimerMgr::Advance(float delta)
{
	incDepth();

	foreach(TimerItemBase timerItem in m_timerLists)
	{
		if (!timerItem.getClientDispose())
		{
			timerItem.OnTimer(delta);
		}

		if (timerItem.m_disposed)        // 如果已经结束
		{
			delObject(timerItem);
		}
	}

	decDepth();
}