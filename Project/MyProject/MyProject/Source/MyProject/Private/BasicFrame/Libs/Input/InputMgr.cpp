#include "MyProject.h"
#include "InputMgr.h"
#include "MDictionary.h"
#include "MyPlayerControllerBase.h"		// AMyPlayerControllerBase
#include "GameFramework/PlayerInput.h"	// UPlayerInput
#include "InputCoreTypes.h"		// FKey
#include "KeyState.h"	 // FKeyState

MY_BEGIN_NAMESPACE(MyNS)

InputMgr::InputMgr()
{

}

InputMgr::~InputMgr()
{

}

void InputMgr::init()
{
	
}

void InputMgr::dispose()
{

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