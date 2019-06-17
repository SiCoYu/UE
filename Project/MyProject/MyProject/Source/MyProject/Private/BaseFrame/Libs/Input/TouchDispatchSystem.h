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
	TouchDispatchSystem();

	void init();
	void dispose();

	void addTouchListener(InputEventId evtId, EventDispatchDelegate handle);
	void removeTouchListener(InputEventId evtId, EventDispatchDelegate handle);
    // 是否还有需要处理的事件
	bool hasEventHandle();
	bool hasTouch();

	void handleTouchBegan(MMouseOrTouch* touch);
	void handleTouchMoved(MMouseOrTouch* touch);
	void handleTouchStationary(MMouseOrTouch* touch);
	void handleTouchEnded(MMouseOrTouch* touch);
	void handleTouchCanceled(MMouseOrTouch* touch);

    /********************************** Multi Touch *********************************/
	void addMultiTouchListener(InputEventId evtId, EventDispatchDelegate handle);
	void removeMultiTouchListener(InputEventId evtId, EventDispatchDelegate handle);
    // 是否还有需要处理的事件
	bool hasMultiEventHandle();
	bool hasMultiTouch();

	void handleMultiTouchBegan(IDispatchObject* touch);
	void handleMultiTouchMoved(IDispatchObject* touch);
	void handleMultiTouchStationary(IDispatchObject* touch);
	void handleMultiTouchEnded(IDispatchObject* touch);
	void handleMultiTouchCanceled(IDispatchObject* touch);
};

MY_END_NAMESPACE