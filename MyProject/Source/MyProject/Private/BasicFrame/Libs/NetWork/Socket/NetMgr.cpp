#include "MyProject.h"
#include "NetMgr.h"
#include "NetThread.h"
#include "ClientBuffer.h"
#include <sstream>
#include "MMutex.h"
#include "UtilContainers.h"
#include "ByteBuffer.h"
#include "MLock.h"
#include "Common.h"
#include "MEvent.h"

#ifdef USE_EXTERN_THREAD
	#include "NetTCPClient.h"
	#include "Windows/AllowWindowsPlatformTypes.h"

	#ifdef _WIN32
	#pragma warning(disable:4786)
	#endif
	#include <Sockets/StdoutLog.h>
	#include <Sockets/SocketHandler.h>
	#include <Sockets/TcpSocket.h>
	#include <Sockets/ListenSocket.h>
	#include <Sockets/Utility.h>
	#include <Sockets/Parse.h>
	#include <Sockets/HttpGetSocket.h>
	#include <Sockets/Socket.h>
	#include <Sockets/HttpDebugSocket.h>
	#include <iostream>

	#include "Windows/HideWindowsPlatformTypes.h"

#else
	#include "UENetThread.h"
	#include "UENetClient.h"
#endif

#include "Core.h"

#ifdef USE_EXTERN_THREAD

	#ifdef SOCKETS_NAMESPACE
	using namespace SOCKETS_NAMESPACE;
	#endif

#endif

#ifdef USE_EXTERN_THREAD
class MyHandler : public SocketHandler
{
public:
	MyHandler(StdLog *p) : SocketHandler(p), m_done(false), m_quit(false) {}
	~MyHandler() {}

	void List(TcpSocket *p) {
		for (socket_m::iterator it = m_sockets.begin(); it != m_sockets.end(); it++)
		{
			Socket *p0 = (*it).second;
//#ifdef ENABLE_POOL
//			if (dynamic_cast<ISocketHandler::PoolSocket *>(p0))
//			{
//				p->Send("PoolSocket\n");
//			}
//			else
//#endif
//				if (dynamic_cast<HttpGetSocket *>(p0))
//				{
//					p->Send("HttpGetSocket\n");
//				}
//				else
//					if (dynamic_cast<TcpSocket *>(p0))
//					{
//						p->Send("TcpSocket\n");
//					}
//					else
//					{
//						p->Send("Some kind of Socket\n");
//					}
		}
	}
	void SetQuit() { m_quit = true; }
	bool Quit() { return m_quit; }
	void CheckHtml() {
		if (m_done)
		{
			if (m_ok)
				printf("Html OK:\n%s\n", m_html.c_str());
			else
				printf("Html Failed\n");
			m_done = false;
		}
	}

	std::string m_html;
	bool m_ok;
	bool m_done;

private:
	bool m_quit;
};

class TestSocket : public TcpSocket
{
public:
	TestSocket(ISocketHandler& h) : TcpSocket(h) {
		SetLineProtocol();
	}
	void OnConnect() {
		printf("TestSocket connected, sending QUIT\n");
		Send("quit\n");
	}
	void OnConnectFailed() {
		printf("TestSocket::OnConnectFailed\n");
		SetCloseAndDelete();
	}
	void OnLine(const std::string& line) {
		printf("TestSocket: %s\n", line.c_str());
	}
	void OnDelete() {
		printf("TestSocket::OnDelete()\n");
	}
#ifdef ENABLE_RESOLVER
	void OnResolved(int id, ipaddr_t a, port_t port) {
		printf("TestSocket::OnResolved():  %d,  %08x:%d\n", id, a, port);
		TcpSocket::OnResolved(id, a, port);
	}
#endif
};

#endif

#ifdef USE_EXTERN_THREAD
NetMgr::NetMgr(StdLog *p)
	: SocketHandler(p)
#else
NetMgr::NetMgr()
#endif
{
#ifdef USE_EXTERN_THREAD
	NetMgr_Extern();
#else
	NetMgr_Inter();
#endif
}

