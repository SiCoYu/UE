#ifndef __NetTCPClient_H
#define __NetTCPClient_H

#include "Windows/AllowWindowsPlatformTypes.h"

#ifdef USE_EXTERN_THREAD

#include <Sockets/SocketHandler.h>
#include <Sockets/TcpSocket.h>

#endif	// USE_EXTERN_THREAD

#include "Windows/HideWindowsPlatformTypes.h"

#include "PlatformDefine.h"			// 是否使用 UE 的 Socket

#ifdef SOCKETS_NAMESPACE
using namespace SOCKETS_NAMESPACE;
#endif

#ifdef USE_EXTERN_THREAD

class ClientBuffer;

class NetTCPClient : public TcpSocket
{
protected:
	ClientBuffer* mClientBuffer;

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

#endif	// USE_EXTERN_THREAD

#endif				// __NETCLIENT_H