#include "MyProject.h"
#include "InputMgr.h"
#include "MyPlayerControllerBase.h"		// AMyPlayerControllerBase
#include "GameFramework/PlayerInput.h"	// UPlayerInput
#include "InputCoreTypes.h"		// FKey
#include "KeyState.h"			// FKeyState
#include "MMouseOrTouch.h"
#include "AddOnceEventDispatch.h"
#include "MMouseDispatch.h"
#include "MultiTouchSet.h"
#include "InputKey.h"
#include "AddOnceEventDispatch.h"
#include "MMouseDeviceType.h"
#include "UtilMath.h"

MY_BEGIN_NAMESPACE(MyNS)

InputMgr::InputMgr()
{
	mCurrentScheme = MControlScheme::Mouse;
	mCurrentTouchId = -1;

	this->mHasAccelerationHandle = false;

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

	this->mMouseDispatchArray[0] = MY_NEW MMouseDispatch();
	this->mMouseDispatchArray[1] = MY_NEW MMouseDispatch();
	this->mMouseDispatchArray[2] = MY_NEW MMouseDispatch();

	this->mMultiTouchSet = MY_NEW MultiTouchSet();

	this->mMultiTouchEnabled = UnityEngine.Input.multiTouchEnabled;
	//this->mSimulateMouseWithTouches = UnityEngine.Input.simulateMouseWithTouches;
	this->mTouchSupported = UnityEngine.Input.touchSupported;
	this->mSimulateMouseWithTouches = true;
	//this->mMultiTouchEnabled = true;

	this->mOnDeviceOpDispatch = MY_NEW AddOnceEventDispatch();
	this->mOnDeviceHomeDispatch = MY_NEW AddOnceEventDispatch();
}

InputMgr::~InputMgr()
{

}

void InputMgr::init()
{
	InputKey.getInputKeyArray();
	this->mMouseDispatchArray[0].init();
	this->mMouseDispatchArray[1].init();
	this->mMouseDispatchArray[2].init();
}

void InputMgr::dispose()
{
	this->mMouseDispatchArray[0].dispose();
	this->mMouseDispatchArray[1].dispose();
	this->mMouseDispatchArray[2].dispose();
}

void InputMgr::setPlayerController(AMyPlayerControllerBase* value)
{
	this->mPlayerController = value;
	this->mPlayerInput = this->mPlayerController->PlayerInput;
}

void InputMgr::setPlayerInput(UPlayerInput* value)
{
	this->mPlayerInput = value;
}

bool InputMgr::getKeyDown(FKey keyCode)
{
	return this->mPlayerInput->GetKeyState(keyCode)->bDown;
}

bool InputMgr::getKeyUp(FKey keyCode)
{
	return !this->mPlayerInput->GetKeyState(keyCode)->bDown;
}

bool InputMgr::getKey(FKey keyCode)
{
	return !this->mPlayerInput->IsPressed(keyCode);
}

bool InputMgr::GetMouseButtonDown(int mouseIndex)
{
	bool ret = false;

	if ((int)MMouseDeviceType::eMouseLeftButton == mouseIndex)
	{
		ret = this->mPlayerInput->GetKeyState(EKeys::LeftMouseButton)->bDown;
	}
	else if ((int)MMouseDeviceType::eMouseRightButton == mouseIndex)
	{
		ret = this->mPlayerInput->GetKeyState(EKeys::RightMouseButton)->bDown;
	}
	else if ((int)MMouseDeviceType::eMouseMiddleButton == mouseIndex)
	{
		ret = this->mPlayerInput->GetKeyState(EKeys::MiddleMouseButton)->bDown;
	}

	return ret;
}

bool InputMgr::GetMouseButtonUp(int mouseIndex)
{
	bool ret = false;

	if ((int)MMouseDeviceType::eMouseLeftButton == mouseIndex)
	{
		ret = !this->mPlayerInput->GetKeyState(EKeys::LeftMouseButton)->bDown;
	}
	else if ((int)MMouseDeviceType::eMouseRightButton == mouseIndex)
	{
		ret = !this->mPlayerInput->GetKeyState(EKeys::RightMouseButton)->bDown;
	}
	else if ((int)MMouseDeviceType::eMouseMiddleButton == mouseIndex)
	{
		ret = !this->mPlayerInput->GetKeyState(EKeys::MiddleMouseButton)->bDown;
	}

	return ret;
}

