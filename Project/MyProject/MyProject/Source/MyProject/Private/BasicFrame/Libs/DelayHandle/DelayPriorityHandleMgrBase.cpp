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
	this->mDeferredDelQueue = MY_NEW PriorityList();
	this->mDeferredDelQueue->setIsSpeedUpFind(true);
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
		MY_DELETE this->mDeferredAddQueue;
		this->mDeferredAddQueue = nullptr;
	}
	if (nullptr != this->mDeferredDelQueue)
	{
		this->mDeferredDelQueue->dispose();
		MY_DELETE this->mDeferredDelQueue;
		this->mDeferredDelQueue = nullptr;
	}

	Super::dispose();
}
	
MY_END_NAMESPACE