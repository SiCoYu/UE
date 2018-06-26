#include "MyProject.h"
#include "GameNetNotify.h"
#include "SafePointer.h"		// SAFE_NEW
#include "GameTimeCmdHandle.h"
#include "EventDispatchDelegate.h"
#include "NullUserCmd.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"
#include "MyMemoryAlloc.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "MClassFactory.h"
#include "Ctx.h"
#include "NetCmdNotify.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(GameNetNotify, NetModuleDispatchHandle)

GameNetNotify::GameNetNotify()
{
            
}

void GameNetNotify::init()
{
    Super::init();

    this->mNetCmdDispatchHandle = MY_NEW GameTimeCmdHandle();

	this->mNetCmdDispatchHandle->init();

	NetCmdDispatchHandle* tmp = (NetCmdDispatchHandle*)this->mNetCmdDispatchHandle;

	this->addCmdHandle(
		(uint8)NullUserCmdCV::TIME_USERCMD,
		MakeEventDispatchDelegate(
			tmp,
			&NetCmdDispatchHandle::handleMsg, 
			(uint)0
		)
	);

	GNetCmdNotify->addOneNofity(this);
}

void GameNetNotify::dispose()
{
	if (nullptr != this->mNetCmdDispatchHandle)
	{
		NetCmdDispatchHandle* tmp = (NetCmdDispatchHandle*)this->mNetCmdDispatchHandle;

		this->removeCmdHandle(
			(uint8)NullUserCmdCV::TIME_USERCMD,
			MakeEventDispatchDelegate(
				tmp,
				&NetCmdDispatchHandle::handleMsg, 
				(uint)0
			)
		);

		this->mNetCmdDispatchHandle->dispose();
		this->mNetCmdDispatchHandle = nullptr;
    }

    Super::dispose();

	GNetCmdNotify->removeOneNofity(this);
}

MY_END_NAMESPACE