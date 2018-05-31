#include "MyProject.h"
#include "GameTimeCmdHandle.h"
#include "EventDispatchDelegate.h"

MY_BEGIN_NAMESPACE(MyNS)

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
    this->removeParamHandle(
		0, 
		MakeEventDispatchDelegate(
			this, 
			&GameTimeCmdHandle::onParamHandle
		)
	);

	Super::dispose();
}

void GameTimeCmdHandle::onParamHandle(IDispatchObject* dispObj)
{

}

MY_END_NAMESPACE