#include "MyProject.h"
#include "DelayHandleMgrBase.h"

// 只有没有添加到列表中的才能添加
bool DelayHandleMgrBase::existAddList(IDelayHandleItem delayObject)
{
	foreach(var item in m_deferredAddQueue.list)
	{
		if (UtilApi.isAddressEqual(item.m_delayObject, delayObject))
		{
			return true;
		}
	}

	return false;
}

// 只有没有添加到列表中的才能添加
bool DelayHandleMgrBase::existDelList(IDelayHandleItem delayObject)
{
	foreach(var item in m_deferredDelQueue.list)
	{
		if (UtilApi.isAddressEqual(item.m_delayObject, delayObject))
		{
			return true;
		}
	}

	return false;
}

// 从延迟添加列表删除一个 Item
void DelayHandleMgrBase::delFromDelayAddList(IDelayHandleItem delayObject)
{
	foreach(var item in m_deferredAddQueue.list)
	{
		if (UtilApi.isAddressEqual(item.m_delayObject, delayObject))
		{
			m_deferredAddQueue.Remove(item);
		}
	}
}

// 从延迟删除列表删除一个 Item
void DelayHandleMgrBase::delFromDelayDelList(IDelayHandleItem delayObject)
{
	foreach(var item in m_deferredDelQueue.list)
	{
		if (UtilApi.isAddressEqual(item.m_delayObject, delayObject))
		{
			m_deferredDelQueue.Remove(item);
		}
	}
}

void DelayHandleMgrBase::processDelayObjects()
{
	if (0 == m_loopDepth)       // 只有全部退出循环后，才能处理添加删除
	{
		if (m_deferredAddQueue.Count() > 0)
		{
			for (int idx = 0; idx < m_deferredAddQueue.Count(); idx++)
			{
				addObject(m_deferredAddQueue[idx].m_delayObject, (m_deferredAddQueue[idx].m_delayParam as DelayAddParam).m_priority);
			}

			m_deferredAddQueue.Clear();
		}

		if (m_deferredDelQueue.Count() > 0)
		{
			for (int idx = 0; idx < m_deferredDelQueue.Count(); idx++)
			{
				delObject(m_deferredDelQueue[idx].m_delayObject);
			}

			m_deferredDelQueue.Clear();
		}
	}
}

DelayHandleMgrBase::DelayHandleMgrBase()
{
	m_deferredAddQueue = new MList<DelayHandleObject>();
	m_deferredDelQueue = new MList<DelayHandleObject>();

	m_loopDepth = 0;
}

void DelayHandleMgrBase::addObject(IDelayHandleItem delayObject, float priority = 0.0f)
{
	if (m_loopDepth > 0)
	{
		if (!existAddList(delayObject))        // 如果添加列表中没有
		{
			if (existDelList(delayObject))    // 如果已经添加到删除列表中
			{
				delFromDelayDelList(delayObject);
			}

			DelayHandleObject delayHandleObject = new DelayHandleObject();
			delayHandleObject.m_delayParam = new DelayAddParam();
			m_deferredAddQueue.Add(delayHandleObject);

			delayHandleObject.m_delayObject = delayObject;
			(delayHandleObject.m_delayParam as DelayAddParam).m_priority = priority;
		}
	}
}

void DelayHandleMgrBase::delObject(IDelayHandleItem* delayObject)
{
	if (m_loopDepth > 0)
	{
		if (!existDelList(delayObject))
		{
			if (existAddList(delayObject))    // 如果已经添加到删除列表中
			{
				delFromDelayAddList(delayObject);
			}

			delayObject.setClientDispose();

			DelayHandleObject delayHandleObject = new DelayHandleObject();
			delayHandleObject.m_delayParam = new DelayDelParam();
			m_deferredDelQueue.Add(delayHandleObject);
			delayHandleObject.m_delayObject = delayObject;
		}
	}
}

void DelayHandleMgrBase::incDepth()
{
	++m_loopDepth;
}

void DelayHandleMgrBase::decDepth()
{
	--m_loopDepth;
	processDelayObjects();
}

bool DelayHandleMgrBase::bInDepth()
{
	return m_loopDepth > 0;
}