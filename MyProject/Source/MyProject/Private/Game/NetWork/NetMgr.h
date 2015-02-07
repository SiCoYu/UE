#ifndef __NETMGR_H
#define __NETMGR_H

#include "Windows/AllowWindowsPlatformTypes.h"

#include <Sockets/StdoutLog.h>
#include <Sockets/SocketHandler.h>
#include <Sockets/SocketThread.h>

#include "Windows/HideWindowsPlatformTypes.h"

#include "INetMgr.h"

#ifdef SOCKETS_NAMESPACE
using namespace SOCKETS_NAMESPACE;
#endif

class NetMgr : public SocketHandler, public INetMgr
{
private:
	SocketThread* m_pSocketThread;

public:
	NetMgr(StdLog *p);
	~NetMgr();

	virtual void openSocket(std::string ip, uint32 port);

};

#endif				// __NETMGR_H