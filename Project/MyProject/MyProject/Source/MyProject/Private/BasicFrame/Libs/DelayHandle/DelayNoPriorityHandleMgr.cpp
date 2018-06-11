#include "MyProject.h"
#include "DelayNoPriorityHandleMgr.h"
#include "ITickedObject.h"
#include "INoOrPriorityObject.h"
#include "NoPriorityList.h"
#include "MyMemoryDefaultAlloc.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MClassFactory.h"
#include "SafePointer.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(DelayNoPriorityHandleMgr, DelayNoOrPriorityHandleMgr)

DelayNoPriorityHandleMgr::DelayNoPriorityHandleMgr()
{
	this->mDeferredAddQueue = MY_NEW NoPriorityList();
	this->mDeferredAddQueue->setIsSpeedUpFind(true);
	this->mDeferredRemoveQueue = MY_NEW NoPriorityList();
	this->mDeferredRemoveQueue->setIsSpeedUpFind(true);

	this->mNoOrPriorityList = MY_NEW NoPriorityList();
	this->mNoOrPriorityList->setIsSpeedUpFind(true);
}

void DelayNoPriorityHandleMgr::init()
{
	Super::init();
}

void DelayNoPriorityHandleMgr::dispose()
{
	GObject* tmp = nullptr;

	tmp = (GObject*)this->mDeferredAddQueue;
	MY_SAFE_DISPOSE(tmp);
	this->mDeferredAddQueue = nullptr;

	tmp = (GObject*)this->mDeferredRemoveQueue;
	MY_SAFE_DISPOSE(tmp);
	this->mDeferredRemoveQueue = nullptr;

	tmp = (GObject*)this->mNoOrPriorityList;
	MY_SAFE_DISPOSE(tmp);
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