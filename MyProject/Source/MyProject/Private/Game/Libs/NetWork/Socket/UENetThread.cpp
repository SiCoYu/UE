#include "MyProject.h"
#include "UENetThread.h"
#include "INetMgr.h"
#include "MEvent.h"

UENetThread::UENetThread(INetMgr* pNetMgr, std::string m_threadName)
	: MThread(m_threadName), m_ExitFlag(false)
{
	m_pNetMgr = pNetMgr;
	m_pSyncEvent = new MEvent();
}

UENetThread::~UENetThread()
{
	delete m_pSyncEvent;
}

MEvent* UENetThread::getSyncEventPtr()
{
	return m_pSyncEvent;
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
	if (m_pSyncEvent != nullptr)
	{
		m_pSyncEvent->Set();
	}

	while (!m_ExitFlag)
	{
		m_pNetMgr->recAndSendMsg();
		FPlatformProcess::Sleep(1.0f);
	}

	return 0;
}