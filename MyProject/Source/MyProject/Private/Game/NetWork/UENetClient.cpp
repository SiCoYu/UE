#include "MyProject.h"
#include "UENetClient.h"
#include "NetClientBuffer.h"
#include "SocketSubsystem.h"
#include "Sockets.h"

UENetClient::UENetClient()
	: m_boundEndpoint(FIPv4Address::Any, 0)
{
	m_pSocket = nullptr;
	m_pNetClientBuffer = new NetClientBuffer();
	m_strDesc = "";
	//m_boundEndpoint(FIPv4Address::Any, 0);
}

UENetClient::~UENetClient()
{
	delete m_pNetClientBuffer;
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
	return m_pNetClientBuffer;
}

void UENetClient::sendMsg()
{
	//m_pNetClientBuffer->sendMsg();
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