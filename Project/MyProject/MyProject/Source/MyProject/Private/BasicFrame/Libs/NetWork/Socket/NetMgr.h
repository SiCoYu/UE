#ifndef __NetMgr_H
#define __NetMgr_H

#include "PlatformDefine.h"
#include "GObject.h"

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
	#include "MDictionary.h"
	#include <string>

	MY_BEGIN_NAMESPACE(MyNS)

	class UENetThread;
	class UENetClient;

	MY_END_NAMESPACE

#endif

MY_BEGIN_NAMESPACE(MyNS)

class MMutex;
class MByteBuffer;


#ifdef USE_EXTERN_THREAD
class NetMgr : public SocketHandler, public INetMgr
#else
class NetMgr : public GObject, public INetMgr
#endif
{
public:
	typedef typename MDictionary<std::string, UENetClient*>::Iterator ClientMapIte;
private:
#ifdef USE_EXTERN_THREAD
	NetThread* mNetThread;
	Mutex* mMutex;
#else
	UENetThread* mNetThread;
	MDictionary<std::string, UENetClient*> mId2ClientDic;
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
	MByteBuffer* getMsg();
	// ��ȡ������Ϣ������
	virtual MByteBuffer* getSendBA();
	// ע����������Ƿ��뻺�����壬�������������߳��з���
	virtual void send(bool bnet = true);
	// �ر����� ����Ҫ�ȴ����߳̽���
	void quipNet();
	void sendAndRecData();
};

MY_END_NAMESPACE

#endif				// __NetMgr_H