bool InputMgr::GetMouseButton(int mouseIndex)
{
	bool ret = false;

	if ((int)MMouseDeviceType::eMouseLeftButton == mouseIndex)
	{
		ret = this->mPlayerInput->IsPressed(EKeys::LeftMouseButton);
	}
	else if ((int)MMouseDeviceType::eMouseRightButton == mouseIndex)
	{
		ret = this->mPlayerInput->IsPressed(EKeys::RightMouseButton);
	}
	else if ((int)MMouseDeviceType::eMouseMiddleButton == mouseIndex)
	{
		ret = this->mPlayerInput->IsPressed(EKeys::MiddleMouseButton);
	}

	return ret;
}

FVector InputMgr::GetMousePosition()
{
	FVector ret = UtilMath::ZeroVec3;

	if ((int)MMouseDeviceType::eMouseLeftButton == mouseIndex)
	{
		ret = this->mPlayerInput->GetKeyState(EKeys::LeftMouseButton)->Value;
	}
	else if ((int)MMouseDeviceType::eMouseRightButton == mouseIndex)
	{
		ret = this->mPlayerInput->GetKeyState(EKeys::RightMouseButton)->Value;
	}
	else if ((int)MMouseDeviceType::eMouseMiddleButton == mouseIndex)
	{
		ret = this->mPlayerInput->GetKeyState(EKeys::MiddleMouseButton)->Value;
	}

	return ret;

	return 
}

void InputMgr::onTick(float delta, TickMode tickMode)
{
	int index = 0;

	for (index = 0; index < this->mEventInputKeyList.count(); index++)
	{
		this->mEventInputKeyList[index]->onTick(delta, tickMode);
	}

	for (index = 0; index < this->mEventMouseList.count(); index++)
	{
		this->mEventMouseList[index]->onTick(delta, tickMode);
	}

	this->ProcessTouches(delta, tickMode);

	//if (this->mHasAccelerationHandle)
	//{
	//	MAcceleration::mAccelerationOne->onTick(delta, tickMode);
	//}
}

bool InputMgr::keyJustPressed(InputKey* inputKey)
{
	return inputKey->keyJustPressed();
}

bool InputMgr::keyJustReleased(InputKey* inputKey)
{
	return inputKey->keyJustReleased();
}

bool InputMgr::isKeyDown(InputKey* inputKey)
{
	return inputKey->isKeyDown();
}

bool InputMgr::isAnyKeyDown()
{
	int index = 0;
	int listLen = (int)KeyId::Total;
	InputKey* inputKey = nullptr;
	bool ret = false;

	while (index < listLen)
	{
		inputKey = InputKey::mInputKeyArray[index];

		if (nullptr != inputKey)
		{
			ret = inputKey->mKeyState;
			break;
		}

		index += 1;
	}

	return ret;
}

// 添加 KeyInput 输入事件
void InputMgr::addKeyListener(InputKey* inputKey, InputEventId evtId, EventDispatchDelegate handle)
{
	inputKey->addKeyListener(evtId, handle);

	this->addEventInputKey(inputKey);
}

// 移除键盘 KeyInput 输入事件
void InputMgr::removeKeyListener(InputKey* inputKey, InputEventId evtId, EventDispatchDelegate handle)
{
	inputKey->removeKeyListener(evtId, handle);

	if (!inputKey->hasEventHandle())
	{
		this->removeEventInputKey(inputKey);
	}
}

// 添加鼠标监听器
void InputMgr::addMouseListener(MMouseDevice* mouse, InputEventId evtId, EventDispatchDelegate handle)
{
	this->mMouseDispatchArray[mouse.mTouchIndex].addMouseListener(evtId, handle);
	this->addEventMouse(mouse);
}

// 移除鼠标监听器
void InputMgr::removeMouseListener(MMouseDevice* mouse, InputEventId evtId, EventDispatchDelegate handle)
{
	this->mMouseDispatchArray[mouse.mTouchIndex].removeMouseListener(evtId, handle);

	if (!this->hasEventHandle(mouse))
	{
		this->removeEventMouse(mouse);
	}
}

