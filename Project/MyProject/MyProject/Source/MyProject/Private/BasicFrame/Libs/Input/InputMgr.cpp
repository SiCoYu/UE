#include "MyProject.h"
#include "InputMgr.h"
#include "MDictionary.h"
#include "MyPlayerControllerBase.h"		// AMyPlayerControllerBase
#include "GameFramework/PlayerInput.h"	// UPlayerInput

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

MY_END_NAMESPACE