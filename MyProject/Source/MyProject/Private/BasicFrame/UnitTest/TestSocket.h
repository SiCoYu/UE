#ifndef __TestSocket_H
#define __TestSocket_H

#include "Windows/AllowWindowsPlatformTypes.h"

#include <Sockets/StdoutLog.h>
#include <Sockets/SocketHandler.h>
#include <Sockets/TcpSocket.h>

#include "Windows/HideWindowsPlatformTypes.h"

class TestSocket
{
public:
	TcpSocket* mTcpSocket;

public:
	TestSocket();
};

#endif				// __TESTSOCKET_H