#include "MyProject.h"
#include "DelayPriorityHandleMgrBase.h"
#include "MyMemoryDefaultAlloc.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "PriorityList.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(DelayPriorityHandleMgrBase, DelayNoOrPriorityHandleMgrBase)

DelayPriorityHandleMgrBase::DelayPriorityHandleMgrBase()
{
	this->mDeferredAddQueue = MY_NEW PriorityList();
	this->mDeferredAddQueue->setIsSpeedUpFind(true);
	this->mDeferredRemoveQueue = MY_NEW PriorityList();
	this->mDeferredRemoveQueue->setIsSpeedUpFind(true);
}

void DelayPriorityHandleMgrBase::init()
{
	Super::init();
}

void DelayPriorityHandleMgrBase::dispose()
{
	if(nullptr != this->mDeferredAddQueue)
	{
		this->mDeferredAddQueue->dispose();
		MY_DELETE (GObject*)this->mDeferredAddQueue;
		this->mDeferredAddQueue = nullptr;
	}
	if (nullptr != this->mDeferredRemoveQueue)
	{
		this->mDeferredRemoveQueue->dispose();
		MY_DELETE (GObject*)this->mDeferredRemoveQueue;
		this->mDeferredRemoveQueue = nullptr;
	}

	Super::dispose();
}
	
MY_END_NAMESPACE