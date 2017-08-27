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

// 发送消息
void UENetClient::Send()
{
	MLock mlock(mSendMutex);

	if (!checkAndUpdateConnect())
	{
		return;
	}

	if (mClientBuffer->getSendBuffer()->getBytesAvailable() == 0)     // 如果发送缓冲区没有要发送的数据
	{
		if (mClientBuffer->getSendTmpBuffer()->getCircularBuffer()->getSize() > 0)      // 如果发送临时缓冲区有数据要发
		{
			mClientBuffer->getSendData();
		}

		if (mClientBuffer->getSendBuffer()->getBytesAvailable() == 0)        // 如果发送缓冲区中确实没有数据
		{
			mMsgSendEndEvent->Set();        // 通知等待线程，所有数据都发送完成
			return;
		}
	}

	GLogSys->log(UtilStr::Format("开始发送字节数 {0} ", mClientBuffer->getSendBuffer()->getBytesAvailable()));

	bool ret = true;
	int bytesSent = 0;
	ret = mSocket->Send((uint8*)(mClientBuffer->getSendBuffer()->getDynBuffer()->getBuffer() + mClientBuffer->getSendBuffer()->getPos()), mClientBuffer->getSendBuffer()->getBytesAvailable(), bytesSent);
	
	if (!ret)		// 如果发送失败
	{
		mMsgSendEndEvent->Set();        // 发生异常，通知等待线程，所有数据都发送完成，防止等待线程不能解锁
		// 输出日志
		GLogSys->error("发送失败");
		//Disconnect(0);
	}
	else
	{
		GLogSys->log(UtilStr::Format("结束发送字节数 {0} ", bytesSent));

		if (mClientBuffer->getSendBuffer()->getLength() < mClientBuffer->getSendBuffer()->getPos() + bytesSent)
		{
			GLogSys->log(UtilStr::Format("结束发送字节数错误 {0}", bytesSent));
			mClientBuffer->getSendBuffer()->setPos(mClientBuffer->getSendBuffer()->getLength());
		}
		else
		{
			mClientBuffer->getSendBuffer()->setPos(mClientBuffer->getSendBuffer()->getPos() + bytesSent);
		}

		if (mClientBuffer->getSendBuffer()->getBytesAvailable() > 0)     // 如果上一次发送的数据还没发送完成，继续发送
		{
			Send();                 // 继续发送数据
		}
	}
}

// 接受数据
void UENetClient::Receive()
{
	// 只有 socket 连接的时候才继续接收数据
	if (!mIsConnected)
	{
		// 接收从服务器返回的信息
		bool ret = true;	// 默认是接收的
		int32 bytesRead = 0;	// 读取的总的字节数
		ret = mSocket->Recv((uint8*)(mClientBuffer->getDynBuffer()->getBuffer()), (int)mClientBuffer->getDynBuffer()->getCapacity(), bytesRead, ESocketReceiveFlags::None);

		if (!ret)
		{
			GLogSys->error("接收数据出错");
		}
		else
		{
			if (bytesRead > 0)
			{
				GLogSys->log(UtilStr::Format("接收到数据 {0}", bytesRead));
				mClientBuffer->getDynBuffer()->setSize(bytesRead);	// 设置读取大小
				mClientBuffer->moveDyn2Raw();             // 将接收到的数据放到原始数据队列
				mClientBuffer->moveRaw2Msg();             // 将完整的消息移动到消息缓冲区
				Receive();                  // 继续接收
			}
		}
	}
}

// 检查并且更新连接状态
bool UENetClient::checkAndUpdateConnect()
{
	if (mSocket != nullptr && mSocket->GetConnectionState() != SCS_Connected)	// 如果不是连接状态
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
	mSocket->SetSendBufferSize(size, retSize);      // ReceiveBufferSize 默认 8096 字节
	mClientBuffer->SetRevBufferSize(size);
}