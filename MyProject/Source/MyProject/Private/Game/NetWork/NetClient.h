#ifndef __NETCLIENT_H
#define __NETCLIENT_H

#include "Windows/AllowWindowsPlatformTypes.h"

#include <Sockets/SocketHandler.h>
#include <Sockets/TcpSocket.h>
#include <iostream>

#include "Windows/HideWindowsPlatformTypes.h"

#ifdef SOCKETS_NAMESPACE
using namespace SOCKETS_NAMESPACE;
#endif

class NetClient : public TcpSocket
{
protected:
	NetBuffer* m_pNetBuffer;

public:
	NetClient(ISocketHandler& h);
	virtual void OnConnect();
	virtual void OnConnectFailed();
	virtual void OnRawData(const char *buf, size_t len);
	virtual void OnDelete();
};

#endif				// __NETCLIENT_H