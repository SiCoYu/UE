#include "MyProject.h"
#include "EventDispatch.h"
#include "Common.h"
#include "EventDispatchFunctionObject.h"

EventDispatch::EventDispatch(int eventId_)
{
	m_eventId = eventId_;
}

int EventDispatch::getUniqueId()
{
	return m_uniqueId;
}

void EventDispatch::setUniqueId(int value)
{
	m_uniqueId = value;
	m_handleList.setUniqueId(m_uniqueId);
}

//public LuaCSBridgeDispatch luaCSBridgeDispatch
//{
//    get
//    {
//        return m_luaCSBridgeDispatch;
//    }
//    set
//    {
//        m_luaCSBridgeDispatch = value;
//    }
//}

// 相同的函数只能增加一次
void EventDispatch::addEventHandle(EventDispatchDelegate handle)
{
	EventDispatchFunctionObject* funcObject = new EventDispatchFunctionObject();
	funcObject->m_handle = handle;
	if (nullptr != handle)
	{
		addObject(funcObject);
	}
	else
	{
		g_pLogSys->log("Event Handle is null");
	}
}

void EventDispatch::addObject(IDelayHandleItem* delayObject, float priority)
{
	if (bInDepth())
	{
		DelayHandleMgrBase::addObject(delayObject, priority);
	}
	else
	{
		// 这个判断说明相同的函数只能加一次，但是如果不同资源使用相同的回调函数就会有问题，但是这个判断可以保证只添加一次函数，值得，因此不同资源需要不同回调函数
		m_handleList.Add((EventDispatchFunctionObject*)delayObject);
	}
}

void EventDispatch::removeEventHandle(EventDispatchDelegate handle)
{
	int idx = 0;
	for (idx = 0; idx < m_handleList.Count(); ++idx)
	{
		if (m_handleList[idx]->m_handle, handle)
		{
			break;
		}
	}
	if (idx < m_handleList.Count())
	{
		delObject(m_handleList[idx]);
	}
	else
	{
		g_pLogSys->log("Event Handle not exist");
	}
}

void EventDispatch::delObject(IDelayHandleItem* delayObject)
{
	if (bInDepth())
	{
		DelayHandleMgrBase::delObject(delayObject);
	}
	else
	{
		if (!m_handleList.Remove((EventDispatchFunctionObject*)delayObject))
		{
			g_pLogSys->log("Event Handle not exist");
		}
	}
}

void EventDispatch::dispatchEvent(IDispatchObject* dispatchObject)
{
	//try
	//{
	incDepth();

	for(auto handle : m_handleList.getList())
	{
		if (!handle->m_bClientDispose)
		{
			handle->m_handle(dispatchObject);
		}
	}

	//if (m_luaCSBridgeDispatch != nullptr)
	//{
	//	m_luaCSBridgeDispatch.handleGlobalEvent(m_eventId, dispatchObject);
	//}

	decDepth();
	//}
	//catch (Exception ex)
	//{
	//    Ctx.m_instance.m_logSys.catchLog(ex.ToString());
	//}
}

void EventDispatch::clearEventHandle()
{
	if (bInDepth())
	{
		for(auto item : m_handleList.getList())
		{
			delObject(item);
		}
	}
	else
	{
		m_handleList.Clear();
	}
}

// 这个判断说明相同的函数只能加一次，但是如果不同资源使用相同的回调函数就会有问题，但是这个判断可以保证只添加一次函数，值得，因此不同资源需要不同回调函数
bool EventDispatch::existEventHandle(EventDispatchDelegate handle)
{
	bool bFinded = false;
	for(auto item : m_handleList.getList())
	{
		if (item->m_handle == handle)
		{
			bFinded = true;
			break;
		}
	}

	return bFinded;
}

void EventDispatch::copyFrom(EventDispatch& rhv)
{
	for(auto handle : rhv.getHandleList().getList())
	{
		m_handleList.Add(handle);
	}
}

MList<EventDispatchFunctionObject*>& EventDispatch::getHandleList()
{
	return m_handleList;
}