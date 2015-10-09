#ifndef __UENETCLIENT_H
#define __UENETCLIENT_H

#include "MyProject.h"
//#include "IPv4Address.h"		// FIPv4Address
//#include "IPv4Endpoint.h"		// ֻ���� IPv4Endpoint.h ����벻�� // FIPv4Endpoint
#include "Networking.h"			// ����һ����ȫ��������ֹֻ�������ֵ��±��벻��
#include <string>

class FSocket;
class ClientBuffer;
class MEvent;
class MMutex;

class UENetClient
{
protected:
	FSocket* m_pSocket;
	ClientBuffer* m_clientBuffer;
	FString	m_strDesc;
	FIPv4Endpoint m_boundEndpoint;

	MEvent* m_msgSendEndEvent;
	MMutex* m_sendMutex;
	bool m_isConnected;

protected:
	void testSendData();

public:
	std::string m_ip = "127.0.0.1";
	int m_port = 50000;

	UENetClient();
	~UENetClient();

	virtual void OnConnect();
	virtual void OnConnectFailed();
	virtual void OnRawData(const char *buf, size_t len);
	virtual void OnDelete();
	ClientBuffer* getClientBuffer();
	void sendMsg();

	bool connect(FString ip, uint32 port);	// ���ӷ�����
	void Send();
	bool checkAndUpdateConnect();
	void Disconnect();
};

#endif