#include "MyProject.h"
#include "UENetClient.h"
#include "MClientBuffer.h"
#include "SocketSubsystem.h"
#include "Sockets.h"
#include "MEvent.h"
#include "MMutex.h"
#include "MLock.h"
#include "Prequisites.h"
#include "UtilStr.h"
#include "MByteBuffer.h"
#include "MMsgBuffer.h"
#include "UtilStr.h"
#include "MCircularBuffer.h"
#include "MDynBuffer.h"

MY_BEGIN_NAMESPACE(MyNS)

UENetClient::UENetClient()
	: mBoundEndpoint(FIPv4Address::Any, 0),
	mIsConnected(false)
{
	this->mSocket = nullptr;
	this->mClientBuffer = MY_NEW MClientBuffer();
	this->mStrDesc = "";
	//mBoundEndpoint(FIPv4Address::Any, 0);

	this->mMsgSendEndEvent = MY_NEW MEvent();
	this->mSendMutex = MY_NEW MMutex();
}

UENetClient::~UENetClient()
{
	MY_DELETE this->mClientBuffer;
	MY_DELETE this->mMsgSendEndEvent;
	MY_DELETE this->mSendMutex;
}

bool UENetClient::getRecvThreadStart()
{
	return this->mIsRecvThreadStart;
}

void UENetClient::setRecvThreadStart(bool value)
{
	this->mIsRecvThreadStart = value;
}

bool UENetClient::getIsConnected()
{
	return this->mIsConnected;
}

void UENetClient::setIsConnected(bool value)
{
	this->mIsConnected = value;
}

void UENetClient::Disconnect()
{

}

MClientBuffer* UENetClient::getClientBuffer()
{
	return this->mClientBuffer;
}

void UENetClient::sendMsg()
{
	//mClientBuffer->sendMsg();
	this->testSendData();
}

bool UENetClient::connect(FString ip, uint32 port)
{
	FIPv4Address IPAddress;
	FIPv4Address::Parse(ip, IPAddress);
	this->mBoundEndpoint = FIPv4Endpoint(IPAddress, port);

	ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	bool result = false;

	if (SocketSubsystem != nullptr)
	{
		this->mSocket = SocketSubsystem->CreateSocket(NAME_Stream, *mStrDesc, true);

		result = mSocket->Connect(*mBoundEndpoint.ToInternetAddr());
	}

	return result;
}

void UENetClient::testSendData()
{
	int sendByte = 0;
	uint8 data[5] = { 1, 2, 3, 4, 5 };

	if (this->mSocket != nullptr)
	{
		this->mSocket->Send(data, 5, sendByte);
	}
}

// 发送消息
void UENetClient::Send()
{
	MLock mlock(this->mSendMutex);

	if (!this->checkAndUpdateConnect())
	{
		return;
	}

	if (this->mClientBuffer->getSendBuffer()->getBytesAvailable() == 0)     // 如果发送缓冲区没有要发送的数据
	{
		if (this->mClientBuffer->getSendTmpBuffer()->getCircularBuffer()->getSize() > 0)      // 如果发送临时缓冲区有数据要发
		{
			this->mClientBuffer->getSendData();
		}

		if (this->mClientBuffer->getSendBuffer()->getBytesAvailable() == 0)        // 如果发送缓冲区中确实没有数据
		{
			this->mMsgSendEndEvent->Set();        // 通知等待线程，所有数据都发送完成
			return;
		}
	}

	GLogSys->log(UtilStr::Format("开始发送字节数 {0} ", this->mClientBuffer->getSendBuffer()->getBytesAvailable()));

	bool ret = true;
	int bytesSent = 0;

	ret = this->mSocket->Send((uint8*)(this->mClientBuffer->getSendBuffer()->getDynBuffer()->getBuffer() + this->mClientBuffer->getSendBuffer()->getPos()), this->mClientBuffer->getSendBuffer()->getBytesAvailable(), bytesSent);
	
	if (!ret)		// 如果发送失败
	{
		this->mMsgSendEndEvent->Set();        // 发生异常，通知等待线程，所有数据都发送完成，防止等待线程不能解锁
		// 输出日志
		GLogSys->error("发送失败");
		//Disconnect(0);
	}
	else
	{
		GLogSys->log(UtilStr::Format("结束发送字节数 {0} ", bytesSent));

		if (this->mClientBuffer->getSendBuffer()->getLength() < this->mClientBuffer->getSendBuffer()->getPos() + bytesSent)
		{
			GLogSys->log(UtilStr::Format("结束发送字节数错误 {0}", bytesSent));
			this->mClientBuffer->getSendBuffer()->setPos(this->mClientBuffer->getSendBuffer()->getLength());
		}
		else
		{
			this->mClientBuffer->getSendBuffer()->setPos(this->mClientBuffer->getSendBuffer()->getPos() + bytesSent);
		}

		if (this->mClientBuffer->getSendBuffer()->getBytesAvailable() > 0)     // 如果上一次发送的数据还没发送完成，继续发送
		{
			this->Send();                 // 继续发送数据
		}
	}
}

// 接受数据
void UENetClient::Receive()
{
	// 只有 socket 连接的时候才继续接收数据
	if (!this->mIsConnected)
	{
		// 接收从服务器返回的信息
		bool ret = true;	// 默认是接收的
		int32 bytesRead = 0;	// 读取的总的字节数
		ret = this->mSocket->Recv((uint8*)(this->mClientBuffer->getDynBuffer()->getBuffer()), (int)this->mClientBuffer->getDynBuffer()->getCapacity(), bytesRead, ESocketReceiveFlags::None);

		if (!ret)
		{
			GLogSys->error("接收数据出错");
		}
		else
		{
			if (bytesRead > 0)
			{
				GLogSys->log(UtilStr::Format("接收到数据 {0}", bytesRead));
				this->mClientBuffer->getDynBuffer()->setSize(bytesRead);	// 设置读取大小
				this->mClientBuffer->moveDyn2Raw();             // 将接收到的数据放到原始数据队列
				this->mClientBuffer->moveRaw2Msg();             // 将完整的消息移动到消息缓冲区
				this->Receive();                  // 继续接收
			}
		}
	}
}

// 检查并且更新连接状态
bool UENetClient::checkAndUpdateConnect()
{
	if (this->mSocket != nullptr && this->mSocket->GetConnectionState() != SCS_Connected)	// 如果不是连接状态
	{
		//if (mIsConnected)
		//{
		//	Ctx.m_instance.m_sysMsgRoute.push(new SocketCloseedMR());
		//}
		this->mIsConnected = false;
	}

	return this->mIsConnected;
}

MEvent* UENetClient::getMsgSendEndEvent()
{
	return this->mMsgSendEndEvent;
}

void UENetClient::setMsgSendEndEvent(MEvent* value)
{
	this->mMsgSendEndEvent = value;
}

bool UENetClient::canSendNewData()
{
	return (this->mClientBuffer->getSendBuffer()->getBytesAvailable() == 0);
}

void UENetClient::SetRevBufferSize(int size)
{
	int retSize = 0;
	this->mSocket->SetSendBufferSize(size, retSize);      // ReceiveBufferSize 默认 8096 字节
	this->mClientBuffer->SetRevBufferSize(size);
}

MY_END_NAMESPACE