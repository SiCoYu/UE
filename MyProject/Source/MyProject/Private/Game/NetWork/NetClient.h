#ifndef __NETCLIENT_H
#define __NETCLIENT_H

#include <Sockets/SocketHandler.h>
#include <Sockets/TcpSocket.h>
#include <iostream>

#ifdef SOCKETS_NAMESPACE
using namespace SOCKETS_NAMESPACE;
#endif

class NetClient : public TcpSocket
{
public:
	NetClient(ISocketHandler& h);
	void OnConnect();
	void OnConnectFailed();
	void OnLine(const std::string& line);
	void OnDelete();
#ifdef ENABLE_RESOLVER
	void OnResolved(int id, ipaddr_t a, port_t port);
#endif
};

#endif				// __NETCLIENT_H