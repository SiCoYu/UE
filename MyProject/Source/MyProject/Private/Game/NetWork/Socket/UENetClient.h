#ifndef __UENETCLIENT_H
#define __UENETCLIENT_H

#include "MyProject.h"
//#include "IPv4Address.h"		// FIPv4Address
//#include "IPv4Endpoint.h"		// 只包含 IPv4Endpoint.h 会编译不过 // FIPv4Endpoint
#include "Networking.h"			// 网络一次性全包括，防止只包含部分导致编译不过
#include <string>

class FSocket;
class ClientBuffer;
class MEvent;
class MMutex;

class UENetClient
{
protected:
	FString	m_strDesc;
	FIPv4Endpoint m_boundEndpoint;

	FSocket* m_socket;
	ClientBuffer* m_clientBuffer;

	bool m_brecvThreadStart;      // 接收线程是否启动
	bool m_isConnected;

	MEvent* m_msgSendEndEvent;
	MMutex* m_sendMutex;

protected:
	void testSendData();

public:
	std::string m_ip;
	int m_port;

	UENetClient();
	~UENetClient();

	bool getRecvThreadStart();
	void setRecvThreadStart(bool value);

	bool getIsConnected();
	void setIsConnected(bool value);

	ClientBuffer* getClientBuffer();
	void sendMsg();

	bool connect(FString ip = "127.0.0.1", uint32 port = 5000);	// 连接服务器
	void Send();
	void Receive();
	bool checkAndUpdateConnect();
	void Disconnect();
};

#endif