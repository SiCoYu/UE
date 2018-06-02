#include "MyProject.h"
#include "DelayPriorityHandleMgr.h"

MY_BEGIN_NAMESPACE(MyNS)

DelayPriorityHandleMgr()
{
	this.mDeferredAddQueue = new NoPriorityList();
	this.mDeferredAddQueue.setIsSpeedUpFind(true);
	this.mDeferredDelQueue = new NoPriorityList();
	this.mDeferredDelQueue.setIsSpeedUpFind(true);

	this.mNoOrPriorityList = new PriorityList();
	this.mNoOrPriorityList.setIsSpeedUpFind(true);
	this.mNoOrPriorityList.setIsOpKeepSort(true);
}

virtual void init() override
{
	Super::init();
}

virtual void dispose() override
{
	if (null != this.mDeferredAddQueue)
	{
		this.mDeferredAddQueue.clear();
		this.mDeferredAddQueue = null;
	}
	if (null != this.mDeferredDelQueue)
	{
		this.mDeferredDelQueue.clear();
		this.mDeferredDelQueue = null;
	}
	if (null != this.mNoOrPriorityList)
	{
		this.mNoOrPriorityList.clear();
		this.mNoOrPriorityList = null;
	}

	Super::dispose();
}

void addPriorityObject(INoOrPriorityObject priorityObject, float priority = 0.0f)
{
	this.addNoOrPriorityObject(priorityObject, priority);
}

void removePriorityObject(ITickedObject tickObj)
{
	this.removeNoOrPriorityObject(tickObj);
}

MY_END_NAMESPACE