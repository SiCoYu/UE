#include "MyProject.h"
#include "NetClient.h"

//NetClient::NetClient(ISocketHandler& h) 
//	: TcpSocket(h) 
//{
//	SetLineProtocol();
//}
//
//void NetClient::OnConnect() 
//{
//	printf("TestSocket connected, sending QUIT\n");
//	Send("quit\n");
//}
//
//void NetClient::OnConnectFailed() 
//{
//	printf("TestSocket::OnConnectFailed\n");
//	SetCloseAndDelete();
//}
//
//void NetClient::OnLine(const std::string& line) 
//{
//	printf("TestSocket: %s\n", line.c_str());
//}
//
//void NetClient::OnDelete() 
//{
//	printf("TestSocket::OnDelete()\n");
//}
//
//#ifdef ENABLE_RESOLVER
//void NetClient::OnResolved(int id, ipaddr_t a, port_t port) 
//{
//	printf("TestSocket::OnResolved():  %d,  %08x:%d\n", id, a, port);
//	TcpSocket::OnResolved(id, a, port);
//}
//#endif