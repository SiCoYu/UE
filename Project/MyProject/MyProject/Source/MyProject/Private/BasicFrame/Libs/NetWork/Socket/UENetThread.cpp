#include "MyProject.h"
#include "UENetThread.h"
#include "INetMgr.h"
#include "MEvent.h"

#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"
#include "MyMemoryAlloc.h"

MY_BEGIN_NAMESPACE(MyNS)

UENetThread::UENetThread(INetMgr* pNetMgr, std::string mThreadName)
	: MThread(mThreadName)
{
	this->mNetMgr = pNetMgr;
	this->mSyncEvent = MY_NEW MEvent();
}

UENetThread::~UENetThread()
{
	MY_DELETE this->mSyncEvent;
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