#ifdef USE_EXTERN_THREAD
void NetMgr::NetMgr_Extern()
{
	mNetThread = new NetThread(this);
	mMutex = new Mutex();

	this->SetSlave();
	this->EnableRelease();
}
#endif

#ifndef USE_EXTERN_THREAD
void NetMgr::NetMgr_Inter()
{
	mVisitMutex = new MMutex();
	startThread();
}
#endif

NetMgr::~NetMgr() 
{
	mNetThread->setExitFlag(true);
#ifdef USE_EXTERN_THREAD
	this->Release();
#endif

	delete mVisitMutex;
}

void NetMgr::startThread()
{
	//mNetThread = new UENetThread(this);
	//m_pRenderingThread = FRunnableThread::Create(mNetThread, TEXT("NetThread"), 0, TPri_Normal, FPlatformAffinity::GetNoAffinityMask());
	//mNetThread->m_pTaskGraphBoundSyncEvent->Wait();

	// 函数 FRunnableThread::Create 第二个参数一定是款字节字符串，如果是多字节就会编译报错
	mNetThread = new UENetThread(this, "NetThread");
	mNetThread->start();
	mNetThread->getSyncEventPtr()->Wait();
}

void NetMgr::openSocket(std::string ip, uint32 port)
{
#ifdef USE_EXTERN_THREAD
	openSocket_Extern(ip, port);
#else
	openSocket_Inter(ip, port);
#endif
}

void NetMgr::closeSocket(std::string ip, uint32 port)
{
	std::stringstream strStream;
	strStream << ip << "&" << port;
	std::string key = strStream.str();
	if (UtilMap::ContainsKey(mId2ClientDic, key))	// 如果没有这个 NetClient
	{
		// 关闭 socket 之前要等待所有的数据都发送完成，如果发送一直超时，可能就卡在这很长时间
		mId2ClientDic[key]->getMsgSendEndEvent()->Reset();        // 重置信号
		mId2ClientDic[key]->getMsgSendEndEvent()->WaitOne();      // 阻塞等待数据全部发送完成

		mVisitMutex->Lock();
		{
			mId2ClientDic[key]->Disconnect();
			UtilMap::Remove(mId2ClientDic, key);
		}
		mVisitMutex->Unlock();
		mCurClient = nullptr;
	}
}

#ifdef USE_EXTERN_THREAD
void NetMgr::openSocket_Extern(std::string ip, uint32 port)
{
	//try
	//{
	//	StdoutLog log;
	//	MyHandler h(&log);

	//	TestSocket ts(h);
	//	printf(">>> TestSocket.Open\n");

	//	ts.Open("192.168.125.17", 10002);
	//	ts.Send("aaaaaaaaabbbbbbbbb");

	//	printf(">>> Adding TestSocket\n");
	//	h.Add(&ts);

	//	printf(">>> Enter mainloop\n");
	//	h.Select(0, 0);
	//	while (!h.Quit())
	//	{
	//		h.Select(1, 0);
	//	}
	//	printf(">>> Leaving mainloop\n");
	//}
	//catch (const Exception& e)
	//{
	//	std::cerr << e.ToString() << std::endl;
	//}
	//catch (const std::exception& e)
	//{
	//	std::cerr << e.what() << std::endl;
	//}

	NetClient* pClient = new NetClient(*this);
	bool success = pClient->Open(ip, port);

	mMutex->Lock();

	this->Add(pClient);
	pClient->SetSlaveHandler(this);
	pClient->OnDetached();

	mMutex->Unlock();
}
#endif

#ifndef USE_EXTERN_THREAD
void NetMgr::openSocket_Inter(std::string ip, uint32 port)
{
	std::stringstream strStream;
	strStream << ip << "&" << port;
	std::string ipId = strStream.str();
	if (!UtilMap::ContainsKey(mId2ClientDic, ipId))	// 如果没有这个 NetClient
	{
		mId2ClientDic[ipId] = new UENetClient();
		mId2ClientDic[ipId]->connect(ip.c_str(), port);

		testSendData(ip, port);
	}
}
#endif

void NetMgr::recAndSendMsg()
{
#ifdef USE_EXTERN_THREAD
	recAndSendMsg_Extern();
#else
	recAndSendMsg_Inter();
#endif
}

