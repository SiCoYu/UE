#include "MyProject.h"
#include "DelayHandleMgrBase.h"
#include "DelayHandleObject.h"
#include "DelayAddParam.h"
#include "DelayDelParam.h"
#include "IDelayHandleItem.h"
#include "UtilContainers.h"

// 只有没有添加到列表中的才能添加
bool DelayHandleMgrBase::existAddList(IDelayHandleItem* delayObject)
{
	for(auto item : m_deferredAddQueue.getList())
	{
		if (item->m_delayObject == delayObject)
		{
			return true;
		}
	}

	return false;
}

// 只有没有添加到列表中的才能添加
bool DelayHandleMgrBase::existDelList(IDelayHandleItem* delayObject)
{
	for(auto item : m_deferredDelQueue.getList())
	{
		if (item->m_delayObject == delayObject)
		{
			return true;
		}
	}

	return false;
}

// 从延迟添加列表删除一个 Item
void DelayHandleMgrBase::delFromDelayAddList(IDelayHandleItem* delayObject)
{
	for(auto item : m_deferredAddQueue.getList())
	{
		if (item->m_delayObject == delayObject)
		{
			UtilVector::Remove(m_deferredAddQueue.getList(), item);
		}
	}
}

// 从延迟删除列表删除一个 Item
void DelayHandleMgrBase::delFromDelayDelList(IDelayHandleItem* delayObject)
{
	for(auto item : m_deferredDelQueue.getList())
	{
		if (item->m_delayObject == delayObject)
		{
			UtilVector::Remove(m_deferredDelQueue.getList(), item);
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
				addObject(m_deferredAddQueue[idx]->m_delayObject, ((DelayAddParam*)(m_deferredAddQueue[idx]->m_delayParam))->m_priority);
			}

			m_deferredAddQueue.Clear();
		}

		if (m_deferredDelQueue.Count() > 0)
		{
			for (int idx = 0; idx < m_deferredDelQueue.Count(); idx++)
			{
				delObject(m_deferredDelQueue[idx]->m_delayObject);
			}

			m_deferredDelQueue.Clear();
		}
	}
}

DelayHandleMgrBase::DelayHandleMgrBase()
{
	m_loopDepth = 0;
}

void DelayHandleMgrBase::addObject(IDelayHandleItem* delayObject, float priority)
{
	if (m_loopDepth > 0)
	{
		if (!existAddList(delayObject))        // 如果添加列表中没有
		{
			if (existDelList(delayObject))    // 如果已经添加到删除列表中
			{
				delFromDelayDelList(delayObject);
			}

			DelayHandleObject* delayHandleObject = new DelayHandleObject();
			delayHandleObject->m_delayParam = new DelayAddParam();
			m_deferredAddQueue.Add(delayHandleObject);

			delayHandleObject->m_delayObject = delayObject;
			((DelayAddParam*)(delayHandleObject->m_delayParam))->m_priority = priority;
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

			delayObject->setClientDispose();

			DelayHandleObject* delayHandleObject = new DelayHandleObject();
			delayHandleObject->m_delayParam = new DelayDelParam();
			m_deferredDelQueue.Add(delayHandleObject);
			delayHandleObject->m_delayObject = delayObject;
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