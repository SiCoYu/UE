#include "MyProject.h"
#include "GameNetNotify.h"
#include "SafePointer.h"		// SAFE_NEW
#include "GameTimeCmdHandle.h"
#include "EventDispatchDelegate.h"
#include "stNullUserCmd.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"
#include "MyMemoryAlloc.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "MClassFactory.h"


M_IMPLEMENT_CLASS(GameNetNotify, NetModuleDispatchHandle)
M_REGISTER_CLASS(GameNetNotify)

GameNetNotify::GameNetNotify()
{
            
}

void GameNetNotify::init()
{
    Super::init();

    this->mNetCmdDispatchHandle = MY_NEW GameTimeCmdHandle();

	this->mNetCmdDispatchHandle->init();
	//this->addCmdHandle(
	//	NullUserCmdCV::TIME_USERCMD,
	//	MakeEventDispatchDelegate(
	//		this->mNetCmdDispatchHandle, 
	//		&NetCmdDispatchHandle::handleMsg
	//	)
	//);
}

void GameNetNotify::dispose()
{
	if (nullptr != this->mNetCmdDispatchHandle)
	{
		//this->removeCmdHandle(
		//	NullUserCmdCV::TIME_USERCMD,
		//	MakeEventDispatchDelegate(
		//		this->mNetCmdDispatchHandle,
		//		&NetCmdDispatchHandle::handleMsg
		//	)
		//);
		this->mNetCmdDispatchHandle->dispose();
		this->mNetCmdDispatchHandle = nullptr;
    }

    Super::dispose();
}