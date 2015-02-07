#ifndef __NETCLIENT_H
#define __NETCLIENT_H

#include "Windows/AllowWindowsPlatformTypes.h"

#include <Sockets/SocketHandler.h>
#include <Sockets/TcpSocket.h>

#include "Windows/HideWindowsPlatformTypes.h"

#ifdef SOCKETS_NAMESPACE
using namespace SOCKETS_NAMESPACE;
#endif

class NetClientBuffer;

class NetClient : public TcpSocket
{
protected:
	NetClientBuffer* m_pNetClientBuffer;

public:
	NetClient(ISocketHandler& h);
	~NetClient();

	virtual void OnConnect();
	virtual void OnConnectFailed();
	virtual void OnRawData(const char *buf, size_t len);
	virtual void OnDelete();
	NetClientBuffer* getNetClientBuffer();
	void sendMsg();
};

#endif				// __NETCLIENT_H