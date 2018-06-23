#include "MyProject.h"
#include "MMouseDispatch.h"
#include "MMouseOrTouch.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"
#include "AddOnceEventDispatch.h"

MY_BEGIN_NAMESPACE(MyNS)

MMouseDispatch::MMouseDispatch()
{
	this->mOnMouseDownDispatch = MY_NEW AddOnceEventDispatch();
	this->mOnMouseUpDispatch = MY_NEW AddOnceEventDispatch();
	this->mOnMousePressDispatch = MY_NEW AddOnceEventDispatch();
	this->mOnMouseMoveDispatch = MY_NEW AddOnceEventDispatch();
	this->mOnMousePressMoveDispatch = MY_NEW AddOnceEventDispatch();
	this->mOnMouseCanceledDispatch = MY_NEW AddOnceEventDispatch();
}

void MMouseDispatch::init()
{

}

void MMouseDispatch::dispose()
{

}

void MMouseDispatch::addMouseListener(InputEventId evtId, EventDispatchDelegate handle)
{
	if (InputEventId::MOUSEDOWN_EVENT == evtId)
	{
		this->mOnMouseDownDispatch->addEventHandle(handle);
	}
	else if (InputEventId::MOUSEUP_EVENT == evtId)
	{
		this->mOnMouseUpDispatch->addEventHandle(handle);
	}
	else if (InputEventId::MOUSEPRESS_EVENT == evtId)
	{
		this->mOnMousePressDispatch->addEventHandle(handle);
	}
	else if (InputEventId::MOUSEMOVE_EVENT == evtId)
	{
		this->mOnMouseMoveDispatch->addEventHandle(handle);
	}
	else if (InputEventId::MOUSEPRESS_MOVE_EVENT == evtId)
	{
		this->mOnMousePressMoveDispatch->addEventHandle(handle);
	}
}

void MMouseDispatch::removeMouseListener(InputEventId evtId, EventDispatchDelegate handle)
{
	if (InputEventId::KEYUP_EVENT == evtId)
	{
		this->mOnMouseDownDispatch->removeEventHandle(handle);
	}
	else if (InputEventId::KEYDOWN_EVENT == evtId)
	{
		this->mOnMouseUpDispatch->removeEventHandle(handle);
	}
	else if (InputEventId::KEYPRESS_EVENT == evtId)
	{
		this->mOnMousePressDispatch->removeEventHandle(handle);
	}
	else if (InputEventId::MOUSEMOVE_EVENT == evtId)
	{
		this->mOnMouseMoveDispatch->removeEventHandle(handle);
	}
	else if (InputEventId::MOUSEPRESS_MOVE_EVENT == evtId)
	{
		this->mOnMousePressMoveDispatch->removeEventHandle(handle);
	}
}

// 是否还有需要处理的事件
bool MMouseDispatch::hasEventHandle()
{
	bool ret = false;

	if (this->mOnMouseDownDispatch->hasEventHandle())
	{
		ret = true;
	}
	if (this->mOnMouseUpDispatch->hasEventHandle())
	{
		ret = true;
	}
	if (this->mOnMousePressDispatch->hasEventHandle())
	{
		ret = true;
	}
	if (this->mOnMousePressMoveDispatch->hasEventHandle())
	{
		ret = true;
	}

	return ret;
}

void MMouseDispatch::handleMouseDown(MMouseOrTouch* mouse)
{
	if (nullptr != this->mOnMouseDownDispatch)
	{
		this->mOnMouseDownDispatch->dispatchEvent(mouse);
	}
}

void MMouseDispatch::handleMouseUp(MMouseOrTouch* mouse)
{
	if (nullptr != this->mOnMouseUpDispatch)
	{
		this->mOnMouseUpDispatch->dispatchEvent(mouse);
	}
}

void MMouseDispatch::handleMousePress(MMouseOrTouch* mouse)
{
	if (nullptr != this->mOnMousePressDispatch)
	{
		this->mOnMousePressDispatch->dispatchEvent(mouse);
	}
}

void MMouseDispatch::handleMousePressOrMove(MMouseOrTouch* mouse)
{
	if (nullptr != this->mOnMouseMoveDispatch)
	{
		this->mOnMouseMoveDispatch->dispatchEvent(mouse);
	}
}

void MMouseDispatch::handleMousePressMove(MMouseOrTouch* mouse)
{
	if (nullptr != this->mOnMousePressMoveDispatch)
	{
		this->mOnMousePressMoveDispatch->dispatchEvent(mouse);
	}
}

MY_END_NAMESPACE