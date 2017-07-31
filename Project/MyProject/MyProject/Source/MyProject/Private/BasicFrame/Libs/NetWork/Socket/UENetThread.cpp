#include "MyProject.h"
#include "UENetThread.h"
#include "INetMgr.h"
#include "MEvent.h"

UENetThread::UENetThread(INetMgr* pNetMgr, std::string mThreadName)
	: MThread(mThreadName)
{
	mNetMgr = pNetMgr;
	mSyncEvent = new MEvent();
}

UENetThread::~UENetThread()
{
	delete mSyncEvent;
}

MEvent* UENetThread::getSyncEventPtr()
{
	return mSyncEvent;
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
	if (mSyncEvent != nullptr)
	{
		mSyncEvent->Set();
	}

	while (!mIsExitFlag)
	{
		mNetMgr->recAndSendMsg();
		FPlatformProcess::Sleep(1.0f);
	}

	return 0;
}