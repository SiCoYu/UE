#include "MyProject.h"
#include "UENetClient.h"
#include "NetClientBuffer.h"
#include "SocketSubsystem.h"
#include "Sockets.h"
#include "MEvent.h"
#include "MMutex.h"
#include "MLock.h"

UENetClient::UENetClient()
	: m_boundEndpoint(FIPv4Address::Any, 0),
	m_isConnected(false)
{
	m_pSocket = nullptr;
	m_dataBuffer = new NetClientBuffer();
	m_strDesc = "";
	//m_boundEndpoint(FIPv4Address::Any, 0);

	m_msgSendEndEvent = new MEvent();
	m_sendMutex = new MMutex();
}

UENetClient::~UENetClient()
{
	delete m_dataBuffer;
	delete m_msgSendEndEvent;
	delete m_sendMutex;
}

void UENetClient::OnConnect()
{
	
}

void UENetClient::OnConnectFailed()
{
	
}

void UENetClient::OnDelete()
{

}

void UENetClient::OnRawData(const char *buf, size_t len)
{

}

NetClientBuffer* UENetClient::getNetClientBuffer()
{
	return m_dataBuffer;
}

void UENetClient::sendMsg()
{
	//m_dataBuffer->sendMsg();
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
		m_pSocket = SocketSubsystem->CreateSocket(NAME_Stream, *m_strDesc, true);

		result = m_pSocket->Connect(*m_boundEndpoint.ToInternetAddr());
	}

	return result;
}

void UENetClient::testSendData()
{
	int sendByte = 0;
	uint8 data[5] = { 1, 2, 3, 4, 5 };
	if (m_pSocket != nullptr)
	{
		m_pSocket->Send(data, 5, sendByte);
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

	if (m_dataBuffer->sendBuffer.bytesAvailable == 0)     // 如果发送缓冲区没有要发送的数据
	{
		if (m_dataBuffer->sendTmpBuffer.circuleBuffer.size > 0)      // 如果发送临时缓冲区有数据要发
		{
			m_dataBuffer->getSendData();
		}

		if (m_dataBuffer->sendBuffer.bytesAvailable == 0)        // 如果发送缓冲区中确实没有数据
		{
			m_msgSendEndEvent.Set();        // 通知等待线程，所有数据都发送完成
			return;
		}
	}

	try
	{
		Ctx.m_instance.m_logSys.log(string.Format("开始发送字节数 {0} ", m_dataBuffer.sendBuffer.bytesAvailable));

		IAsyncResult asyncSend = m_socket.BeginSend(m_dataBuffer.sendBuffer.dynBuff.buff, (int)m_dataBuffer.sendBuffer.position, (int)m_dataBuffer.sendBuffer.bytesAvailable, 0, new System.AsyncCallback(SendCallback), 0);
		//bool success = asyncSend.AsyncWaitHandle.WaitOne(m_sendTimeout, true);
		//if (!success)
		//{
		//    Ctx.m_instance.m_logSys.asyncLog(string.Format("SendMsg Timeout {0} ", m_sendTimeout));
		//}
	}
	catch (System.Exception e)
	{
#if NET_MULTHREAD
		m_msgSendEndEvent.Set();        // 发生异常，通知等待线程，所有数据都发送完成，防止等待线程不能解锁
#endif
		// 输出日志
		Ctx.m_instance.m_logSys.error(e.Message);
		//Disconnect(0);
	}
}

// 检查并且更新连接状态
bool UENetClient::checkAndUpdateConnect()
{
	if (m_pSocket != nullptr && m_pSocket->GetConnectionState() != SCS_Connected)	// 如果不是连接状态
	{
		//if (m_isConnected)
		//{
		//	Ctx.m_instance.m_sysMsgRoute.push(new SocketCloseedMR());
		//}
		m_isConnected = false;
	}

	return m_isConnected;
}