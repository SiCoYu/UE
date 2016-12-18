#include "MyProject.h"
#include "UENetClient.h"
#include "ClientBuffer.h"
#include "SocketSubsystem.h"
#include "Sockets.h"
#include "MEvent.h"
#include "MMutex.h"
#include "MLock.h"
#include "Common.h"
#include "UtilStr.h"
#include "ByteBuffer.h"
#include "MsgBuffer.h"
#include "UtilStr.h"
#include "MCircularBuffer.h"
#include "DynBuffer.h"

UENetClient::UENetClient()
	: mBoundEndpoint(FIPv4Address::Any, 0),
	mIsConnected(false)
{
	mSocket = nullptr;
	mClientBuffer = new ClientBuffer();
	m_strDesc = "";
	//mBoundEndpoint(FIPv4Address::Any, 0);

	mMsgSendEndEvent = new MEvent();
	mSendMutex = new MMutex();
}

UENetClient::~UENetClient()
{
	delete mClientBuffer;
	delete mMsgSendEndEvent;
	delete mSendMutex;
}

bool UENetClient::getRecvThreadStart()
{
	return mIsRecvThreadStart;
}

void UENetClient::setRecvThreadStart(bool value)
{
	mIsRecvThreadStart = value;
}

bool UENetClient::getIsConnected()
{
	return mIsConnected;
}

void UENetClient::setIsConnected(bool value)
{
	mIsConnected = value;
}

void UENetClient::Disconnect()
{

}

ClientBuffer* UENetClient::getClientBuffer()
{
	return mClientBuffer;
}

void UENetClient::sendMsg()
{
	//mClientBuffer->sendMsg();
	testSendData();
}

bool UENetClient::connect(FString ip, uint32 port)
{
	FIPv4Address IPAddress;
	FIPv4Address::Parse(ip, IPAddress);
	mBoundEndpoint = FIPv4Endpoint(IPAddress, port);

	ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	bool result = false;
	if (SocketSubsystem != nullptr)
	{
		mSocket = SocketSubsystem->CreateSocket(NAME_Stream, *m_strDesc, true);

		result = mSocket->Connect(*mBoundEndpoint.ToInternetAddr());
	}

	return result;
}

void UENetClient::testSendData()
{
	int sendByte = 0;
	uint8 data[5] = { 1, 2, 3, 4, 5 };
	if (mSocket != nullptr)
	{
		mSocket->Send(data, 5, sendByte);
	}
}

// ������Ϣ
void UENetClient::Send()
{
	MLock mlock(mSendMutex);

	if (!checkAndUpdateConnect())
	{
		return;
	}

	if (mClientBuffer->getSendBuffer()->getBytesAvailable() == 0)     // ������ͻ�����û��Ҫ���͵�����
	{
		if (mClientBuffer->getSendTmpBuffer()->getCircularBuffer()->getSize() > 0)      // ���������ʱ������������Ҫ��
		{
			mClientBuffer->getSendData();
		}

		if (mClientBuffer->getSendBuffer()->getBytesAvailable() == 0)        // ������ͻ�������ȷʵû������
		{
			mMsgSendEndEvent->Set();        // ֪ͨ�ȴ��̣߳��������ݶ��������
			return;
		}
	}

	GLogSys->log(UtilStr::Format("��ʼ�����ֽ��� {0} ", mClientBuffer->getSendBuffer()->getBytesAvailable()));

	bool ret = true;
	int bytesSent = 0;
	ret = mSocket->Send((uint8*)(mClientBuffer->getSendBuffer()->getDynBuffer()->getBuffer() + mClientBuffer->getSendBuffer()->getPos()), mClientBuffer->getSendBuffer()->getBytesAvailable(), bytesSent);
	
	if (!ret)		// �������ʧ��
	{
		mMsgSendEndEvent->Set();        // �����쳣��֪ͨ�ȴ��̣߳��������ݶ�������ɣ���ֹ�ȴ��̲߳��ܽ���
		// �����־
		GLogSys->error("����ʧ��");
		//Disconnect(0);
	}
	else
	{
		GLogSys->log(UtilStr::Format("���������ֽ��� {0} ", bytesSent));

		if (mClientBuffer->getSendBuffer()->getLength() < mClientBuffer->getSendBuffer()->getPos() + bytesSent)
		{
			GLogSys->log(UtilStr::Format("���������ֽ������� {0}", bytesSent));
			mClientBuffer->getSendBuffer()->setPos(mClientBuffer->getSendBuffer()->getLength());
		}
		else
		{
			mClientBuffer->getSendBuffer()->setPos(mClientBuffer->getSendBuffer()->getPos() + bytesSent);
		}

		if (mClientBuffer->getSendBuffer()->getBytesAvailable() > 0)     // �����һ�η��͵����ݻ�û������ɣ���������
		{
			Send();                 // ������������
		}
	}
}

// ��������
void UENetClient::Receive()
{
	// ֻ�� socket ���ӵ�ʱ��ż�����������
	if (!mIsConnected)
	{
		// ���մӷ��������ص���Ϣ
		bool ret = true;	// Ĭ���ǽ��յ�
		int32 bytesRead = 0;	// ��ȡ���ܵ��ֽ���
		ret = mSocket->Recv((uint8*)(mClientBuffer->getDynBuffer()->getBuffer()), (int)mClientBuffer->getDynBuffer()->getCapacity(), bytesRead, ESocketReceiveFlags::None);

		if (!ret)
		{
			GLogSys->error("�������ݳ���");
		}
		else
		{
			if (bytesRead > 0)
			{
				GLogSys->log(UtilStr::Format("���յ����� {0}", bytesRead));
				mClientBuffer->getDynBuffer()->setSize(bytesRead);	// ���ö�ȡ��С
				mClientBuffer->moveDyn2Raw();             // �����յ������ݷŵ�ԭʼ���ݶ���
				mClientBuffer->moveRaw2Msg();             // ����������Ϣ�ƶ�����Ϣ������
				Receive();                  // ��������
			}
		}
	}
}

// ��鲢�Ҹ�������״̬
bool UENetClient::checkAndUpdateConnect()
{
	if (mSocket != nullptr && mSocket->GetConnectionState() != SCS_Connected)	// �����������״̬
	{
		//if (mIsConnected)
		//{
		//	Ctx.m_instance.m_sysMsgRoute.push(new SocketCloseedMR());
		//}
		mIsConnected = false;
	}

	return mIsConnected;
}

MEvent* UENetClient::getMsgSendEndEvent()
{
	return mMsgSendEndEvent;
}

void UENetClient::setMsgSendEndEvent(MEvent* value)
{
	mMsgSendEndEvent = value;
}

bool UENetClient::canSendNewData()
{
	return (mClientBuffer->getSendBuffer()->getBytesAvailable() == 0);
}

void UENetClient::SetRevBufferSize(int size)
{
	int retSize = 0;
	mSocket->SetSendBufferSize(size, retSize);      // ReceiveBufferSize Ĭ�� 8096 �ֽ�
	mClientBuffer->SetRevBufferSize(size);
}