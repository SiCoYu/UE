#include "MyProject.h"
#include "EventDispatch.h"
#include "Common.h"
#include "EventDispatchFunctionObject.h"

EventDispatch::EventDispatch(int eventId_)
{
	this->mEventId = eventId_;
}

int EventDispatch::getUniqueId()
{
	return this->mUniqueId;
}

void EventDispatch::setUniqueId(int value)
{
	this->mUniqueId = value;
	this->mHandleList.setUniqueId(mUniqueId);
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
		this->addObject(funcObject);
	}
	else
	{
		GLogSys->log("Event Handle is null");
	}
}

void EventDispatch::addObject(IDelayHandleItem* delayObject, float priority)
{
	if (this->isInDepth())
	{
		Super::addObject(delayObject, priority);
	}
	else
	{
		// 这个判断说明相同的函数只能加一次，但是如果不同资源使用相同的回调函数就会有问题，但是这个判断可以保证只添加一次函数，值得，因此不同资源需要不同回调函数
		this->mHandleList.Add((EventDispatchFunctionObject*)delayObject);
	}
}

void EventDispatch::removeEventHandle(EventDispatchDelegate handle)
{
	int idx = 0;
	for (idx = 0; idx < mHandleList.Count(); ++idx)
	{
		if (this->mHandleList[idx]->mHandle, handle)
		{
			break;
		}
	}
	if (idx < this->mHandleList.Count())
	{
		this->delObject(this->mHandleList[idx]);
	}
	else
	{
		GLogSys->log("Event Handle not exist");
	}
}

void EventDispatch::delObject(IDelayHandleItem* delayObject)
{
	if (this->isInDepth())
	{
		Super::delObject(delayObject);
	}
	else
	{
		if (!this->mHandleList.Remove((EventDispatchFunctionObject*)delayObject))
		{
			GLogSys->log("Event Handle not exist");
		}
	}
}

void EventDispatch::dispatchEvent(IDispatchObject* dispatchObject)
{
	//try
	//{
	this->incDepth();

	for(auto handle : this->mHandleList.getList())
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
	if (this->isInDepth())
	{
		for(auto item : mHandleList.getList())
		{
			this->delObject(item);
		}
	}
	else
	{
		this->mHandleList.Clear();
	}
}

// 这个判断说明相同的函数只能加一次，但是如果不同资源使用相同的回调函数就会有问题，但是这个判断可以保证只添加一次函数，值得，因此不同资源需要不同回调函数
bool EventDispatch::isExistEventHandle(EventDispatchDelegate handle)
{
	bool bFinded = false;
	for(auto item : this->mHandleList.getList())
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
		this->mHandleList.Add(handle);
	}
}

MList<EventDispatchFunctionObject*>& EventDispatch::getHandleList()
{
	return this->mHandleList;
}