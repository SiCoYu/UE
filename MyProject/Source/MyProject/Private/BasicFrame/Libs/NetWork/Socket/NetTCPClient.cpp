#include "MyProject.h"
#include "NetTCPClient.h"
#include "ClientBuffer.h"

#ifdef USE_EXTERN_THREAD

NetTCPClient::NetTCPClient(ISocketHandler& h)
	: TcpSocket(h) 
{
	mClientBuffer = new ClientBuffer();
}

NetTCPClient::~NetTCPClient()
{
	delete mClientBuffer;
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
	return mClientBuffer;
}

void NetTCPClient::sendMsg()
{
	//mClientBuffer->sendMsg();
}

#endif	// USE_EXTERN_THREAD