#include "MyProject.h"
#include "NetClient.h"

NetClient::NetClient(ISocketHandler& h) 
	: TcpSocket(h) 
{
	
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