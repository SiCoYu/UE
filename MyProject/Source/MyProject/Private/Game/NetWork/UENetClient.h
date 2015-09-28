#ifndef __UENETCLIENT_H
#define __UENETCLIENT_H

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
};

#endif