#ifndef __UENETCLIENT_H
#define __UENETCLIENT_H

#include "MyProject.h"
//#include "IPv4Address.h"		// FIPv4Address
//#include "IPv4Endpoint.h"		// ֻ���� IPv4Endpoint.h ����벻�� // FIPv4Endpoint
#include "Networking.h"			// ����һ����ȫ��������ֹֻ�������ֵ��±��벻��
#include <string>
#include "PlatformDefine.h"

class FSocket;

MY_BEGIN_NAMESPACE(MyNS)

class MClientBuffer;
class MEvent;
class MMutex;

class UENetClient
{
protected:
	FString	mStrDesc;
	FIPv4Endpoint mBoundEndpoint;

	FSocket* mSocket;
	MClientBuffer* mClientBuffer;

	bool mIsRecvThreadStart;      // �����߳��Ƿ�����
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

	void init();
	void dispose();

	bool getRecvThreadStart();
	void setRecvThreadStart(bool value);

	bool getIsConnected();
	void setIsConnected(bool value);

	MClientBuffer* getClientBuffer();

	MEvent* getMsgSendEndEvent();
	void setMsgSendEndEvent(MEvent* value);
	// �Ƿ���Է����µ����ݣ���һ�η��͵������Ƿ�����ɣ�ֻ���ϴη��͵�����ȫ��������ɣ����ܷ����µ�����
	bool canSendNewData();
	// ���ý��ջ�������С������;�������Խӣ����һ��Ҫ�ͷ�������Сһ�£�����һ��Ҫ�� 8 ������������������Ϣ�Ƚ϶࣬����һ�������͹�����ʱ�򣬻����
	void SetRevBufferSize(int size);

	void sendMsg();
	bool connect(FString ip = "127.0.0.1", uint32 port = 5000);	// ���ӷ�����
	void Send();
	void Receive();
	bool checkAndUpdateConnect();
	void Disconnect();
};

MY_END_NAMESPACE

#endif