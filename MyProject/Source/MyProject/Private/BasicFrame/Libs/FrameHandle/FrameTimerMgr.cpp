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
	if (UtilVector::IndexOf(m_timerLists, frameTimerItem) == -1)
	{
		if (bInDepth())
		{
			DelayHandleMgrBase::addObject(delayObject, priority);
		}
		else
		{
			m_timerLists.push_back((FrameTimerItem*)delayObject);
		}
	}
}

void FrameTimerMgr::delObject(IDelayHandleItem* delayObject)
{
	// 检查当前是否在队列中
	FrameTimerItem* frameTimerItem = (FrameTimerItem*)delayObject;
	if (UtilVector::IndexOf(m_timerLists, frameTimerItem) != -1)
	{
		((FrameTimerItem*)delayObject)->m_disposed = true;
		if (bInDepth())
		{
			DelayHandleMgrBase::addObject(delayObject);
		}
		else
		{
			for(FrameTimerItem* item : m_timerLists)
			{
				if (item == delayObject)
				{
					UtilVector::Remove(m_timerLists, item);
					break;
				}
			}
		}
	}
}

void FrameTimerMgr::Advance(float delta)
{
	incDepth();

	for(FrameTimerItem* timerItem : m_timerLists)
	{
		if (!timerItem->getClientDispose())
		{
			timerItem->OnFrameTimer();
		}
		if (timerItem->m_disposed)
		{
			delObject(timerItem);
		}
	}

	decDepth();
}