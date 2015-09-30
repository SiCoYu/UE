#ifndef __UENETCLIENT_H
#define __UENETCLIENT_H

#include "MyProject.h"
//#include "IPv4Address.h"		// FIPv4Address
//#include "IPv4Endpoint.h"		// 只包含 IPv4Endpoint.h 会编译不过 // FIPv4Endpoint
#include "Networking.h"			// 网络一次性全包括，防止只包含部分导致编译不过

class FSocket;
class NetClientBuffer;

class UENetClient
{
protected:
	FSocket* m_pSocket;
	NetClientBuffer* m_pNetClientBuffer;
	FString	m_strDesc;
	FIPv4Endpoint m_boundEndpoint;

protected:
	void testSendData();

public:
	UENetClient();
	~UENetClient();

	virtual void OnConnect();
	virtual void OnConnectFailed();
	virtual void OnRawData(const char *buf, size_t len);
	virtual void OnDelete();
	NetClientBuffer* getNetClientBuffer();
	void sendMsg();

	bool connect(FString ip, uint32 port);	// 连接服务器
};

#endif