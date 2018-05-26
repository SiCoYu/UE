#include "MyProject.h"
#include "UENetThread.h"
#include "INetMgr.h"
#include "MEvent.h"

UENetThread::UENetThread(INetMgr* pNetMgr, std::string mThreadName)
	: MThread(mThreadName)
{
	this->mNetMgr = pNetMgr;
	this->mSyncEvent = MY_NEW MEvent();
}

UENetThread::~UENetThread()
{
	delete this->mSyncEvent;
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