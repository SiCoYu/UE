#include "MyProject.h"
#include "DelayPriorityHandleMgr.h"

MY_BEGIN_NAMESPACE(MyNS)

DelayPriorityHandleMgr::DelayPriorityHandleMgr()
{
	this->mDeferredAddQueue = new NoPriorityList();
	this->mDeferredAddQueue.setIsSpeedUpFind(true);
	this->mDeferredDelQueue = new NoPriorityList();
	this->mDeferredDelQueue.setIsSpeedUpFind(true);

	this->mNoOrPriorityList = new PriorityList();
	this->mNoOrPriorityList.setIsSpeedUpFind(true);
	this->mNoOrPriorityList.setIsOpKeepSort(true);
}

void DelayPriorityHandleMgr::init()
{
	Super::init();
}

void DelayPriorityHandleMgr::dispose()
{
	if (nullptr != this->mDeferredAddQueue)
	{
		this->mDeferredAddQueue.clear();
		this->mDeferredAddQueue = nullptr;
	}
	if (nullptr != this->mDeferredDelQueue)
	{
		this->mDeferredDelQueue.clear();
		this->mDeferredDelQueue = nullptr;
	}
	if (nullptr != this->mNoOrPriorityList)
	{
		this->mNoOrPriorityList.clear();
		this->mNoOrPriorityList = nullptr;
	}

	Super::dispose();
}

void DelayPriorityHandleMgr::addPriorityObject(INoOrPriorityObject* priorityObject, float priority)
{
	this->addNoOrPriorityObject(priorityObject, priority);
}

void DelayPriorityHandleMgr::removePriorityObject(ITickedObject* tickObj)
{
	this->removeNoOrPriorityObject(tickObj);
}

MY_END_NAMESPACE