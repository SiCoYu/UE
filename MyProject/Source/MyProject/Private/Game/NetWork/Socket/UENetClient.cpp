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

// ������Ϣ
void UENetClient::Send()
{
	MLock mlock(m_sendMutex);

	if (!checkAndUpdateConnect())
	{
		return;
	}

	if (m_dataBuffer->sendBuffer.bytesAvailable == 0)     // ������ͻ�����û��Ҫ���͵�����
	{
		if (m_dataBuffer->sendTmpBuffer.circuleBuffer.size > 0)      // ���������ʱ������������Ҫ��
		{
			m_dataBuffer->getSendData();
		}

		if (m_dataBuffer->sendBuffer.bytesAvailable == 0)        // ������ͻ�������ȷʵû������
		{
			m_msgSendEndEvent.Set();        // ֪ͨ�ȴ��̣߳��������ݶ��������
			return;
		}
	}

	try
	{
		Ctx.m_instance.m_logSys.log(string.Format("��ʼ�����ֽ��� {0} ", m_dataBuffer.sendBuffer.bytesAvailable));

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
		m_msgSendEndEvent.Set();        // �����쳣��֪ͨ�ȴ��̣߳��������ݶ�������ɣ���ֹ�ȴ��̲߳��ܽ���
#endif
		// �����־
		Ctx.m_instance.m_logSys.error(e.Message);
		//Disconnect(0);
	}
}

// ��鲢�Ҹ�������״̬
bool UENetClient::checkAndUpdateConnect()
{
	if (m_pSocket != nullptr && m_pSocket->GetConnectionState() != SCS_Connected)	// �����������״̬
	{
		//if (m_isConnected)
		//{
		//	Ctx.m_instance.m_sysMsgRoute.push(new SocketCloseedMR());
		//}
		m_isConnected = false;
	}

	return m_isConnected;
}