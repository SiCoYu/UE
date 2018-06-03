#include "MyProject.h"
#include "DelayPriorityHandleMgrBase.h"

MY_BEGIN_NAMESPACE(MyNS)

DelayPriorityHandleMgrBase::DelayPriorityHandleMgrBase()
{
	this->mDeferredAddQueue = new PriorityList();
	this->mDeferredAddQueue.setIsSpeedUpFind(true);
	this->mDeferredDelQueue = new PriorityList();
	this->mDeferredDelQueue.setIsSpeedUpFind(true);
}

void DelayPriorityHandleMgrBase::init()
{
	Super::init();
}

void DelayPriorityHandleMgrBase::dispose()
{
	if(nullptr != this->mDeferredAddQueue)
	{
		this->mDeferredAddQueue.dispose();
		this->mDeferredAddQueue = nullptr;
	}
	if (nullptr != this->mDeferredDelQueue)
	{
		this->mDeferredDelQueue.dispose();
		this->mDeferredDelQueue = nullptr;
	}

	Super::dispose();
}
	
MY_END_NAMESPACE