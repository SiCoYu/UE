#ifndef __UENETCLIENT_H
#define __UENETCLIENT_H

#include "MyProject.h"

class NetClientBuffer;

class UENetClient
{
protected:
	NetClientBuffer* m_pNetClientBuffer;

public:
	UENetClient();
	~UENetClient();

	virtual void OnConnect();
	virtual void OnConnectFailed();
	virtual void OnRawData(const char *buf, size_t len);
	virtual void OnDelete();
	NetClientBuffer* getNetClientBuffer();
	void sendMsg();

	void connect(FString ip, uint32 port);	// 连接服务器
};

#endif