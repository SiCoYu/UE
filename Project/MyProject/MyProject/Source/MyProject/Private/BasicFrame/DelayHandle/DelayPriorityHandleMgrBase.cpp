#include "MyProject.h"
#include "DelayPriorityHandleMgrBase.h"

MY_BEGIN_NAMESPACE(MyNS)

DelayPriorityHandleMgrBase::DelayPriorityHandleMgrBase()
{
	this.mDeferredAddQueue = new PriorityList();
	this.mDeferredAddQueue.setIsSpeedUpFind(true);
	this.mDeferredDelQueue = new PriorityList();
	this.mDeferredDelQueue.setIsSpeedUpFind(true);
}

void DelayPriorityHandleMgrBase::init()
{
	Super::init();
}

void DelayPriorityHandleMgrBase::dispose()
{
	if(null != this.mDeferredAddQueue)
	{
		this.mDeferredAddQueue.dispose();
		this.mDeferredAddQueue = null;
	}
	if (null != this.mDeferredDelQueue)
	{
		this.mDeferredDelQueue.dispose();
		this.mDeferredDelQueue = null;
	}

	Super::dispose();
}
	
MY_END_NAMESPACE