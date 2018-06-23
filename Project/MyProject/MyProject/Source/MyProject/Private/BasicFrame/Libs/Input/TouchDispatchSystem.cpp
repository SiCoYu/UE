#include "MyProject.h"
#include "TouchDispatchSystem.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"
#include "IDispatchObject.h"
#include "MMouseOrTouch.h"
#include "AddOnceEventDispatch.h"

MY_BEGIN_NAMESPACE(MyNS)

TouchDispatchSystem::TouchDispatchSystem()
{
	this->mOnTouchBeganDispatch = MY_NEW AddOnceEventDispatch();
	this->mOnTouchMovedDispatch = MY_NEW AddOnceEventDispatch();
	this->mOnTouchStationaryDispatch = MY_NEW AddOnceEventDispatch();
	this->mOnTouchEndedDispatch = MY_NEW AddOnceEventDispatch();
	this->mOnTouchCanceledDispatch = MY_NEW AddOnceEventDispatch();

	this->mOnMultiTouchBeganDispatch = MY_NEW AddOnceEventDispatch();
	this->mOnMultiTouchMovedDispatch = MY_NEW AddOnceEventDispatch();
	this->mOnMultiTouchStationaryDispatch = MY_NEW AddOnceEventDispatch();
	this->mOnMultiTouchEndedDispatch = MY_NEW AddOnceEventDispatch();
	this->mOnMultiTouchCanceledDispatch = MY_NEW AddOnceEventDispatch();
}

void TouchDispatchSystem::init()
{

}

void TouchDispatchSystem::dispose()
{

}

void TouchDispatchSystem::addTouchListener(InputEventId evtId, EventDispatchDelegate handle)
{
	if (InputEventId::TOUCHBEGIN_EVENT == evtId)
	{
		this->mOnTouchBeganDispatch->addEventHandle(handle);
	}
	else if (InputEventId::TOUCHMOVED_EVENT == evtId)
	{
		this->mOnTouchMovedDispatch->addEventHandle(handle);
	}
	else if (InputEventId::TOUCHSTATIONARY_EVENT == evtId)
	{
		this->mOnTouchStationaryDispatch->addEventHandle(handle);
	}
	else if (InputEventId::TOUCHENDED_EVENT == evtId)
	{
		this->mOnTouchEndedDispatch->addEventHandle(handle);
	}
	else if (InputEventId::TOUCHCANCELED_EVENT == evtId)
	{
		this->mOnTouchCanceledDispatch->addEventHandle(handle);
	}

	this->mHasTouch = true;
}

void TouchDispatchSystem::removeTouchListener(InputEventId evtId, EventDispatchDelegate handle)
{
	if (InputEventId::TOUCHBEGIN_EVENT == evtId)
	{
		this->mOnTouchBeganDispatch->removeEventHandle(handle);
	}
	else if (InputEventId::TOUCHMOVED_EVENT == evtId)
	{
		this->mOnTouchMovedDispatch->removeEventHandle(handle);
	}
	else if (InputEventId::TOUCHSTATIONARY_EVENT == evtId)
	{
		this->mOnTouchStationaryDispatch->removeEventHandle(handle);
	}
	else if (InputEventId::TOUCHENDED_EVENT == evtId)
	{
		this->mOnTouchEndedDispatch->removeEventHandle(handle);
	}
	else if (InputEventId::TOUCHCANCELED_EVENT == evtId)
	{
		this->mOnTouchCanceledDispatch->removeEventHandle(handle);
	}

	this->mHasTouch = this->hasEventHandle();
}

// 是否还有需要处理的事件
bool TouchDispatchSystem::hasEventHandle()
{
	if (this->mOnTouchBeganDispatch->hasEventHandle())
	{
		return true;
	}
	if (this->mOnTouchMovedDispatch->hasEventHandle())
	{
		return true;
	}
	if (this->mOnTouchStationaryDispatch->hasEventHandle())
	{
		return true;
	}
	if (this->mOnTouchEndedDispatch->hasEventHandle())
	{
		return true;
	}
	if (this->mOnTouchCanceledDispatch->hasEventHandle())
	{
		return true;
	}

	return false;
}

bool TouchDispatchSystem::hasTouch()
{
	return this->mHasTouch;
}

void TouchDispatchSystem::handleTouchBegan(MMouseOrTouch* touch)
{
	if (nullptr != this->mOnTouchBeganDispatch)
	{
		this->mOnTouchBeganDispatch->dispatchEvent(touch);
	}
}

void TouchDispatchSystem::handleTouchMoved(MMouseOrTouch* touch)
{
	if (nullptr != this->mOnTouchMovedDispatch)
	{
		this->mOnTouchMovedDispatch->dispatchEvent(touch);
	}
}

void TouchDispatchSystem::handleTouchStationary(MMouseOrTouch* touch)
{
	if (nullptr != this->mOnTouchStationaryDispatch)
	{
		this->mOnTouchStationaryDispatch->dispatchEvent(touch);
	}
}

