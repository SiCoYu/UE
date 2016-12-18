#include "MyProject.h"
#include "EventDispatch.h"
#include "Common.h"
#include "EventDispatchFunctionObject.h"

EventDispatch::EventDispatch(int eventId_)
{
	mEventId = eventId_;
}

int EventDispatch::getUniqueId()
{
	return mUniqueId;
}

void EventDispatch::setUniqueId(int value)
{
	mUniqueId = value;
	mHandleList.setUniqueId(mUniqueId);
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
	funcObject->mHandle = handle;
	if (nullptr != handle)
	{
		addObject(funcObject);
	}
	else
	{
		GLogSys->log("Event Handle is null");
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
		mHandleList.Add((EventDispatchFunctionObject*)delayObject);
	}
}

void EventDispatch::removeEventHandle(EventDispatchDelegate handle)
{
	int idx = 0;
	for (idx = 0; idx < mHandleList.Count(); ++idx)
	{
		if (mHandleList[idx]->mHandle, handle)
		{
			break;
		}
	}
	if (idx < mHandleList.Count())
	{
		delObject(mHandleList[idx]);
	}
	else
	{
		GLogSys->log("Event Handle not exist");
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
		if (!mHandleList.Remove((EventDispatchFunctionObject*)delayObject))
		{
			GLogSys->log("Event Handle not exist");
		}
	}
}

void EventDispatch::dispatchEvent(IDispatchObject* dispatchObject)
{
	//try
	//{
	incDepth();

	for(auto handle : mHandleList.getList())
	{
		if (!handle->mIsClientDispose)
		{
			handle->mHandle(dispatchObject);
		}
	}

	//if (m_luaCSBridgeDispatch != nullptr)
	//{
	//	m_luaCSBridgeDispatch.handleGlobalEvent(mEventId, dispatchObject);
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
		for(auto item : mHandleList.getList())
		{
			delObject(item);
		}
	}
	else
	{
		mHandleList.Clear();
	}
}

// 这个判断说明相同的函数只能加一次，但是如果不同资源使用相同的回调函数就会有问题，但是这个判断可以保证只添加一次函数，值得，因此不同资源需要不同回调函数
bool EventDispatch::isExistEventHandle(EventDispatchDelegate handle)
{
	bool bFinded = false;
	for(auto item : mHandleList.getList())
	{
		if (item->mHandle == handle)
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
		mHandleList.Add(handle);
	}
}

MList<EventDispatchFunctionObject*>& EventDispatch::getHandleList()
{
	return mHandleList;
}