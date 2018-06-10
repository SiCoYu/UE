#include "MyProject.h"
#include "MThread.h"
#include "MEvent.h"

MY_BEGIN_NAMESPACE(MyNS)

MThread::MThread(std::string threadName)
	: mThreadName(threadName), mIsExitFlag(false)
{
	//mSyncEvent = new MEvent();
}

MThread::~MThread()
{
	//delete mSyncEvent;
}

void MThread::init()
{

}

void MThread::dispose()
{

}

void MThread::setExitFlag(bool value)
{
	mIsExitFlag = value;
}

void MThread::start()
{
	// FRunnableThread::Create 的第二个参数如果穿 ansi 字符集会导致编译不过，需要传递宽字节编码
	//mThread = FRunnableThread::Create(this, mThreadName.c_str(), 0, TPri_Normal, FPlatformAffinity::GetNoAffinityMask());
	mThread = FRunnableThread::Create(this, StringCast<TCHAR>(mThreadName.c_str()).Get(), 0, TPri_Normal, FPlatformAffinity::GetNoAffinityMask());
	//this->mSyncEvent->Wait();
}

void MThread::join()
{
	this->Stop();
	mThread->WaitForCompletion();
}

bool MThread::Init(void)
{
	return true;
}

void MThread::Exit(void)
{

}

uint32 MThread::Run(void)
{
	return 0;
}

void MThread::Stop()
{
	mIsExitFlag = true;
}

void MThread::EnsureCompletion()
{
	this->Stop();
	this->mThread->WaitForCompletion();
}

void MThread::Shutdown()
{
	this->EnsureCompletion();
}

MY_END_NAMESPACE