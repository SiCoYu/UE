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
	UENetClient* mCurClient;	// ��ǰ����ʹ�õ� Client
	MMutex* mVisitMutex;

	void testSendData(std::string ip, uint32 port);

#ifdef USE_EXTERN_THREAD
	void NetMgr_Extern();
	void recAndSendMsg_Extern();	// ʹ���ⲿ��
	void openSocket_Extern(std::string ip, uint32 port);
#else
	void NetMgr_Inter();
	void recAndSendMsg_Inter();		// ʹ���ڲ���
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
	* @brief �ر� socket
	*/
	virtual void closeSocket(std::string ip, uint32 port);
	virtual void recAndSendMsg();

	/**
	* @brief �رյ�ǰ socket
	*/
	void closeCurSocket();
	ByteBuffer* getMsg();
	// ��ȡ������Ϣ������
	virtual ByteBuffer* getSendBA();
	// ע����������Ƿ��뻺�����壬�������������߳��з���
	virtual void send(bool bnet = true);
	// �ر� App ����Ҫ�ȴ����߳̽���
	void quipApp();
	void sendAndRecData();
};

#endif				// __NETMGR_H