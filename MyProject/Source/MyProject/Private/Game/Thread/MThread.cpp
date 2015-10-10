#include "MyProject.h"
#include "MThread.h"
#include "MEvent.h"

MThread::MThread(std::string threadName)
	: m_threadName(threadName)
{
	//m_pSyncEvent = new MEvent();
}

MThread::~MThread()
{
	//delete m_pSyncEvent;
}

void MThread::setExitFlag(bool value)
{
	m_ExitFlag = value;
}

void MThread::start()
{
	// FRunnableThread::Create 的第二个参数如果穿 ansi 字符集会导致编译不过，需要传递宽字节编码
	//m_pThread = FRunnableThread::Create(this, m_threadName.c_str(), 0, TPri_Normal, FPlatformAffinity::GetNoAffinityMask());
	m_pThread = FRunnableThread::Create(this, StringCast<TCHAR>(m_threadName.c_str()).Get(), 0, TPri_Normal, FPlatformAffinity::GetNoAffinityMask());
	//this->m_pSyncEvent->Wait();
}

void MThread::join()
{
	m_pThread->WaitForCompletion();
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