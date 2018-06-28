#include "MyProject.h"
#include "InputKey.h"
#include "KeyId.h"
#include "AddOnceEventDispatch.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"
#include "Ctx.h"
#include "InputMgr.h"
#include "InputEventId.h"

MY_BEGIN_NAMESPACE(MyNS)

InputKey* InputKey::A = new InputKey(KeyId::A, EKeys::A, "A");
InputKey* InputKey::S = new InputKey(KeyId::S, EKeys::S, "S");
InputKey* InputKey::D = new InputKey(KeyId::D, EKeys::D, "D");
InputKey* InputKey::F = new InputKey(KeyId::F, EKeys::F, "F");

bool InputKey::msIsInit = false;

InputKey* InputKey::msInputKeyArray[(int)KeyId::Total];

InputKey** InputKey::getInputKeyArray()
{
	if (!InputKey::msIsInit)
	{
		InputKey::msIsInit = true;

		InputKey::msInputKeyArray[(int)KeyId::A] = InputKey::A;
		InputKey::msInputKeyArray[(int)KeyId::S] = InputKey::S;
		InputKey::msInputKeyArray[(int)KeyId::D] = InputKey::D;
		InputKey::msInputKeyArray[(int)KeyId::F] = InputKey::F;
	}

	return InputKey::msInputKeyArray;
}

std::string InputKey::codeToString(FKey value)
{
	//return InputKey::mInputKeyArray[(int)value].getKeyDesc();
	return "";
}

InputKey::InputKey(KeyId keyId, FKey keyCode, std::string keyDesc)
{
	this->mKeyId = keyId;
	this->mKeyCode = keyCode;
	this->mKeyDesc = keyDesc;

	this->mKeyState = false;
	this->mKeyStateOld = false;
	this->mJustPressed = false;
	this->mJustReleased = false;

	this->mOnKeyUpDispatch = MY_NEW AddOnceEventDispatch();
	this->mOnKeyDownDispatch = MY_NEW AddOnceEventDispatch();
	this->mOnKeyPressDispatch = MY_NEW AddOnceEventDispatch();
}

KeyId InputKey::getKeyId()
{
	return this->mKeyId;
}

FKey InputKey::getKeyCode()
{
	return this->mKeyCode;
}

std::string InputKey::getKeyDesc()
{
	return this->mKeyDesc;
}

void InputKey::onTick(float delta, TickMode tickMode)
{
	if (GInputMgr->getKeyDown(this->mKeyCode))
	{
		this->mKeyStateOld = this->mKeyState;
		this->mKeyState = true;

		if (this->mKeyStateOld != this->mKeyState)
		{
			this->mJustPressed = true;
			this->mJustReleased = false;
		}
		else
		{
			this->mJustPressed = false;
			this->mJustReleased = false;
		}

		if (this->mJustPressed)
		{
			this->_onKeyDown(this->mKeyCode);
		}
	}
	else if (GInputMgr->getKeyUp(this->mKeyCode))
	{
		this->mKeyStateOld = this->mKeyState;
		this->mKeyState = false;

		if (this->mKeyStateOld != this->mKeyState)
		{
			this->mJustPressed = false;
			this->mJustReleased = true;
		}
		else
		{
			this->mJustPressed = false;
			this->mJustReleased = false;
		}

		if (this->mJustReleased)
		{
			this->_onKeyUp(this->mKeyCode);
		}
	}

	// 一直按着
	if (GInputMgr->getKey(this->mKeyCode))
	{
		this->mKeyStateOld = this->mKeyState;
		this->mKeyState = true;
		this->mJustPressed = false;
		this->mJustReleased = false;

		this->_onKeyPress(this->mKeyCode);
	}
}

void InputKey::_onKeyDown(FKey keyCode)
{
	if (nullptr != this->mOnKeyDownDispatch)
	{
		this->mOnKeyDownDispatch->dispatchEvent(this);
	}
}

void InputKey::_onKeyUp(FKey keyCode)
{
	if (nullptr != this->mOnKeyUpDispatch)
	{
		this->mOnKeyUpDispatch->dispatchEvent(this);
	}
}

void InputKey::_onKeyPress(FKey keyCode)
{
	if (nullptr != this->mOnKeyPressDispatch)
	{
		this->mOnKeyPressDispatch->dispatchEvent(this);
	}
}

void InputKey::addKeyListener(InputEventId evtId, EventDispatchDelegate handle)
{
	if (InputEventId::KEYUP_EVENT == evtId)
	{
		this->mOnKeyUpDispatch->addEventHandle(handle);
	}
	else if (InputEventId::KEYDOWN_EVENT == evtId)
	{
		this->mOnKeyDownDispatch->addEventHandle(handle);
	}
	else if (InputEventId::KEYPRESS_EVENT == evtId)
	{
		this->mOnKeyPressDispatch->addEventHandle(handle);
	}
}

void InputKey::removeKeyListener(InputEventId evtId, EventDispatchDelegate handle)
{
	if (InputEventId::KEYUP_EVENT == evtId)
	{
		this->mOnKeyUpDispatch->removeEventHandle(handle);
	}
	else if (InputEventId::KEYDOWN_EVENT == evtId)
	{
		this->mOnKeyDownDispatch->removeEventHandle(handle);
	}
	else if (InputEventId::KEYPRESS_EVENT == evtId)
	{
		this->mOnKeyPressDispatch->removeEventHandle(handle);
	}
}

// 是否还有需要处理的事件
bool InputKey::hasEventHandle()
{
	bool ret = false;

	if (this->mOnKeyUpDispatch->hasEventHandle())
	{
		ret = true;
	}
	if (this->mOnKeyDownDispatch->hasEventHandle())
	{
		ret = true;
	}
	if (this->mOnKeyPressDispatch->hasEventHandle())
	{
		ret = true;
	}

	return ret;
}

bool InputKey::keyJustPressed()
{
	bool ret = false;

	if (GInputMgr->getKey(this->mKeyCode))
	{
		ret = true;
	}

	return false;
}

bool InputKey::keyJustReleased()
{
	bool ret = false;

	if (GInputMgr->getKeyUp(this->mKeyCode))
	{
		ret = true;
	}

	return ret;
}

bool InputKey::isKeyDown()
{
	bool ret = false;

	if (GInputMgr->getKeyDown(this->mKeyCode))
	{
		ret = true;
	}

	return ret;
}

MY_END_NAMESPACE