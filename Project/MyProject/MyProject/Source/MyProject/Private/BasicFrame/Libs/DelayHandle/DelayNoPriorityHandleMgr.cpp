#include "MyProject.h"
#include "DelayNoPriorityHandleMgr.h"
#include "ITickedObject.h"
#include "INoOrPriorityObject.h"
#include "NoPriorityList.h"
#include "MyMemoryDefaultAlloc.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"

MY_BEGIN_NAMESPACE(MyNS)

DelayNoPriorityHandleMgr::DelayNoPriorityHandleMgr()
{
	this->mDeferredAddQueue = MY_NEW NoPriorityList();
	this->mDeferredAddQueue->setIsSpeedUpFind(true);
	this->mDeferredDelQueue = MY_NEW NoPriorityList();
	this->mDeferredDelQueue->setIsSpeedUpFind(true);

	this->mNoOrPriorityList = MY_NEW NoPriorityList();
	this->mNoOrPriorityList->setIsSpeedUpFind(true);
}

void DelayNoPriorityHandleMgr::init()
{
	Super::init();
}

void DelayNoPriorityHandleMgr::dispose()
{
	this->mDeferredAddQueue->clear();
	MY_DELETE this->mDeferredAddQueue;
	this->mDeferredAddQueue = nullptr;

	this->mDeferredDelQueue->clear();
	MY_DELETE this->mDeferredDelQueue;
	this->mDeferredDelQueue = nullptr;

	this->mNoOrPriorityList->clear();
	MY_DELETE this->mNoOrPriorityList;
	this->mNoOrPriorityList = nullptr;

	Super::dispose();
}

void DelayNoPriorityHandleMgr::addNoPriorityObject(INoOrPriorityObject* priorityObject)
{
	this->addNoOrPriorityObject(priorityObject);
}

void DelayNoPriorityHandleMgr::removeNoPriorityObject(ITickedObject* tickObj)
{
	this->removeNoOrPriorityObject(tickObj);
}

MY_END_NAMESPACE