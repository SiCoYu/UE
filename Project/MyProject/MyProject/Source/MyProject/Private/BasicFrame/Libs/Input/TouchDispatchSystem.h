#pragma once

#include "GObject.h"
#include "TickMode.h"
#include "InputEventId.h"
#include "EventDispatchDelegate.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class AddOnceEventDispatch;
class IDispatchObject;
class MMouseOrTouch;

/**
 * @brief 触碰后事件分发系统
 */
class TouchDispatchSystem : public GObject
{
private:
	bool mHasTouch;
    bool mHasMultiTouch;

    AddOnceEventDispatch* mOnTouchBeganDispatch;         // 触碰开始
    AddOnceEventDispatch* mOnTouchMovedDispatch;         // 触碰状态，但是移动
    AddOnceEventDispatch* mOnTouchStationaryDispatch;    // 触碰状态但是不移动
    AddOnceEventDispatch* mOnTouchEndedDispatch;         // 触碰结束
    AddOnceEventDispatch* mOnTouchCanceledDispatch;      // 触碰取消

    AddOnceEventDispatch* mOnMultiTouchBeganDispatch;         // 触碰开始
    AddOnceEventDispatch* mOnMultiTouchMovedDispatch;         // 触碰状态，但是移动
    AddOnceEventDispatch* mOnMultiTouchStationaryDispatch;    // 触碰状态但是不移动
    AddOnceEventDispatch* mOnMultiTouchEndedDispatch;         // 触碰结束
    AddOnceEventDispatch* mOnMultiTouchCanceledDispatch;      // 触碰取消

public:
	TouchDispatchSystem()
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

    void init()
    {

    }

    void dispose()
    {

    }

    void addTouchListener(InputEventId evtId, EventDispatchDelegate handle)
    {
        if (InputEventId::TOUCHBEGIN_EVENT == evtId)
        {
            this->mOnTouchBeganDispatch->addEventHandle(nullptr, handle);
        }
        else if (InputEventId::TOUCHMOVED_EVENT == evtId)
        {
            this->mOnTouchMovedDispatch->addEventHandle(nullptr, handle);
        }
        else if (InputEventId::TOUCHSTATIONARY_EVENT == evtId)
        {
            this->mOnTouchStationaryDispatch->addEventHandle(nullptr, handle);
        }
        else if (InputEventId::TOUCHENDED_EVENT == evtId)
        {
            this->mOnTouchEndedDispatch->addEventHandle(nullptr, handle);
        }
        else if (InputEventId::TOUCHCANCELED_EVENT == evtId)
        {
            this->mOnTouchCanceledDispatch->addEventHandle(nullptr, handle);
        }

        this->mHasTouch = true;
    }

    void removeTouchListener(InputEventId evtId, EventDispatchDelegate handle)
    {
        if (InputEventId::TOUCHBEGIN_EVENT == evtId)
        {
            this->mOnTouchBeganDispatch->removeEventHandle(nullptr, handle);
        }
        else if (InputEventId::TOUCHMOVED_EVENT == evtId)
        {
            this->mOnTouchMovedDispatch->removeEventHandle(nullptr, handle);
        }
        else if (InputEventId::TOUCHSTATIONARY_EVENT == evtId)
        {
            this->mOnTouchStationaryDispatch->removeEventHandle(nullptr, handle);
        }
        else if (InputEventId::TOUCHENDED_EVENT == evtId)
        {
            this->mOnTouchEndedDispatch->removeEventHandle(nullptr, handle);
        }
        else if (InputEventId::TOUCHCANCELED_EVENT == evtId)
        {
            this->mOnTouchCanceledDispatch->removeEventHandle(nullptr, handle);
        }

        this->mHasTouch = this->hasEventHandle();
    }

    // 是否还有需要处理的事件
    bool hasEventHandle()
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

    bool hasTouch()
    {
        return this->mHasTouch;
    }

    void handleTouchBegan(MMouseOrTouch* touch)
    {
        if (nullptr != this->mOnTouchBeganDispatch)
        {
            this->mOnTouchBeganDispatch->dispatchEvent(touch);
        }
    }

    void handleTouchMoved(MMouseOrTouch* touch)
    {
        if (nullptr != this->mOnTouchMovedDispatch)
        {
            this->mOnTouchMovedDispatch->dispatchEvent(touch);
        }
    }

