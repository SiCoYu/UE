#include "MyProject.h"
#include "GameTimeCmdHandle.h"
#include "EventDispatchDelegate.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(GameTimeCmdHandle, NetCmdDispatchHandle)

GameTimeCmdHandle::GameTimeCmdHandle()
{

}

void GameTimeCmdHandle::init()
{
    Super::init();

    this->addParamHandle(
		0, 
		MakeEventDispatchDelegate(
			this, 
			&GameTimeCmdHandle::onParamHandle, 
			(uint)0
		)
	);
}

void GameTimeCmdHandle::dispose()
{
    this->removeParamHandle(
		0, 
		MakeEventDispatchDelegate(
			this, 
			&GameTimeCmdHandle::onParamHandle, 
			(uint)0
		)
	);

	Super::dispose();
}

void GameTimeCmdHandle::onParamHandle(uint eventId, IDispatchObject* dispObj)
{

}

MY_END_NAMESPACE