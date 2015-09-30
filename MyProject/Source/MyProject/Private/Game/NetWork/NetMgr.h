#ifndef __NETMGR_H
#define __NETMGR_H

#include "PlatformDefine.h"

#ifdef USE_EXTERN_THREAD

	#include "Windows/AllowWindowsPlatformTypes.h"

	#include <Sockets/StdoutLog.h>
	#include <Sockets/SocketHandler.h>
	#include <Sockets/Mutex.h>

	#include "Windows/HideWindowsPlatformTypes.h"

#endif

#include "INetMgr.h"

#ifdef USE_EXTERN_THREAD

	class NetThread;

	#ifdef SOCKETS_NAMESPACE
	using namespace SOCKETS_NAMESPACE;
	#endif

#else
	class UENetThread;
	class UENetClient;
	#include <map>
	#include <string>
#endif

#ifdef USE_EXTERN_THREAD
class NetMgr : public SocketHandler, public INetMgr
#else
class NetMgr : public INetMgr
#endif
{
private:
#ifdef USE_EXTERN_THREAD
	NetThread* m_pNetThread;
	Mutex* m_pMutex;
#else
	UENetThread* m_pNetThread;
	FRunnableThread* m_pRenderingThread;
	std::map<std::string, UENetClient*> m_id2ClientMap;
#endif
	UENetClient* m_curSocket;	// 当前正在使用的 Client

	void testSendData(std::string ip, uint32 port);

#ifdef USE_EXTERN_THREAD
	void NetMgr_Extern();
	void recAndSendMsg_Extern();	// 使用外部库
	void openSocket_Extern(std::string ip, uint32 port);
#else
	void NetMgr_Inter();
	void recAndSendMsg_Inter();		// 使用内部库
	void openSocket_Inter(std::string ip, uint32 port);
	void startThread();
#endif

public:
#ifdef USE_EXTERN_THREAD
	NetMgr(StdLog *p);
#else
	NetMgr();
#endif
	~NetMgr();

	virtual void openSocket(std::string ip, uint32 port);
	/**
	* @brief 关闭 socket
	*/
	virtual void closeSocket(std::string ip, uint32 port);
	virtual void recAndSendMsg();
};

#endif				// __NETMGR_H