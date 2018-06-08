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
	GObject* tmp = nullptr;

	if(nullptr != this->mDeferredAddQueue)
	{
		this->mDeferredAddQueue->dispose();
		tmp = (GObject*)this->mDeferredAddQueue;
		MY_DELETE tmp;
		this->mDeferredAddQueue = nullptr;
	}
	if (nullptr != this->mDeferredRemoveQueue)
	{
		this->mDeferredRemoveQueue->dispose();
		tmp = (GObject*)this->mDeferredRemoveQueue;
		MY_DELETE tmp;
		this->mDeferredRemoveQueue = nullptr;
	}

	Super::dispose();
}
	
MY_END_NAMESPACE