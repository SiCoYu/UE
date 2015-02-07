#include "MyProject.h"
#include "NetThread.h"

#ifdef ENABLE_DETACH

#include "Windows/AllowWindowsPlatformTypes.h"

#include "Sockets/Utility.h"

#include "Windows/HideWindowsPlatformTypes.h"

#ifdef SOCKETS_NAMESPACE
namespace SOCKETS_NAMESPACE {
#endif

NetThread::NetThread(Socket *p)
	:Thread(false)
	, m_socket(p)
{
	// Creator will release
}

NetThread::~NetThread()
{
	if (IsRunning())
	{
		SetRelease(true);
		SetRunning(false);
		m_h.Release();
		Utility::Sleep(5);
	}
}

void NetThread::Run()
{
	m_h.SetSlave();
	m_h.Add(m_socket);
	m_socket->SetSlaveHandler(&m_h);
	m_socket->OnDetached();
	m_h.EnableRelease();
	while (m_h.GetCount() > 1 && IsRunning())
	{
		m_h.Select(0, 500000);
	}
	// m_socket now deleted oops
	//  (a socket can only be detached if DeleteByHandler() is true)
	// yeah oops m_socket delete its socket thread, that means this
	// so Socket will no longer delete its socket thread, instead we do this:
	SetDeleteOnExit();
}

#ifdef SOCKETS_NAMESPACE
} // namespace SOCKETS_NAMESPACE {
#endif

#endif // ENABLE_DETACH