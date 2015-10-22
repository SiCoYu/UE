#include "MyProject.h"
#include "TickMgr.h"
#include "ITickedObject.h"
#include "TickProcessObject.h"

TickMgr::TickMgr()
{

}

void TickMgr::addTick(ITickedObject* tickObj, float priority = 0.0f)
{
	addObject((IDelayHandleItem*)tickObj, priority);
}

void TickMgr::addObject(IDelayHandleItem* delayObject, float priority)
{
	if (bInDepth())
	{
		DelayHandleMgrBase::addObject(delayObject, priority);
	}
	else
	{
		int position = -1;
		for (int i = 0; i < m_tickLst.Count(); i++)
		{
			if (m_tickLst[i] == nullptr)
				continue;

			if (m_tickLst[i]->m_tickObject == (ITickedObject*)delayObject)
			{
				return;
			}

			if (m_tickLst[i]->m_priority < priority)
			{
				position = i;
				break;
			}
		}

		TickProcessObject* processObject = new TickProcessObject();
		processObject->m_tickObject = (ITickedObject*)delayObject;
		processObject->m_priority = priority;

		if (position < 0 || position >= m_tickLst.Count)
		{
			m_tickLst.Add(processObject);
		}
		else
		{
			m_tickLst.Insert(position, processObject);
		}
	}
}

void TickMgr::delObject(IDelayHandleItem* delayObject)
{
	if (bInDepth())
	{
		DelayHandleMgrBase::delObject(delayObject);
	}
	else
	{
		for(TickProcessObject* item : m_tickLst.getList())
		{
			if (item->m_tickObject == (ITickedObject*)delayObject)
			{
				m_tickLst.Remove(item);
				break;
			}
		}
	}
}

void TickMgr::Advance(float delta)
{
	incDepth();

	for(TickProcessObject* tk : m_tickLst.getList())
	{
		if (!((IDelayHandleItem*)(tk->m_tickObject))->getClientDispose())
		{
			((ITickedObject*)(tk->m_tickObject))->onTick(delta);
		}
	}

	decDepth();
}