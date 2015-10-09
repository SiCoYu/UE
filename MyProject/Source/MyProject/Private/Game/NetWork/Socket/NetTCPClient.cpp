#include "MyProject.h"
#include "NetClient.h"
#include "NetClientBuffer.h"

NetTCPClient::NetTCPClient(ISocketHandler& h)
	: TcpSocket(h) 
{
	m_pNetClientBuffer = new ClientBuffer();
}

NetTCPClient::~NetTCPClient()
{
	delete m_pNetClientBuffer;
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
	return m_dataBuffer;
}

void NetTCPClient::sendMsg()
{
	m_dataBuffer->sendMsg();
}