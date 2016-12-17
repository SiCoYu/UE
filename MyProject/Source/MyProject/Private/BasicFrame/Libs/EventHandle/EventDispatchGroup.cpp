#include "MyProject.h"
#include "EventDispatchGroup.h"
#include "Common.h"
#include "UtilContainers.h"
#include "EventDispatch.h"

EventDispatchGroup::EventDispatchGroup()
{
	m_bInLoop = false;
}

// 添加分发器
void EventDispatchGroup::addEventDispatch(int groupID, EventDispatch* disp)
{
	if (!UtilMap::ContainsKey(m_groupID2DispatchDic, groupID))
	{
		m_groupID2DispatchDic[groupID] = disp;
	}
}

void EventDispatchGroup::addEventHandle(int groupID, EventDispatchDelegate handle)
{
	m_groupID2DispatchDic[groupID]->addEventHandle(handle);
}

void EventDispatchGroup::removeEventHandle(int groupID, EventDispatchDelegate handle)
{
	if (UtilMap::ContainsKey(m_groupID2DispatchDic, groupID))
	{
		m_groupID2DispatchDic[groupID]->removeEventHandle(handle);
	}
	else
	{
		GLogSys->log("Event Dispatch Group not exist");
	}
}

void EventDispatchGroup::dispatchEvent(int groupID, IDispatchObject* dispatchObject)
{
	m_bInLoop = true;
	if (UtilMap::ContainsKey(m_groupID2DispatchDic, groupID))
	{
		m_groupID2DispatchDic[groupID]->dispatchEvent(dispatchObject);
	}
	else
	{
		GLogSys->log("Event Dispatch Group not exist");
	}
	m_bInLoop = false;
}

void EventDispatchGroup::clearAllEventHandle()
{
	if (!m_bInLoop)
	{
		// map for 语句
		for(auto dispatch : m_groupID2DispatchDic)
		{
			dispatch.second->clearEventHandle();
		}

		m_groupID2DispatchDic.clear();
	}
	else
	{
		GLogSys->log("looping cannot delete element");
	}
}

void EventDispatchGroup::clearGroupEventHandle(int groupID)
{
	if (!m_bInLoop)
	{
		if (UtilMap::ContainsKey(m_groupID2DispatchDic, groupID))
		{
			m_groupID2DispatchDic[groupID]->clearEventHandle();
			UtilMap::Remove(m_groupID2DispatchDic, groupID);
		}
		else
		{
			GLogSys->log("Event Dispatch Group not exist");
		}
	}
	else
	{
		GLogSys->log("looping cannot delete element");
	}
}