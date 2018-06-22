#include "MyProject.h"
#include "InputKey.h"
#include "KeyId.h"
#include "AddOnceEventDispatch.h"
#include "InputCoreTypes.h"		// FKey

MY_BEGIN_NAMESPACE(MyNS)

InputKey* InputKey::None = new InputKey(KeyId.None, "None");
InputKey* InputKey::A = new InputKey(KeyId.A, "A");

InputKey* InputKey::mInputKeyArray[(int)KeyId::Total];

InputKey* InputKey::getInputKeyArray()
{
	if (InputKey::mInputKeyArray == nullptr)
	{
		InputKey::mInputKeyArray = new InputKey[(int)KeyCode.Joystick8Button19 + 1];
		InputKey::mInputKeyArray[(int)KeyCode.None] = None;
		InputKey::mInputKeyArray[(int)KeyCode.A] = A;
		InputKey::mInputKeyArray[(int)KeyCode.B] = B;
		InputKey::mInputKeyArray[(int)KeyCode.C] = C;
		InputKey::mInputKeyArray[(int)KeyCode.D] = D;
	}

	return InputKey::mInputKeyArray;
}

static std::string codeToString(KeyId value)
{
	return mInputKeyArray[(int)value].getKeyDesc();
}

InputKey::InputKey(FKey keyCode, std::string keyDesc)
{
	this.mKeyCode = keyCode;
	this.mKeyDesc = keyDesc;

	this.mKeyState = false;
	this.mKeyStateOld = false;
	this.mJustPressed = false;
	this.mJustReleased = false;

	this.mOnKeyUpDispatch = new AddOnceEventDispatch();
	this.mOnKeyDownDispatch = new AddOnceEventDispatch();
	this.mOnKeyPressDispatch = new AddOnceEventDispatch();
}

KeyCode InputKey::getKeyCode()
{
	return mKeyCode;
}

std::string InputKey::getKeyDesc()
{
	return mKeyDesc;
}

void InputKey::onTick(float delta, TickMode tickMode)
{
	if (Input.GetKeyDown(this.mKeyCode))
	{
		this._onKeyDown(this.mKeyCode);
	}

	if (Input.GetKeyUp(this.mKeyCode))
	{
		this._onKeyUp(this.mKeyCode);
	}

	if (Input.GetKey(this.mKeyCode))
	{
		this._onKeyPress(this.mKeyCode);
	}
}

void InputKey::_onKeyDown(KeyCode keyCode)
{
	if (nullptr != this.mOnKeyDownDispatch)
	{
		this.mOnKeyDownDispatch.dispatchEvent(this);
	}
}

void InputKey::_onKeyUp(KeyCode keyCode)
{
	if (null != this.mOnKeyUpDispatch)
	{
		this.mOnKeyUpDispatch.dispatchEvent(this);
	}
}

void InputKey::_onKeyPress(KeyCode keyCode)
{
	if (null != this.mOnKeyPressDispatch)
	{
		this.mOnKeyPressDispatch.dispatchEvent(this);
	}
}

void InputKey::addKeyListener(EventId evtId, EventDispatchDelegate handle)
{
	if (EventId.KEYUP_EVENT == evtID)
	{
		mOnKeyUpDispatch.addEventHandle(null, handle);
	}
	else if (EventId.KEYDOWN_EVENT == evtID)
	{
		mOnKeyDownDispatch.addEventHandle(null, handle);
	}
	else if (EventId.KEYPRESS_EVENT == evtID)
	{
		mOnKeyPressDispatch.addEventHandle(null, handle);
	}
}

void InputKey::removeKeyListener(EventId evtID, EventDispatchDelegate handle)
{
	if (EventId.KEYUP_EVENT == evtID)
	{
		mOnKeyUpDispatch.removeEventHandle(null, handle);
	}
	else if (EventId.KEYDOWN_EVENT == evtID)
	{
		mOnKeyDownDispatch.removeEventHandle(null, handle);
	}
	else if (EventId.KEYPRESS_EVENT == evtID)
	{
		mOnKeyPressDispatch.removeEventHandle(null, handle);
	}
}

// 是否还有需要处理的事件
bool InputKey::hasEventHandle()
{
	if (this.mOnKeyUpDispatch.hasEventHandle())
	{
		return true;
	}
	if (this.mOnKeyDownDispatch.hasEventHandle())
	{
		return true;
	}
	if (this.mOnKeyPressDispatch.hasEventHandle())
	{
		return true;
	}

	return false;
}

bool InputKey::keyJustPressed()
{
	if (Input.GetKey(this.mKeyCode))
	{
		return true;
	}

	return false;
}

bool InputKey::keyJustReleased()
{
	if (Input.GetKeyUp(this.mKeyCode))
	{
		return true;
	}

	return false;
}

bool InputKey::isKeyDown()
{
	if (Input.GetKeyDown(this.mKeyCode))
	{
		return true;
	}

	return false;
}

MY_END_NAMESPACE