void InputMgr::addTouchListener(InputEventId evtId, EventDispatchDelegate handle)
{
	if (InputEventId::TOUCHBEGIN_EVENT == evtId)
	{
		this->mOnTouchBeganDispatch->addEventHandle(nullptr, handle);
	}
	else if (InputEventId::TOUCHMOVED_EVENT == evtId)
	{
		this->mOnTouchMovedDispatch.addEventHandle(nullptr, handle);
	}
	else if (InputEventId::TOUCHSTATIONARY_EVENT == evtId)
	{
		this->mOnTouchStationaryDispatch.addEventHandle(nullptr, handle);
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

	if (!this->mTouchSupported)
	{
		if (this->mSimulateMouseWithTouches)
		{
			this->addEventMouse(MMouseDevice::MouseLeftButton);
		}
	}
}

void InputMgr::removeTouchListener(InputEventId evtId, EventDispatchDelegate handle)
{
	if (InputEventId::TOUCHBEGIN_EVENT == evtId)
	{
		this->mOnTouchBeganDispatch->removeEventHandle(nullptr, handle);
	}
	else if (InputEventId::TOUCHMOVED_EVENT == evtId)
	{
		this->mOnTouchMovedDispatch.removeEventHandle(nullptr, handle);
	}
	else if (InputEventId::TOUCHSTATIONARY_EVENT == evtId)
	{
		this->mOnTouchStationaryDispatch.removeEventHandle(nullptr, handle);
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

	if (!this->mTouchSupported && !this->mHasTouch)
	{
		if (this->mSimulateMouseWithTouches)
		{
			this->mHasMultiTouch = this->hasMultiEventHandle();

			if (!this->mHasMultiTouch)
			{
				this->removeEventMouse(MMouseDevice::MouseLeftButton);
			}
		}
	}
}

void InputMgr::addMultiTouchListener(InputEventId evtId, EventDispatchDelegate handle)
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

	if (!this->mTouchSupported)
	{
		if (this->mSimulateMouseWithTouches)
		{
			this->addEventMouse(MMouseDevice::MouseLeftButton);
		}
	}
}

void InputMgr::removeMultiTouchListener(InputEventId evtId, EventDispatchDelegate handle)
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

	if (!this->mTouchSupported && !this->mHasMultiTouch)
	{
		if (this->mSimulateMouseWithTouches)
		{
			this->mHasTouch = this->hasEventHandle();

			if (!this->mHasTouch)
			{
				this->removeEventMouse(MMouseDevice::MouseLeftButton);
			}
		}
	}
}

void InputMgr::addAccelerationListener(InputEventId evtId, EventDispatchDelegate handle)
{
	//MAcceleration.mAccelerationOne.addAccelerationListener(evtId, handle);
	//this->mHasAccelerationHandle = true;
}

void InputMgr::removeAccelerationListener(InputEventId evtId, EventDispatchDelegate handle)
{
	//MAcceleration.mAccelerationOne.removeAccelerationListener(evtId, handle);
	//if (!MAcceleration.mAccelerationOne.hasEventHandle())
	//{
	//	this->mHasAccelerationHandle = false;
	//}
}

void InputMgr::_addEventInputKey(InputKey* inputKey)
{
	if (-1 == this->mEventInputKeyList.indexOf(inputKey))
	{
		this->mEventInputKeyList.add(inputKey);
	}
}

void InputMgr::_removeEventInputKey(InputKey* inputKey)
{
	if (-1 != this->mEventInputKeyList.indexOf(inputKey))
	{
		this->mEventInputKeyList.remove(inputKey);
	}
}

void InputMgr::_addEventMouse(MMouseDevice* mouse)
{
	if (-1 == this->mEventMouseList.indexOf(mouse))
	{
		this->mEventMouseList.add(mouse);
	}
}

void InputMgr::_removeEventMouse(MMouseDevice* mouse)
{
	if (-1 != this->mEventMouseList.indexOf(mouse))
	{
		this->mEventMouseList.remove(mouse);
	}
}

void InputMgr::ProcessTouches(float delta, TickMode tickMode)
{
	if (this->hasTouch() || this->hasMultiTouch())
	{
		this->mMultiTouchSet.reset();

		this->mCurrentScheme = MControlScheme.Touch;

		int index = 0;

		while (index < UnityEngine.Input.touchCount)
		{
			UnityEngine.Touch touch = UnityEngine.Input.GetTouch(index);

			this->mCurrentTouchId = this->mMultiTouchEnabled ? touch.fingerId : 0;
			this->mCurrentTouch = MTouchDevice::GetTouch(this->mCurrentTouchId);

			this->mCurrentTouch->setNativeTouch(touch, this->mCurrentTouchId);
			this->mCurrentTouch->onTick(delta, tickMode);

			if (this->hasMultiTouch())
			{
				this->mMultiTouchSet->addTouch(this->mCurrentTouch);
			}

			++index;
		}

		if (this->hasMultiTouch())
		{
			this->mMultiTouchSet->onTick(delta, tickMode);
		}
	}
}

