#include "MyProject.h"
#include "DelayNoPriorityHandleMgrBase.h"
#include "NullDelayHandleItem.h"
#include "MyMemoryDefaultAlloc.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "NoPriorityList.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(DelayNoPriorityHandleMgrBase, DelayNoOrPriorityHandleMgrBase)

DelayNoPriorityHandleMgrBase::DelayNoPriorityHandleMgrBase()
{
	this->mDeferredAddQueue = MY_NEW NoPriorityList();
	this->mDeferredAddQueue->setIsSpeedUpFind(true);
	this->mDeferredRemoveQueue = MY_NEW NoPriorityList();
	this->mDeferredRemoveQueue->setIsSpeedUpFind(true);
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