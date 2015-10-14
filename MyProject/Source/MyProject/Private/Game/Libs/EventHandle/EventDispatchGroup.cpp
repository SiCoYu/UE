#include "MyProject.h"
#include "EventDispatchGroup.h"

EventDispatchGroup::EventDispatchGroup()
{
	m_bInLoop = false;
}

// 添加分发器
void EventDispatchGroup::addEventDispatch(int groupID, EventDispatch disp)
{
	if (!m_groupID2DispatchDic.ContainsKey(groupID))
	{
		m_groupID2DispatchDic[groupID] = disp;
	}
}

void EventDispatchGroup::addEventHandle(int groupID, Action<IDispatchObject> handle)
{
	m_groupID2DispatchDic[groupID].addEventHandle(handle);
}

void EventDispatchGroup::removeEventHandle(int groupID, Action<IDispatchObject> handle)
{
	if (m_groupID2DispatchDic.ContainsKey(groupID))
	{
		m_groupID2DispatchDic[groupID].removeEventHandle(handle);
	}
	else
	{
		Ctx.m_instance.m_logSys.log("Event Dispatch Group not exist");
	}
}

void EventDispatchGroup::dispatchEvent(int groupID, IDispatchObject dispatchObject)
{
	m_bInLoop = true;
	if (m_groupID2DispatchDic.ContainsKey(groupID))
	{
		m_groupID2DispatchDic[groupID].dispatchEvent(dispatchObject);
	}
	else
	{
		Ctx.m_instance.m_logSys.log("Event Dispatch Group not exist");
	}
	m_bInLoop = false;
}

void EventDispatchGroup::clearAllEventHandle()
{
	if (!m_bInLoop)
	{
		foreach(EventDispatch dispatch in m_groupID2DispatchDic.Values)
		{
			dispatch.clearEventHandle();
		}

		m_groupID2DispatchDic.Clear();
	}
	else
	{
		Ctx.m_instance.m_logSys.log("looping cannot delete element");
	}
}

void EventDispatchGroup::clearGroupEventHandle(int groupID)
{
	if (!m_bInLoop)
	{
		if (m_groupID2DispatchDic.ContainsKey(groupID))
		{
			m_groupID2DispatchDic[groupID].clearEventHandle();
			m_groupID2DispatchDic.Remove(groupID);
		}
		else
		{
			Ctx.m_instance.m_logSys.log("Event Dispatch Group not exist");
		}
	}
	else
	{
		Ctx.m_instance.m_logSys.log("looping cannot delete element");
	}
}