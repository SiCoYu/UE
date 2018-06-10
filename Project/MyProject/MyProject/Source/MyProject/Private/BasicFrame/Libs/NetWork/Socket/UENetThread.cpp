#include "MyProject.h"
#include "UENetThread.h"
#include "INetMgr.h"
#include "MEvent.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"
#include "MyMemoryAlloc.h"
#include "SafePointer.h"

MY_BEGIN_NAMESPACE(MyNS)

UENetThread::UENetThread(INetMgr* pNetMgr, std::string mThreadName)
	: MThread(mThreadName)
{
	this->mNetMgr = pNetMgr;
	this->mSyncEvent = MY_NEW MEvent();
}

UENetThread::~UENetThread()
{
	this->dispose();
}

void UENetThread::dispose()
{
	MY_SAFE_DISPOSE(this->mSyncEvent);
}

MEvent* UENetThread::getSyncEventPtr()
{
	return this->mSyncEvent;
}

bool UENetThread::Init(void)
{
	return true;
}

void UENetThread::Exit(void)
{

}

uint32 UENetThread::Run(void)
{
	if (this->mSyncEvent != nullptr)
	{
		this->mSyncEvent->Set();
	}

	while (!this->mIsExitFlag)
	{
		this->mNetMgr->recAndSendMsg();
		FPlatformProcess::Sleep(1.0f);
	}

	return 0;
}

MY_END_NAMESPACE