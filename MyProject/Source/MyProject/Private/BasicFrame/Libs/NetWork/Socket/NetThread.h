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
	NetThread(SocketHandler *p);
	~NetThread();

	void Run();
	void setExitFlag(bool exit);

private:
	NetThread(const NetThread& s) {}
	NetThread& operator=(const NetThread&) { return *this; }

	SocketHandler* mH;
	bool mIsExitFlag;
};

#ifdef SOCKETS_NAMESPACE
} // namespace SOCKETS_NAMESPACE {
#endif

#endif // ENABLE_DETACH

#endif				// __NETTHREAD_H