#ifndef __UENETCLIENT_H
#define __UENETCLIENT_H

#include "MyProject.h"
//#include "IPv4Address.h"		// FIPv4Address
//#include "IPv4Endpoint.h"		// ֻ���� IPv4Endpoint.h ����벻�� // FIPv4Endpoint
#include "Networking.h"			// ����һ����ȫ��������ֹֻ�������ֵ��±��벻��

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

	bool connect(FString ip, uint32 port);	// ���ӷ�����
};

#endif