void TouchDispatchSystem::handleTouchEnded(MMouseOrTouch* touch)
{
	if (nullptr != this->mOnTouchEndedDispatch)
	{
		this->mOnTouchEndedDispatch->dispatchEvent(touch);
	}
}

void TouchDispatchSystem::handleTouchCanceled(MMouseOrTouch* touch)
{
	if (nullptr != this->mOnTouchCanceledDispatch)
	{
		this->mOnTouchCanceledDispatch->dispatchEvent(touch);
	}
}

/********************************** Multi Touch *********************************/
void TouchDispatchSystem::addMultiTouchListener(InputEventId evtId, EventDispatchDelegate handle)
{
	if (InputEventId::MULTI_TOUCHBEGIN_EVENT == evtId)
	{
		this->mOnMultiTouchBeganDispatch->addEventHandle(handle);
	}
	else if (InputEventId::MULTI_TOUCHMOVED_EVENT == evtId)
	{
		this->mOnMultiTouchMovedDispatch->addEventHandle(handle);
	}
	else if (InputEventId::MULTI_TOUCHSTATIONARY_EVENT == evtId)
	{
		this->mOnMultiTouchStationaryDispatch->addEventHandle(handle);
	}
	else if (InputEventId::MULTI_TOUCHENDED_EVENT == evtId)
	{
		this->mOnMultiTouchEndedDispatch->addEventHandle(handle);
	}
	else if (InputEventId::MULTI_TOUCHCANCELED_EVENT == evtId)
	{
		this->mOnMultiTouchCanceledDispatch->addEventHandle(handle);
	}

	this->mHasMultiTouch = true;
}

void TouchDispatchSystem::removeMultiTouchListener(InputEventId evtId, EventDispatchDelegate handle)
{
	if (InputEventId::MULTI_TOUCHBEGIN_EVENT == evtId)
	{
		this->mOnMultiTouchBeganDispatch->removeEventHandle(handle);
	}
	else if (InputEventId::MULTI_TOUCHMOVED_EVENT == evtId)
	{
		this->mOnMultiTouchMovedDispatch->removeEventHandle(handle);
	}
	else if (InputEventId::MULTI_TOUCHSTATIONARY_EVENT == evtId)
	{
		this->mOnMultiTouchStationaryDispatch->removeEventHandle(handle);
	}
	else if (InputEventId::MULTI_TOUCHENDED_EVENT == evtId)
	{
		this->mOnMultiTouchEndedDispatch->removeEventHandle(handle);
	}
	else if (InputEventId::MULTI_TOUCHCANCELED_EVENT == evtId)
	{
		this->mOnMultiTouchCanceledDispatch->removeEventHandle(handle);
	}

	this->mHasMultiTouch = this->hasMultiEventHandle();
}

// 是否还有需要处理的事件
bool TouchDispatchSystem::hasMultiEventHandle()
{
	bool ret = false;

	if (this->mOnMultiTouchBeganDispatch->hasEventHandle())
	{
		ret = true;
	}
	if (this->mOnMultiTouchMovedDispatch->hasEventHandle())
	{
		ret = true;
	}
	if (this->mOnMultiTouchStationaryDispatch->hasEventHandle())
	{
		ret = true;
	}
	if (this->mOnMultiTouchEndedDispatch->hasEventHandle())
	{
		ret = true;
	}
	if (this->mOnMultiTouchCanceledDispatch->hasEventHandle())
	{
		ret = true;
	}

	return ret;
}

bool TouchDispatchSystem::hasMultiTouch()
{
	return this->mHasMultiTouch;
}

void TouchDispatchSystem::handleMultiTouchBegan(IDispatchObject* touch)
{
	if (nullptr != this->mOnMultiTouchBeganDispatch)
	{
		this->mOnMultiTouchBeganDispatch->dispatchEvent(touch);
	}
}

void TouchDispatchSystem::handleMultiTouchMoved(IDispatchObject* touch)
{
	if (nullptr != this->mOnMultiTouchMovedDispatch)
	{
		this->mOnMultiTouchMovedDispatch->dispatchEvent(touch);
	}
}

void TouchDispatchSystem::handleMultiTouchStationary(IDispatchObject* touch)
{
	if (nullptr != this->mOnMultiTouchStationaryDispatch)
	{
		this->mOnMultiTouchStationaryDispatch->dispatchEvent(touch);
	}
}

void TouchDispatchSystem::handleMultiTouchEnded(IDispatchObject* touch)
{
	if (nullptr != this->mOnMultiTouchEndedDispatch)
	{
		this->mOnMultiTouchEndedDispatch->dispatchEvent(touch);
	}
}

void TouchDispatchSystem::handleMultiTouchCanceled(IDispatchObject* touch)
{
	if (nullptr != this->mOnMultiTouchCanceledDispatch)
	{
		this->mOnMultiTouchCanceledDispatch->dispatchEvent(touch);
	}
}

MY_END_NAMESPACE