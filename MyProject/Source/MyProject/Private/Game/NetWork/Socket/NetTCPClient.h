#ifndef __NETCLIENT_H
#define __NETCLIENT_H

#include "Windows/AllowWindowsPlatformTypes.h"

#include <Sockets/SocketHandler.h>
#include <Sockets/TcpSocket.h>

#include "Windows/HideWindowsPlatformTypes.h"

#include "PlatformDefine.h"			// 是否使用 UE 的 Socket

#ifdef SOCKETS_NAMESPACE
using namespace SOCKETS_NAMESPACE;
#endif

class ClientBuffer;

class NetTCPClient : public TcpSocket
{
protected:
	ClientBuffer* m_dataBuffer;

public:
	NetTCPClient(ISocketHandler& h);
	~NetTCPClient();

	virtual void OnConnect();
	virtual void OnConnectFailed();
	virtual void OnRawData(const char *buf, size_t len);
	virtual void OnDelete();
	ClientBuffer* getClientBuffer();
	void sendMsg();
};

#endif				// __NETCLIENT_H