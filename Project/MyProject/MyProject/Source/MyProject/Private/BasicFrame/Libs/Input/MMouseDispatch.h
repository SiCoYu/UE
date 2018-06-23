#pragma once

#include "GObject.h"
#include "InputEventId.h"
#include "EventDispatchDelegate.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class AddOnceEventDispatch;
class MMouseOrTouch;

/**
 * @brief 鼠标分发系统
 */
class MMouseDispatch : public GObject
{
private:
	AddOnceEventDispatch* mOnMouseDownDispatch;
    AddOnceEventDispatch* mOnMouseUpDispatch;
    AddOnceEventDispatch* mOnMousePressDispatch;
    AddOnceEventDispatch* mOnMouseMoveDispatch;
    AddOnceEventDispatch* mOnMousePressMoveDispatch;
    AddOnceEventDispatch* mOnMouseCanceledDispatch;

public:
	MMouseDispatch();

	void init();
	void dispose();

	void addMouseListener(InputEventId evtId, EventDispatchDelegate handle);
	public void removeMouseListener(InputEventId evtId, EventDispatchDelegate handle);
    // 是否还有需要处理的事件
	bool hasEventHandle();

	void handleMouseDown(MMouseOrTouch* mouse);
	void handleMouseUp(MMouseOrTouch* mouse);
	void handleMousePress(MMouseOrTouch* mouse);
	void handleMousePressOrMove(MMouseOrTouch* mouse);
	void handleMousePressMove(MMouseOrTouch* mouse);
};

MY_END_NAMESPACE