// 是否还有需要处理的事件
bool InputMgr::hasEventHandle()
{
	bool ret = false;

	if (this->mOnTouchBeganDispatch->hasEventHandle())
	{
		ret = true;
	}
	if (this->mOnTouchMovedDispatch.hasEventHandle())
	{
		ret = true;
	}
	if (this->mOnTouchStationaryDispatch.hasEventHandle())
	{
		ret = true;
	}
	if (this->mOnTouchEndedDispatch->hasEventHandle())
	{
		ret = true;
	}
	if (this->mOnTouchCanceledDispatch->hasEventHandle())
	{
		ret = true;
	}

	return ret;
}

bool InputMgr::hasTouch()
{
	return this->mHasTouch;
}

void InputMgr::handleTouchBegan(MMouseOrTouch* touch)
{
	if (nullptr != this->mOnTouchBeganDispatch)
	{
		this->mOnTouchBeganDispatch->dispatchEvent(touch);
	}
}

void InputMgr::handleTouchMoved(MMouseOrTouch* touch)
{
	if (nullptr != this->mOnTouchMovedDispatch)
	{
		this->mOnTouchMovedDispatch.dispatchEvent(touch);
	}
}

void InputMgr::handleTouchStationary(MMouseOrTouch* touch)
{
	if (nullptr != this->mOnTouchStationaryDispatch)
	{
		this->mOnTouchStationaryDispatch.dispatchEvent(touch);
	}
}

void InputMgr::handleTouchEnded(MMouseOrTouch* touch)
{
	if (nullptr != this->mOnTouchEndedDispatch)
	{
		this->mOnTouchEndedDispatch->dispatchEvent(touch);
	}
}

void InputMgr::handleTouchCanceled(MMouseOrTouch* touch)
{
	if (nullptr != this->mOnTouchCanceledDispatch)
	{
		this->mOnTouchCanceledDispatch->dispatchEvent(touch);
	}
}

/********************************** Multi Touch *********************************/
// 是否还有需要处理的事件
bool InputMgr::hasMultiEventHandle()
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

bool InputMgr::hasMultiTouch()
{
	return this->mHasMultiTouch;
}

void InputMgr::handleMultiTouchBegan(IDispatchObject* touch)
{
	if (nullptr != this->mOnMultiTouchBeganDispatch)
	{
		this->mOnMultiTouchBeganDispatch->dispatchEvent(touch);
	}
}

void InputMgr::handleMultiTouchMoved(IDispatchObject* touch)
{
	if (nullptr != this->mOnMultiTouchMovedDispatch)
	{
		this->mOnMultiTouchMovedDispatch->dispatchEvent(touch);
	}
}

void InputMgr::handleMultiTouchStationary(IDispatchObject* touch)
{
	if (nullptr != this->mOnMultiTouchStationaryDispatch)
	{
		this->mOnMultiTouchStationaryDispatch->dispatchEvent(touch);
	}
}

void InputMgr::handleMultiTouchEnded(IDispatchObject* touch)
{
	if (nullptr != this->mOnMultiTouchEndedDispatch)
	{
		this->mOnMultiTouchEndedDispatch->dispatchEvent(touch);
	}
}

void InputMgr::handleMultiTouchCanceled(IDispatchObject* touch)
{
	if (nullptr != this->mOnMultiTouchCanceledDispatch)
	{
		this->mOnMultiTouchCanceledDispatch->dispatchEvent(touch);
	}
}

/******************* Mouse Dispatch *********************/
// 是否还有需要处理的事件
bool InputMgr::hasEventHandle(MMouseDevice* mouse)
{
	return this->mMouseDispatchArray[mouse->mTouchIndex]->hasEventHandle();
}

void InputMgr::handleMouseDown(MMouseOrTouch* mouse)
{
	this->mMouseDispatchArray[mouse->mTouchIndex]->handleMouseDown(mouse);
}

void InputMgr::handleMouseUp(MMouseOrTouch* mouse)
{
	this->mMouseDispatchArray[mouse->mTouchIndex]->handleMouseUp(mouse);
}

void InputMgr::handleMousePress(MMouseOrTouch* mouse)
{
	this->mMouseDispatchArray[mouse->mTouchIndex]->handleMousePress(mouse);
}

void InputMgr::handleMousePressOrMove(MMouseOrTouch* mouse)
{
	this->mMouseDispatchArray[mouse->mTouchIndex]->handleMousePressOrMove(mouse);
}

void InputMgr::handleMousePressMove(MMouseOrTouch* mouse)
{
	this->mMouseDispatchArray[mouse->mTouchIndex]->handleMousePressMove(mouse);
}

MY_END_NAMESPACE