#ifdef USE_EXTERN_THREAD
void NetMgr::recAndSendMsg_Extern()
{
	mMutex->Lock();

	const std::map<SOCKET, Socket *>& allSockets = this->AllSockets();
	for (socket_m::iterator it = m_sockets.begin(); it != m_sockets.end(); ++it)
	{
		// 处理接收到的数据
		((NetClient*)(it->second))->getNetClientBuffer()->moveRecvSocket2RecvClient();
		// 处理发送数据
		((NetClient*)(it->second))->sendMsg();
	}

	mMutex->Unlock();
}
#endif

#ifndef USE_EXTERN_THREAD
void NetMgr::recAndSendMsg_Inter()
{

}
#endif

void NetMgr::testSendData(std::string ip, uint32 port)
{
	std::stringstream strStream;
	strStream << ip << "&" << port;
	std::string ipId = strStream.str();
	if (UtilMap::ContainsKey(mId2ClientDic, ipId))
	{
		mId2ClientDic[ipId]->sendMsg();
	}
}

void NetMgr::closeCurSocket()
{
	if (mCurClient != nullptr)
	{
		std::string ip;
		int port;

		ip = mCurClient->mIp;
		port = mCurClient->mPort;

		std::stringstream strStream;
		strStream << ip << "&" << port;
		std::string key = strStream.str();

		// 关闭 socket 之前要等待所有的数据都发送完成
		//m_id2SocketDic[key].msgSendEndEvent.Reset();        // 重置信号
		//m_id2SocketDic[key].msgSendEndEvent.WaitOne();      // 阻塞等待数据全部发送完成

		if (UtilMap::ContainsKey(mId2ClientDic, key))
		{
#if NET_MULTHREAD
			using (MLock mlock = new MLock(mVisitMutex))
#endif
			{
				mId2ClientDic[key]->Disconnect();
				UtilMap::ContainsKey(mId2ClientDic, key);
			}
			mCurClient = nullptr;
		}
	}
}

ByteBuffer* NetMgr::getMsg()
{
	if (mCurClient != nullptr)
	{
		return mCurClient->getClientBuffer()->getMsg();
	}

	return nullptr;
}

ByteBuffer* NetMgr::getSendBA()
{
	if (mCurClient != nullptr)
	{
		mCurClient->getClientBuffer()->getSendData()->clear();
		return mCurClient->getClientBuffer()->getSendData();
	}

	return nullptr;
}

// 注意这个仅仅是放入缓冲区冲，真正发送在子线程中发送
void NetMgr::send(bool bnet)
{
	if (mCurClient != nullptr)
	{
		mCurClient->getClientBuffer()->send(bnet);
	}
	else
	{
		GLogSys->log("current socket null");
	}
}

// 关闭 App ，需要等待子线程结束
void NetMgr::quipApp()
{
	closeCurSocket();
	mNetThread->setExitFlag(true);        // 设置退出标志
	mNetThread->join();                 // 等待线程结束
}

void NetMgr::sendAndRecData()
{
	MLock mlock(mVisitMutex);
	{
		// 从原始缓冲区取数据，然后放到解压和解密后的消息缓冲区中
		ClientMapIte _beginIte;
		ClientMapIte _endIte;
		_beginIte = mId2ClientDic.begin();
		_endIte = mId2ClientDic.end();
		for (; _beginIte != _endIte; ++_beginIte)
		{
			if (!_beginIte->second->getRecvThreadStart() && _beginIte->second->getIsConnected())
			{
				_beginIte->second->setRecvThreadStart(true);
				_beginIte->second->Receive();
			}

			// 处理接收到的数据
			//socket.dataBuffer.moveRaw2Msg();
			// 处理发送数据
			if (_beginIte->second->canSendNewData())        // 只有上一次发送的数据全部发送出去后，才能继续发送新的数据
			{
				_beginIte->second->Send();
			}
		}
	}
}

#if MSG_ENCRIPT
void NetMgr::setCryptKey(byte[] encrypt)
{
	mCurClient.dataBuffer.setCryptKey(encrypt);
}
#endif