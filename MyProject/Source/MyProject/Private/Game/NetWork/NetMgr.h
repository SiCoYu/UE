#ifndef __NETMGR_H
#define __NETMGR_H

#include "Windows/AllowWindowsPlatformTypes.h"

#include <Sockets/StdoutLog.h>
#include <Sockets/SocketHandler.h>
#include <Sockets/TcpSocket.h>
#include <iostream>

#ifdef SOCKETS_NAMESPACE
using namespace SOCKETS_NAMESPACE;
#endif

class NetMgr : public SocketHandler
{
public:
	NetMgr(StdLog *p);
	~NetMgr();

	void List(TcpSocket *p);
	void SetQuit();
	bool Quit();
	void CheckHtml();

	std::string m_html;
	bool m_ok;
	bool m_done;

private:
	bool m_quit;
};

#endif				// __NETMGR_H