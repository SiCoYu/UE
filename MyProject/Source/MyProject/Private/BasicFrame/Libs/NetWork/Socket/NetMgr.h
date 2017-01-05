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

class MMutex;
class ByteBuffer;

#ifdef USE_EXTERN_THREAD
class NetMgr : public SocketHandler, public INetMgr
#else
class NetMgr : public INetMgr
#endif
{
public:
	typedef std::map<std::string, UENetClient*>::iterator ClientMapIte;
private:
#ifdef USE_EXTERN_THREAD
	NetThread* mNetThread;
	Mutex* mMutex;
#else
	UENetThread* mNetThread;
	std::map<std::string, UENetClient*> mId2ClientDic;
#endif
	UENetClient* mCurClient;	// 当前正在使用的 Client
	MMutex* mVisitMutex;

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

public:
	void init();
	void dispose();

	virtual void openSocket(std::string ip, uint32 port);
	/**
	* @brief 关闭 socket
	*/
	virtual void closeSocket(std::string ip, uint32 port);
	virtual void recAndSendMsg();

	/**
	* @brief 关闭当前 socket
	*/
	void closeCurSocket();
	ByteBuffer* getMsg();
	// 获取发送消息缓冲区
	virtual ByteBuffer* getSendBA();
	// 注意这个仅仅是放入缓冲区冲，真正发送在子线程中发送
	virtual void send(bool bnet = true);
	// 关闭 App ，需要等待子线程结束
	void quipApp();
	void sendAndRecData();
};

#endif				// __NETMGR_H