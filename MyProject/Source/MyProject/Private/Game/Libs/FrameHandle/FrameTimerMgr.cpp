#include "MyProject.h"
#include "FrameTimerMgr.h"

FrameTimerMgr::FrameTimerMgr()
{

}

void FrameTimerMgr::addObject(IDelayHandleItem delayObject, float priority = 0.0f)
{
	// 检查当前是否已经在队列中
	if (m_timerLists.IndexOf(delayObject as FrameTimerItem) == -1)
	{
		if (bInDepth())
		{
			base.addObject(delayObject, priority);
		}
		else
		{
			m_timerLists.Add(delayObject as FrameTimerItem);
		}
	}
}

void FrameTimerMgr::delObject(IDelayHandleItem delayObject)
{
	// 检查当前是否在队列中
	if (m_timerLists.IndexOf(delayObject as FrameTimerItem) != -1)
	{
		(delayObject as FrameTimerItem).m_disposed = true;
		if (bInDepth())
		{
			base.addObject(delayObject);
		}
		else
		{
			foreach(FrameTimerItem item in m_timerLists)
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

void FrameTimerMgr::Advance(float delta)
{
	incDepth();

	foreach(FrameTimerItem timerItem in m_timerLists)
	{
		if (!timerItem.getClientDispose())
		{
			timerItem.OnFrameTimer();
		}
		if (timerItem.m_disposed)
		{
			delObject(timerItem);
		}
	}

	decDepth();
}