#include "MyProject.h"
#include "DelayPriorityHandleMgr.h"
#include "MyMemoryDefaultAlloc.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "NoPriorityList.h"
#include "MClassFactory.h"
#include "NoPriorityList.h"
#include "PriorityList.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(DelayPriorityHandleMgr, DelayNoOrPriorityHandleMgr)

DelayPriorityHandleMgr::DelayPriorityHandleMgr()
{
	this->mDeferredAddQueue = MY_NEW NoPriorityList();
	this->mDeferredAddQueue->setIsSpeedUpFind(true);
	this->mDeferredRemoveQueue = MY_NEW NoPriorityList();
	this->mDeferredRemoveQueue->setIsSpeedUpFind(true);

	this->mNoOrPriorityList = MY_NEW PriorityList();
	this->mNoOrPriorityList->setIsSpeedUpFind(true);
	this->mNoOrPriorityList->setIsOpKeepSort(true);
}

void DelayPriorityHandleMgr::init()
{
	Super::init();
}

void DelayPriorityHandleMgr::dispose()
{
	if (nullptr != this->mDeferredAddQueue)
	{
		this->mDeferredAddQueue->clear();
		MY_DELETE this->mDeferredAddQueue;
		this->mDeferredAddQueue = nullptr;
	}
	if (nullptr != this->mDeferredRemoveQueue)
	{
		this->mDeferredRemoveQueue->clear();
		MY_DELETE this->mDeferredRemoveQueue;
		this->mDeferredRemoveQueue = nullptr;
	}
	if (nullptr != this->mNoOrPriorityList)
	{
		this->mNoOrPriorityList->clear();
		MY_DELETE this->mNoOrPriorityList;
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