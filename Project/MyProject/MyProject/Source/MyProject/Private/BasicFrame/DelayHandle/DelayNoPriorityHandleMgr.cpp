#include "MyProject.h"
#include "DelayNoPriorityHandleMgr.h"

MY_BEGIN_NAMESPACE(MyNS)

DelayNoPriorityHandleMgr()
{
	this.mDeferredAddQueue = new NoPriorityList();
	this.mDeferredAddQueue.setIsSpeedUpFind(true);
	this.mDeferredDelQueue = new NoPriorityList();
	this.mDeferredDelQueue.setIsSpeedUpFind(true);

	this.mNoOrPriorityList = new NoPriorityList();
	this.mNoOrPriorityList.setIsSpeedUpFind(true);
}

virtual void init() override
{
	base.init();
}

virtual void dispose() override
{
	this.mDeferredAddQueue.clear();
	this.mDeferredAddQueue = null;

	this.mDeferredDelQueue.clear();
	this.mDeferredDelQueue = null;

	this.mNoOrPriorityList.clear();
	this.mNoOrPriorityList = null;

	base.dispose();
}

void addNoPriorityObject(INoOrPriorityObject priorityObject)
{
	this.addNoOrPriorityObject(priorityObject);
}

void removeNoPriorityObject(ITickedObject tickObj)
{
	this.removeNoOrPriorityObject(tickObj);
}

MY_END_NAMESPACE