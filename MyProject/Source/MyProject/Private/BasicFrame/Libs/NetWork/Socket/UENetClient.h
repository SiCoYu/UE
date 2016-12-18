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
	FIPv4Endpoint mBoundEndpoint;

	FSocket* mSocket;
	ClientBuffer* mClientBuffer;

	bool mIsRecvThreadStart;      // 接收线程是否启动
	bool mIsConnected;

	MEvent* mMsgSendEndEvent;
	MMutex* mSendMutex;

protected:
	void testSendData();

public:
	std::string mIp;
	int mPort;

	UENetClient();
	~UENetClient();

	bool getRecvThreadStart();
	void setRecvThreadStart(bool value);

	bool getIsConnected();
	void setIsConnected(bool value);

	ClientBuffer* getClientBuffer();

	MEvent* getMsgSendEndEvent();
	void setMsgSendEndEvent(MEvent* value);
	// 是否可以发送新的数据，上一次发送的数据是否发送完成，只有上次发送的数据全部发送完成，才能发送新的数据
	bool canSendNewData();
	// 设置接收缓冲区大小，和征途服务器对接，这个一定要和服务器大小一致，并且一定要是 8 的整数倍，否则在消息比较多，并且一个包发送过来的时候，会出错
	void SetRevBufferSize(int size);

	void sendMsg();
	bool connect(FString ip = "127.0.0.1", uint32 port = 5000);	// 连接服务器
	void Send();
	void Receive();
	bool checkAndUpdateConnect();
	void Disconnect();
};

#endif