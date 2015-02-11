#include "MyProject.h"
#include "NetThread.h"

#ifdef ENABLE_DETACH

#include "Windows/AllowWindowsPlatformTypes.h"

#include "Sockets/Utility.h"

#include "Windows/HideWindowsPlatformTypes.h"

#include "INetMgr.h"
#include "NetClient.h"

#ifdef SOCKETS_NAMESPACE
namespace SOCKETS_NAMESPACE {
#endif

NetThread::NetThread(SocketHandler *p)
	: Thread(true)
	, m_h(p)
	, m_ExitFlag(false)
{
	// Creator will release
}

NetThread::~NetThread()
{
	if (IsRunning())
	{
		SetRelease(true);
		SetRunning(false);
		Utility::Sleep(5);
	}
}

void NetThread::Run()
{
	while (!m_ExitFlag)
	{
		if (m_h->GetCount() > 1 && IsRunning())
		{
			m_h->Select(0, 500000);
			((INetMgr*)m_h)->recAndSendMsg();
		}

		Utility::Sleep(0.04);
	}
	// m_socket now deleted oops
	//  (a socket can only be detached if DeleteByHandler() is true)
	// yeah oops m_socket delete its socket thread, that means this
	// so Socket will no longer delete its socket thread, instead we do this:
	SetDeleteOnExit();
}

void NetThread::setExitFlag(bool exit)
{
	m_ExitFlag = exit;
}

#ifdef SOCKETS_NAMESPACE
} // namespace SOCKETS_NAMESPACE {
#endif

#endif // ENABLE_DETACH