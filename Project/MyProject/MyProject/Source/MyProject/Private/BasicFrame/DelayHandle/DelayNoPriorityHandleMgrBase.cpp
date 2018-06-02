#include "MyProject.h"
#include "NullDelayHandleItem.h"

MY_BEGIN_NAMESPACE(MyNS)

DelayNoPriorityHandleMgrBase::DelayNoPriorityHandleMgrBase()
{
	this.mDeferredAddQueue = new NoPriorityList();
	this.mDeferredAddQueue.setIsSpeedUpFind(true);
	this.mDeferredDelQueue = new NoPriorityList();
	this.mDeferredDelQueue.setIsSpeedUpFind(true);
}

void DelayNoPriorityHandleMgrBase::init()
{
	Super::init();
}

void DelayNoPriorityHandleMgrBase::dispose()
{
	Super::dispose();
}

MY_END_NAMESPACE