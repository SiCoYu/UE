#ifndef __NETTHREAD_H
#define __NETTHREAD_H

#include "Windows/AllowWindowsPlatformTypes.h"

#include "Sockets/Socket.h"
#include "Sockets/Thread.h"
#include "Sockets/SocketHandler.h"
#include "Sockets/sockets-config.h"

#include "Windows/HideWindowsPlatformTypes.h"


#ifdef ENABLE_DETACH


#ifdef SOCKETS_NAMESPACE
namespace SOCKETS_NAMESPACE {
#endif

class Socket;

/** Detached socket run thread.
\ingroup internal */
class NetThread : public Thread
{
public:
	NetThread(Socket *p);
	~NetThread();

	void Run();

private:
	NetThread(const NetThread& s) : m_socket(s.m_socket) {}
	NetThread& operator=(const NetThread&) { return *this; }

	SocketHandler m_h;
	Socket *m_socket;
};

#ifdef SOCKETS_NAMESPACE
} // namespace SOCKETS_NAMESPACE {
#endif

#endif // ENABLE_DETACH

#endif				// __NETTHREAD_H