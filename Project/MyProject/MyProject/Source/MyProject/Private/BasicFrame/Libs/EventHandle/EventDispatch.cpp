#include "MyProject.h"
#include "EventDispatch.h"
#include "Prequisites.h"
#include "EventDispatchFunctionObject.h"
#include "MClassFactory.h"
#include "SafePointer.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(EventDispatch, DelayPriorityHandleMgrBase)

EventDispatch::EventDispatch(int eventId_)
{
	this->mEventId = eventId_;
}

EventDispatch::~EventDispatch()
{
	
}

void EventDispatch::init()
{
	Super::init();
}

void EventDispatch::dispose()
{
	int index = 0;
	int listLen = this->mHandleList.count();

	EventDispatchFunctionObject* handle = nullptr;

	while (index < listLen)
	{
		handle = this->mHandleList[index];
		MY_SAFE_DISPOSE(handle);

		index += 1;
	}

	Super::dispose();
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

// 相同的函数只能增加一次
void EventDispatch::addEventHandle(EventDispatchDelegate handle)
{
	EventDispatchFunctionObject* funcObject = MY_NEW EventDispatchFunctionObject();
	funcObject->mHandle = handle;

	if (nullptr != handle)
	{
		this->_addObject(funcObject);
	}
	else
	{
		GLogSys->log("Event Handle is nullptr");
	}
}

void EventDispatch::_addObject(IDelayHandleItem* delayObject, float priority)
{
	if (this->_isInDepth())
	{
		Super::_addObject(delayObject, priority);
	}
	else
	{
		// 这个判断说明相同的函数只能加一次，但是如果不同资源使用相同的回调函数就会有问题，但是这个判断可以保证只添加一次函数，值得，因此不同资源需要不同回调函数
		EventDispatchFunctionObject* ptr = (EventDispatchFunctionObject*)delayObject;
		this->mHandleList.add(ptr);
	}
}

void EventDispatch::removeEventHandle(EventDispatchDelegate handle)
{
	int index = 0;
	int listLen = this->mHandleList.count();

	while (index < listLen)
	{
		if (this->mHandleList[index]->mHandle, handle)
		{
			break;
		}

		index += 1;
	}

	if (index < this->mHandleList.count())
	{
		this->_removeObject(this->mHandleList[index]);
	}
	else
	{
		GLogSys->log("Event Handle not exist");
	}
}

void EventDispatch::_removeObject(IDelayHandleItem* delayObject)
{
	if (this->_isInDepth())
	{
		Super::_removeObject(delayObject);
	}
	else
	{
		EventDispatchFunctionObject* ptr = (EventDispatchFunctionObject*)delayObject;
		if (!this->mHandleList.remove(ptr))
		{
			GLogSys->log("Event Handle not exist");
		}

		EventDispatchFunctionObject* objPtr = (EventDispatchFunctionObject*)delayObject;
		MY_SAFE_DISPOSE(objPtr);
	}
}

void EventDispatch::dispatchEvent(IDispatchObject* dispatchObject)
{
	//try
	//{
	this->_incDepth();

	for(auto handle : this->mHandleList.getList())
	{
		if (!(GObject*)handle->isClientDispose())
		{
			handle->mHandle(dispatchObject);
		}
	}

	//if (m_luaCSBridgeDispatch != nullptr)
	//{
	//	m_luaCSBridgeDispatch.handleGlobalEvent(mEventId, dispatchObject);
	//}

	this->_decDepth();
	//}
	//catch (Exception ex)
	//{
	//    Ctx.m_instance.m_logSys.catchLog(ex.ToString());
	//}
}

void EventDispatch::clearEventHandle()
{
	if (this->_isInDepth())
	{
		for(auto item : mHandleList.getList())
		{
			this->_removeObject(item);
		}
	}
	else
	{
		this->mHandleList.clear();
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
		this->mHandleList.add(handle);
	}
}

MList<EventDispatchFunctionObject*>& EventDispatch::getHandleList()
{
	return this->mHandleList;
}

bool EventDispatch::hasEventHandle()
{
	return this->mHandleList.count() > 0;
}

int EventDispatch::getEventHandleCount()
{
	return this->mHandleList.count();
}

MY_END_NAMESPACE