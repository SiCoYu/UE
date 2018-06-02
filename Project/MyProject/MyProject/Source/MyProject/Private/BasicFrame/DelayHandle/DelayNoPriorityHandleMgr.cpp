#include "MyProject.h"
#include "DelayNoPriorityHandleMgr.h"

MY_BEGIN_NAMESPACE(MyNS)

DelayNoPriorityHandleMgr::DelayNoPriorityHandleMgr()
{
	this.mDeferredAddQueue = new NoPriorityList();
	this.mDeferredAddQueue.setIsSpeedUpFind(true);
	this.mDeferredDelQueue = new NoPriorityList();
	this.mDeferredDelQueue.setIsSpeedUpFind(true);

	this.mNoOrPriorityList = new NoPriorityList();
	this.mNoOrPriorityList.setIsSpeedUpFind(true);
}

void DelayNoPriorityHandleMgr::init()
{
	Super::init();
}

void DelayNoPriorityHandleMgr::dispose()
{
	this.mDeferredAddQueue.clear();
	this.mDeferredAddQueue = null;

	this.mDeferredDelQueue.clear();
	this.mDeferredDelQueue = null;

	this.mNoOrPriorityList.clear();
	this.mNoOrPriorityList = null;

	Super::dispose();
}

void DelayNoPriorityHandleMgr::addNoPriorityObject(INoOrPriorityObject priorityObject)
{
	this.addNoOrPriorityObject(priorityObject);
}

void DelayNoPriorityHandleMgr::removeNoPriorityObject(ITickedObject tickObj)
{
	this.removeNoOrPriorityObject(tickObj);
}

MY_END_NAMESPACE