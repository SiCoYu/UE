#include "MyProject.h"
#include "UENetThread.h"

#include "INetMgr.h"
#include "NetClient.h"

UENetThread::UENetThread()
	: m_ExitFlag(false)
{
	
}

UENetThread::~UENetThread()
{
	//if (IsRunning())
	//{
	//	Utility::Sleep(5);
	//}
}

void UENetThread::Run()
{
	//while (!m_ExitFlag)
	//{
	//	Utility::Sleep(1000);
	//}
}

void UENetThread::setExitFlag(bool exit)
{
	m_ExitFlag = exit;
}