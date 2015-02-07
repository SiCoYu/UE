#include "MyProject.h"
#include "NetClient.h"
#include "NetClientBuffer.h"

NetClient::NetClient(ISocketHandler& h) 
	: TcpSocket(h) 
{
	m_pNetClientBuffer = new NetClientBuffer();
}

NetClient::~NetClient()
{
	delete m_pNetClientBuffer;
}

void NetClient::OnConnect() 
{
	Send("quit\n");
}

void NetClient::OnConnectFailed() 
{
	SetCloseAndDelete();
}

void NetClient::OnDelete() 
{
	
}

void NetClient::OnRawData(const char *buf, size_t len)
{

}

NetClientBuffer* NetClient::getNetClientBuffer()
{
	return m_pNetClientBuffer;
}

void NetClient::sendMsg()
{
	m_pNetClientBuffer->sendMsg();
}