    void handleTouchStationary(MMouseOrTouch* touch)
    {
        if (nullptr != this->mOnTouchStationaryDispatch)
        {
            this->mOnTouchStationaryDispatch->dispatchEvent(touch);
        }
    }

    void handleTouchEnded(MMouseOrTouch* touch)
    {
        if (nullptr != this->mOnTouchEndedDispatch)
        {
            this->mOnTouchEndedDispatch->dispatchEvent(touch);
        }
    }

    void handleTouchCanceled(MMouseOrTouch* touch)
    {
        if (nullptr != this->mOnTouchCanceledDispatch)
        {
            this->mOnTouchCanceledDispatch->dispatchEvent(touch);
        }
    }

    /********************************** Multi Touch *********************************/
    void addMultiTouchListener(InputEventId evtId, EventDispatchDelegate handle)
    {
        if (InputEventId::MULTI_TOUCHBEGIN_EVENT == evtId)
        {
            this->mOnMultiTouchBeganDispatch->addEventHandle(nullptr, handle);
        }
        else if (InputEventId::MULTI_TOUCHMOVED_EVENT == evtId)
        {
            this->mOnMultiTouchMovedDispatch->addEventHandle(nullptr, handle);
        }
        else if (InputEventId::MULTI_TOUCHSTATIONARY_EVENT == evtId)
        {
            this->mOnMultiTouchStationaryDispatch->addEventHandle(nullptr, handle);
        }
        else if (InputEventId::MULTI_TOUCHENDED_EVENT == evtId)
        {
            this->mOnMultiTouchEndedDispatch->addEventHandle(nullptr, handle);
        }
        else if (InputEventId::MULTI_TOUCHCANCELED_EVENT == evtId)
        {
            this->mOnMultiTouchCanceledDispatch->addEventHandle(nullptr, handle);
        }

        this->mHasMultiTouch = true;
    }

    void removeMultiTouchListener(InputEventId evtId, EventDispatchDelegate handle)
    {
        if (InputEventId::MULTI_TOUCHBEGIN_EVENT == evtId)
        {
            this->mOnMultiTouchBeganDispatch->removeEventHandle(nullptr, handle);
        }
        else if (InputEventId::MULTI_TOUCHMOVED_EVENT == evtId)
        {
            this->mOnMultiTouchMovedDispatch->removeEventHandle(nullptr, handle);
        }
        else if (InputEventId::MULTI_TOUCHSTATIONARY_EVENT == evtId)
        {
            this->mOnMultiTouchStationaryDispatch->removeEventHandle(nullptr, handle);
        }
        else if (InputEventId::MULTI_TOUCHENDED_EVENT == evtId)
        {
            this->mOnMultiTouchEndedDispatch->removeEventHandle(nullptr, handle);
        }
        else if (InputEventId::MULTI_TOUCHCANCELED_EVENT == evtId)
        {
            this->mOnMultiTouchCanceledDispatch->removeEventHandle(nullptr, handle);
        }

        this->mHasMultiTouch = this->hasMultiEventHandle();
    }

    // 是否还有需要处理的事件
    bool hasMultiEventHandle()
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

    bool hasMultiTouch()
    {
        return this->mHasMultiTouch;
    }

    void handleMultiTouchBegan(IDispatchObject* touch)
    {
        if (nullptr != this->mOnMultiTouchBeganDispatch)
        {
            this->mOnMultiTouchBeganDispatch->dispatchEvent(touch);
        }
    }

    void handleMultiTouchMoved(IDispatchObject* touch)
    {
        if (nullptr != this->mOnMultiTouchMovedDispatch)
        {
            this->mOnMultiTouchMovedDispatch->dispatchEvent(touch);
        }
    }

    void handleMultiTouchStationary(IDispatchObject* touch)
    {
        if (nullptr != this->mOnMultiTouchStationaryDispatch)
        {
            this->mOnMultiTouchStationaryDispatch->dispatchEvent(touch);
        }
    }

    void handleMultiTouchEnded(IDispatchObject* touch)
    {
        if (nullptr != this->mOnMultiTouchEndedDispatch)
        {
            this->mOnMultiTouchEndedDispatch->dispatchEvent(touch);
        }
    }

    void handleMultiTouchCanceled(IDispatchObject* touch)
    {
        if (nullptr != this->mOnMultiTouchCanceledDispatch)
        {
            this->mOnMultiTouchCanceledDispatch->dispatchEvent(touch);
        }
    }
};

MY_END_NAMESPACE