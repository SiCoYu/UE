#include "MyProject.h"
#include "EventDispatch.h"

EventDispatch::EventDispatch(int eventId_ = 0)
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
	m_handleList.uniqueId = m_uniqueId;
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
void EventDispatch::addEventHandle(Action<IDispatchObject> handle)
{
	EventDispatchFunctionObject funcObject = new EventDispatchFunctionObject();
	funcObject.m_handle = handle;
	if (null != handle)
	{
		addObject(funcObject);
	}
	else
	{
		Ctx.m_instance.m_logSys.log("Event Handle is null");
	}
}

void EventDispatch::addObject(IDelayHandleItem delayObject, float priority = 0.0f)
{
	if (bInDepth())
	{
		base.addObject(delayObject, priority);
	}
	else
	{
		// 这个判断说明相同的函数只能加一次，但是如果不同资源使用相同的回调函数就会有问题，但是这个判断可以保证只添加一次函数，值得，因此不同资源需要不同回调函数
		m_handleList.Add(delayObject as EventDispatchFunctionObject);
	}
}

void EventDispatch::removeEventHandle(Action<IDispatchObject> handle)
{
	int idx = 0;
	for (idx = 0; idx < m_handleList.Count(); ++idx)
	{
		if (UtilApi.isAddressEqual(m_handleList[idx].m_handle, handle))
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
		Ctx.m_instance.m_logSys.log("Event Handle not exist");
	}
}

void EventDispatch::delObject(IDelayHandleItem delayObject)
{
	if (bInDepth())
	{
		base.delObject(delayObject);
	}
	else
	{
		if (!m_handleList.Remove(delayObject as EventDispatchFunctionObject))
		{
			Ctx.m_instance.m_logSys.log("Event Handle not exist");
		}
	}
}

void EventDispatch::dispatchEvent(IDispatchObject dispatchObject)
{
	//try
	//{
	incDepth();

	foreach(var handle in m_handleList.list)
	{
		if (!handle.m_bClientDispose)
		{
			handle.m_handle(dispatchObject);
		}
	}

	if (m_luaCSBridgeDispatch != null)
	{
		m_luaCSBridgeDispatch.handleGlobalEvent(m_eventId, dispatchObject);
	}

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
		foreach(var item in m_handleList.list)
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
bool EventDispatch::existEventHandle(Action<IDispatchObject> handle)
{
	bool bFinded = false;
	foreach(var item in m_handleList.list)
	{
		if (UtilApi.isAddressEqual(item.m_handle, handle))
		{
			bFinded = true;
			break;
		}
	}

	return bFinded;
}

void EventDispatch::copyFrom(ResEventDispatch rhv)
{
	foreach(var handle in rhv.handleList.list)
	{
		m_handleList.Add(handle);
	}
}