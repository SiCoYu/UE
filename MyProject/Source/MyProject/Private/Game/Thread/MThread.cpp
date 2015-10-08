#include "MyProject.h"
#include "MThread.h"
#include "MEvent.h"

MThread::MThread()
	: m_threadName("")
{
	m_pSyncEvent = new MEvent();
}

MThread::~MThread()
{
	delete m_pSyncEvent;
}

void MThread::setExitFlag(bool value)
{
	m_ExitFlag = value;
}

void MThread::start()
{
	m_pThread = FRunnableThread::Create(this, m_threadName.c_str(), 0, TPri_Normal, FPlatformAffinity::GetNoAffinityMask());
	this->m_pSyncEvent->Wait();
}

void MThread::join()
{
	m_pThread->WaitForCompletion();
}

bool MThread::Init(void)
{

}

void MThread::Exit(void)
{

}

uint32 MThread::Run(void)
{

}