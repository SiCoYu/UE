#ifndef __NETMGR_H
#define __NETMGR_H

#include "Windows/AllowWindowsPlatformTypes.h"

#include <Sockets/StdoutLog.h>
#include <Sockets/SocketHandler.h>
#include <Sockets/Mutex.h>

#include "Windows/HideWindowsPlatformTypes.h"

#include "INetMgr.h"

class NetThread;

#ifdef SOCKETS_NAMESPACE
using namespace SOCKETS_NAMESPACE;
#endif

class NetMgr : public SocketHandler, public INetMgr
{
private:
	NetThread* m_pNetThread;
	Mutex* m_pMutex;

public:
	NetMgr(StdLog *p);
	~NetMgr();

	virtual void openSocket(std::string ip, uint32 port);
	virtual void recAndSendMsg();
};

#endif				// __NETMGR_H