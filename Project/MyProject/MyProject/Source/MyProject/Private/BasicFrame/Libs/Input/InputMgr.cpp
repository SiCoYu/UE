#include "MyProject.h"
#include "InputMgr.h"
#include "MyPlayerControllerBase.h"		// AMyPlayerControllerBase
#include "GameFramework/PlayerInput.h"	// UPlayerInput
#include "InputCoreTypes.h"		// FKey
#include "KeyState.h"	 // FKeyState

MY_BEGIN_NAMESPACE(MyNS)

InputMgr::InputMgr()
{
	mCurrentScheme = MControlScheme::Mouse;
	mCurrentTouchId = -1;

	this->mEventInputKeyList = new MList<InputKey>();
	this->mEventMouseList = new MList<MMouseDevice>();
	this->mHasAccelerationHandle = false;

	this->mOnTouchBeganDispatch = new AddOnceEventDispatch();
	this->mOnTouchMovedDispatch = new AddOnceEventDispatch();
	this->mOnTouchStationaryDispatch = new AddOnceEventDispatch();
	this->mOnTouchEndedDispatch = new AddOnceEventDispatch();
	this->mOnTouchCanceledDispatch = new AddOnceEventDispatch();

	this->mOnMultiTouchBeganDispatch = new AddOnceEventDispatch();
	this->mOnMultiTouchMovedDispatch = new AddOnceEventDispatch();
	this->mOnMultiTouchStationaryDispatch = new AddOnceEventDispatch();
	this->mOnMultiTouchEndedDispatch = new AddOnceEventDispatch();
	this->mOnMultiTouchCanceledDispatch = new AddOnceEventDispatch();

	this->mMouseDispatchArray = new MMouseDispatch[3];
	this->mMouseDispatchArray[0] = new MMouseDispatch();
	this->mMouseDispatchArray[1] = new MMouseDispatch();
	this->mMouseDispatchArray[2] = new MMouseDispatch();

	this->mMultiTouchSet = new MultiTouchSet();

	this->mMultiTouchEnabled = UnityEngine.Input.multiTouchEnabled;
	//this->mSimulateMouseWithTouches = UnityEngine.Input.simulateMouseWithTouches;
	this->mTouchSupported = UnityEngine.Input.touchSupported;
	this->mSimulateMouseWithTouches = true;
	//this->mMultiTouchEnabled = true;

	this->mOnDeviceOpDispatch = new AddOnceEventDispatch();
	this->mOnDeviceHomeDispatch = new AddOnceEventDispatch();
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

MY_END_NAMESPACE