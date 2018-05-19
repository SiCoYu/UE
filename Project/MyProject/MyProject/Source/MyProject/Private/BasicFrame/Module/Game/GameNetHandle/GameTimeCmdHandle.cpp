#include "MyProject.h"
#include "GameTimeCmdHandle.h"
#include "EventDispatchDelegate.h"

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
			&GameTimeCmdHandle::onParamHandle
		)
	);
}

void GameTimeCmdHandle::dispose()
{
    this.removeParamHandle(
		0, 
		MakeEventDispatchDelegate(
			this, 
			&GameTimeCmdHandle::onParamHandle
		)
	);

	Super::dispose();
}

void GameTimeCmdHandle::onParamHandle(IDispatchObject* dispObj, uint uniqueId)
{

}