#include "MyProject.h"
#include "NetTCPClient.h"
#include "ClientBuffer.h"

NetTCPClient::NetTCPClient(ISocketHandler& h)
	: TcpSocket(h) 
{
	m_clientBuffer = new ClientBuffer();
}

NetTCPClient::~NetTCPClient()
{
	delete m_clientBuffer;
}

void NetTCPClient::OnConnect()
{
	Send("quit\n");
}

void NetTCPClient::OnConnectFailed()
{
	SetCloseAndDelete();
}

void NetTCPClient::OnDelete()
{
	
}

void NetTCPClient::OnRawData(const char *buf, size_t len)
{

}

ClientBuffer* NetTCPClient::getClientBuffer()
{
	return m_clientBuffer;
}

void NetTCPClient::sendMsg()
{
	//m_clientBuffer->sendMsg();
}