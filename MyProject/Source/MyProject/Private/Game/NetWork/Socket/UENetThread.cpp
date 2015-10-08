#include "MyProject.h"
#include "UENetThread.h"

#include "INetMgr.h"
#include "NetClient.h"
#include "INetMgr.h"

UENetThread::UENetThread(INetMgr* pNetMgr)
	: m_ExitFlag(false)
{
	m_pNetMgr = pNetMgr;
	m_pTaskGraphBoundSyncEvent = FPlatformProcess::GetSynchEventFromPool(true);
}

UENetThread::~UENetThread()
{
	FPlatformProcess::ReturnSynchEventToPool(m_pTaskGraphBoundSyncEvent);
	m_pTaskGraphBoundSyncEvent = nullptr;
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
	if (m_pTaskGraphBoundSyncEvent != NULL)
	{
		m_pTaskGraphBoundSyncEvent->Trigger();
	}

	while (!m_ExitFlag)
	{
		m_pNetMgr->recAndSendMsg();
		FPlatformProcess::Sleep(1.0f);
	}

	return 0;
}

void UENetThread::setExitFlag(bool exit)
{
	m_ExitFlag = exit;
}