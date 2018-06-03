#include "MyProject.h"
#include "NullDelayHandleItem.h"
#include "MyMemoryDefaultAlloc.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "NoPriorityList.h"

MY_BEGIN_NAMESPACE(MyNS)

DelayNoPriorityHandleMgrBase::DelayNoPriorityHandleMgrBase()
{
	this->mDeferredAddQueue = MY_NEW NoPriorityList();
	this->mDeferredAddQueue->setIsSpeedUpFind(true);
	this->mDeferredDelQueue = MY_NEW NoPriorityList();
	this->mDeferredDelQueue->setIsSpeedUpFind(true);
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