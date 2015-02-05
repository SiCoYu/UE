#ifndef __TESTSOCKET_H
#define __TESTSOCKET_H

#include "Windows/AllowWindowsPlatformTypes.h"

#include <Sockets/StdoutLog.h>
#include <Sockets/SocketHandler.h>
#include <Sockets/TcpSocket.h>

#include "Windows/HideWindowsPlatformTypes.h"

class TestSocket
{
public:
	TcpSocket* m_tcpSocket;

public:
	TestSocket();
};

#endif				// __TESTSOCKET_H