#include "MyProject.h"
#include "NullDelayHandleItem.h"

MY_BEGIN_NAMESPACE(MyNS)

public DelayNoPriorityHandleMgrBase()
{
	this.mDeferredAddQueue = new NoPriorityList();
	this.mDeferredAddQueue.setIsSpeedUpFind(true);
	this.mDeferredDelQueue = new NoPriorityList();
	this.mDeferredDelQueue.setIsSpeedUpFind(true);
}

virtual void init() override
{
	Super::init();
}

virtual void dispose() override
{
	Super::dispose();
}

MY_END_NAMESPACE