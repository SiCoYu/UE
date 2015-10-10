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

// ������Ϣ
void UENetClient::Send()
{
	MLock mlock(m_sendMutex);

	if (!checkAndUpdateConnect())
	{
		return;
	}

	if (m_clientBuffer->getSendBuffer()->getBytesAvailable() == 0)     // ������ͻ�����û��Ҫ���͵�����
	{
		if (m_clientBuffer->getSendTmpBuffer()->getCirculeBuffer()->getSize() > 0)      // ���������ʱ������������Ҫ��
		{
			m_clientBuffer->getSendData();
		}

		if (m_clientBuffer->getSendBuffer()->getBytesAvailable() == 0)        // ������ͻ�������ȷʵû������
		{
			m_msgSendEndEvent->Set();        // ֪ͨ�ȴ��̣߳��������ݶ��������
			return;
		}
	}

	g_pLogSys->log(UtilStr::Format("��ʼ�����ֽ��� {0} ", m_clientBuffer->getSendBuffer()->getBytesAvailable()));

	bool ret = true;
	int bytesSent = 0;
	ret = m_socket->Send(m_clientBuffer->getSendBuffer()->getDynBuff()->getBuff() + m_clientBuffer->getSendBuffer()->getPos(), m_clientBuffer->getSendBuffer()->getBytesAvailable(), bytesSent);
	
	if (!ret)		// �������ʧ��
	{
		m_msgSendEndEvent->Set();        // �����쳣��֪ͨ�ȴ��̣߳��������ݶ�������ɣ���ֹ�ȴ��̲߳��ܽ���
		// �����־
		g_pLogSys->error("����ʧ��");
		//Disconnect(0);
	}
	else
	{
		g_pLogSys->log(UtilStr::Format("���������ֽ��� {0} ", bytesSent));

		if (m_clientBuffer->getSendBuffer().getLength() < m_clientBuffer->getSendBuffer()->getPos() + bytesSent)
		{
			g_pLogSys->log(UtilStr::Format("���������ֽ������� {0}", bytesSent));
			m_clientBuffer->getSendBuffer()->setPos(m_clientBuffer->getSendBuffer().getLength());
		}
		else
		{
			m_clientBuffer->getSendBuffer()->setPos(m_clientBuffer->getSendBuffer()->getPos() + bytesSent);
		}

		if (m_clientBuffer->getSendBuffer()->getBytesAvailable() > 0)     // �����һ�η��͵����ݻ�û������ɣ���������
		{
			Send();                 // ������������
		}
	}
}

// ��������
void UENetClient::Receive()
{
	// ֻ�� socket ���ӵ�ʱ��ż�����������
	if (!m_isConnected)
	{
		// ���մӷ��������ص���Ϣ
		bool ret = true;	// Ĭ���ǽ��յ�
		int32 bytesRead = 0;	// ��ȡ���ܵ��ֽ���
		ret = m_socket->Recv(m_clientBuffer->getDynBuff()->getBuff(), (int)m_clientBuffer->getDynBuff()->getCapacity(), bytesRead, ESocketReceiveFlags::None);

		if (!ret)
		{
			g_pLogSys->error("�������ݳ���");
		}
		else
		{
			if (bytesRead > 0)
			{
				g_pLogSys->log("���յ����� " + read.ToString());
				m_clientBuffer->getDynBuff()->setSize(bytesRead);	// ���ö�ȡ��С
				m_clientBuffer->moveDyn2Raw();             // �����յ������ݷŵ�ԭʼ���ݶ���
				m_clientBuffer->moveRaw2Msg();             // ����������Ϣ�ƶ�����Ϣ������
				Receive();                  // ��������
			}
		}
	}
}

// ��鲢�Ҹ�������״̬
bool UENetClient::checkAndUpdateConnect()
{
	if (m_socket != nullptr && m_socket->GetConnectionState() != SCS_Connected)	// �����������״̬
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
	m_socket->SetSendBufferSize(size, retSize);      // ReceiveBufferSize Ĭ�� 8096 �ֽ�
	m_clientBuffer->SetRevBufferSize(size);
}