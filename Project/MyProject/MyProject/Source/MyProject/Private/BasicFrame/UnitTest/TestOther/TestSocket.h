#ifndef __TestSocket_H
#define __TestSocket_H

#include "Windows/AllowWindowsPlatformTypes.h"

#ifdef USE_EXTERN_THREAD

#include <Sockets/StdoutLog.h>
#include <Sockets/SocketHandler.h>
#include <Sockets/TcpSocket.h>

#endif	// USE_EXTERN_THREAD

#include "Windows/HideWindowsPlatformTypes.h"

#ifdef USE_EXTERN_THREAD

class TestSocket
{
public:
	TcpSocket* mTcpSocket;

public:
	TestSocket();
};

#endif	// USE_EXTERN_THREAD

#endif				// __TESTSOCKET_H