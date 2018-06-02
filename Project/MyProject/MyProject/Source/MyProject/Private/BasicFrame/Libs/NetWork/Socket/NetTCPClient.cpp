#include "MyProject.h"
#include "NetTCPClient.h"
#include "MClientBuffer.h"

#ifdef USE_EXTERN_THREAD

NetTCPClient::NetTCPClient(ISocketHandler& h)
	: TcpSocket(h) 
{
	this->mClientBuffer = MY_NEW MClientBuffer();
}

NetTCPClient::~NetTCPClient()
{
	MY_DELETE this->mClientBuffer;
}

void NetTCPClient::OnConnect()
{
	this->Send("quit\n");
}

void NetTCPClient::OnConnectFailed()
{
	this->SetCloseAndDelete();
}

void NetTCPClient::OnDelete()
{
	
}

void NetTCPClient::OnRawData(const char *buf, size_t len)
{

}

MClientBuffer* NetTCPClient::getClientBuffer()
{
	return this->mClientBuffer;
}

void NetTCPClient::sendMsg()
{
	//mClientBuffer->sendMsg();
}

#endif	// USE_EXTERN_THREAD