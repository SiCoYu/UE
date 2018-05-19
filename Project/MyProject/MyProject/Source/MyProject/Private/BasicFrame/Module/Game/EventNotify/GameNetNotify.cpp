#include "MyProject.h"
#include "GameNetNotify.h"
#include "SafePointer.h"		// SAFE_NEW

GameNetNotify::GameNetNotify()
{
            
}

void GameNetNotify::init()
{
    Super::init();

    this->mNetCmdDispatchHandle = SAFE_NEW GameTimeCmdHandle();
	this->mNetCmdDispatchHandle->init();
	this->addCmdHandle(
		stNullUserCmd.TIME_USERCMD, 
		this->mNetCmdDispatchHandle, 
		this->mNetCmdDispatchHandle.call
	);
}

void GameNetNotify::dispose()
{
    if (nullptr != this.mNetCmdDispatchHandle)
    {
		this->removeCmdHandle(
			stNullUserCmd.TIME_USERCMD, 
			this.mNetCmdDispatchHandle, 
			this.mNetCmdDispatchHandle.call);
		this->mNetCmdDispatchHandle.dispose();
		this->mNetCmdDispatchHandle = null;
    }

    Super::dispose();
}