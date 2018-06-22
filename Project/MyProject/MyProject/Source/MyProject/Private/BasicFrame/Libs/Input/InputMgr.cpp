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
	this->mPlayerInput = this->mPlayerController->PlayerInput;
}

void InputMgr::dispose()
{

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