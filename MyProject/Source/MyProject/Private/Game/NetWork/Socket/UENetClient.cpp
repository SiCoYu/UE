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

UENetClient::UENetClient()
	: m_boundEndpoint(FIPv4Address::Any, 0),
	m_isConnected(false)
{
	m_socket = nullptr;
	m_clientBuffer = new ClientBuffer();
	m_strDesc = "";
	//m_boundEndpoint(FIPv4Address::Any, 0);

	m_msgSendEndEvent = new MEvent();
	m_sendMutex = new MMutex();
}

UENetClient::~UENetClient()
{
	delete m_clientBuffer;
	delete m_msgSendEndEvent;
	delete m_sendMutex;
}

bool UENetClient::getRecvThreadStart()
{
	return m_brecvThreadStart;
}

void UENetClient::setRecvThreadStart(bool value)
{
	m_brecvThreadStart = value;
}

bool UENetClient::getIsConnected()
{
	return m_isConnected;
}

void UENetClient::setIsConnected(bool value)
{
	m_isConnected = value;
}

void UENetClient::Disconnect()
{

}

ClientBuffer* UENetClient::getClientBuffer()
{
	return m_clientBuffer;
}

void UENetClient::sendMsg()
{
	//m_clientBuffer->sendMsg();
	testSendData();
}

bool UENetClient::connect(FString ip, uint32 port)
{
	FIPv4Address IPAddress;
	FIPv4Address::Parse(ip, IPAddress);
	m_boundEndpoint = FIPv4Endpoint(IPAddress, port);

	ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	bool result = false;
	if (SocketSubsystem != nullptr)
	{
		m_socket = SocketSubsystem->CreateSocket(NAME_Stream, *m_strDesc, true);

		result = m_socket->Connect(*m_boundEndpoint.ToInternetAddr());
	}

	return result;
}

void UENetClient::testSendData()
{
	int sendByte = 0;
	uint8 data[5] = { 1, 2, 3, 4, 5 };
	if (m_socket != nullptr)
	{
		m_socket->Send(data, 5, sendByte);
	}
}

// 发送消息
void UENetClient::Send()
{
	MLock mlock(m_sendMutex);

	if (!checkAndUpdateConnect())
	{
		return;
	}

	if (m_clientBuffer->getSendBuffer()->getBytesAvailable() == 0)     // 如果发送缓冲区没有要发送的数据
	{
		if (m_clientBuffer->getSendTmpBuffer()->getCirculeBuffer()->getSize() > 0)      // 如果发送临时缓冲区有数据要发
		{
			m_clientBuffer->getSendData();
		}

		if (m_clientBuffer->getSendBuffer()->getBytesAvailable() == 0)        // 如果发送缓冲区中确实没有数据
		{
			m_msgSendEndEvent->Set();        // 通知等待线程，所有数据都发送完成
			return;
		}
	}

	g_pLogSys->log(UtilStr::Format("开始发送字节数 {0} ", m_clientBuffer->getSendBuffer()->getBytesAvailable()));

	bool ret = true;
	int bytesSent = 0;
	ret = m_socket->Send(m_clientBuffer->getSendBuffer()->getDynBuff()->getBuff() + m_clientBuffer->getSendBuffer()->getPos(), m_clientBuffer->getSendBuffer()->getBytesAvailable(), bytesSent);
	
	if (!ret)		// 如果发送失败
	{
		m_msgSendEndEvent->Set();        // 发生异常，通知等待线程，所有数据都发送完成，防止等待线程不能解锁
		// 输出日志
		g_pLogSys->error("发送失败");
		//Disconnect(0);
	}
	else
	{
		g_pLogSys->log(UtilStr::Format("结束发送字节数 {0} ", bytesSent));

		if (m_clientBuffer->getSendBuffer().getLength() < m_clientBuffer->getSendBuffer()->getPos() + bytesSent)
		{
			g_pLogSys->log(UtilStr::Format("结束发送字节数错误 {0}", bytesSent));
			m_clientBuffer->getSendBuffer()->setPos(m_clientBuffer->getSendBuffer().getLength());
		}
		else
		{
			m_clientBuffer->getSendBuffer()->setPos(m_clientBuffer->getSendBuffer()->getPos() + bytesSent);
		}

		if (m_clientBuffer->getSendBuffer()->getBytesAvailable() > 0)     // 如果上一次发送的数据还没发送完成，继续发送
		{
			Send();                 // 继续发送数据
		}
	}
}

// 接受数据
void UENetClient::Receive()
{
	// 只有 socket 连接的时候才继续接收数据
	if (!m_isConnected)
	{
		// 接收从服务器返回的信息
		bool ret = true;	// 默认是接收的
		int32 bytesRead = 0;	// 读取的总的字节数
		ret = m_socket->Recv(m_clientBuffer->getDynBuff()->getBuff(), (int)m_clientBuffer->getDynBuff()->getCapacity(), bytesRead, ESocketReceiveFlags::None);

		if (!ret)
		{
			g_pLogSys->error("接收数据出错");
		}
		else
		{
			if (bytesRead > 0)
			{
				g_pLogSys->log("接收到数据 " + read.ToString());
				m_clientBuffer->getDynBuff()->setSize(bytesRead);	// 设置读取大小
				m_clientBuffer->moveDyn2Raw();             // 将接收到的数据放到原始数据队列
				m_clientBuffer->moveRaw2Msg();             // 将完整的消息移动到消息缓冲区
				Receive();                  // 继续接收
			}
		}
	}
}

// 检查并且更新连接状态
bool UENetClient::checkAndUpdateConnect()
{
	if (m_socket != nullptr && m_socket->GetConnectionState() != SCS_Connected)	// 如果不是连接状态
	{
		//if (m_isConnected)
		//{
		//	Ctx.m_instance.m_sysMsgRoute.push(new SocketCloseedMR());
		//}
		m_isConnected = false;
	}

	return m_isConnected;
}

MEvent* UENetClient::getMsgSendEndEvent()
{
	return m_msgSendEndEvent;
}

void UENetClient::setMsgSendEndEvent(MEvent* value)
{
	m_msgSendEndEvent = value;
}

bool UENetClient::canSendNewData()
{
	return (m_clientBuffer->getSendBuffer()->getBytesAvailable() == 0);
}

void UENetClient::SetRevBufferSize(int size)
{
	int retSize = 0;
	m_socket->SetSendBufferSize(size, retSize);      // ReceiveBufferSize 默认 8096 字节
	m_clientBuffer->SetRevBufferSize(size);
}