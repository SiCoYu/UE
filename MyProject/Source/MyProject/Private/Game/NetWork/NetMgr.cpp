#include "MyProject.h"
#include "NetMgr.h"
#include "NetClient.h"
#include "NetThread.h"
#include "NetClientBuffer.h"

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

#ifdef SOCKETS_NAMESPACE
using namespace SOCKETS_NAMESPACE;
#endif


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

NetMgr::NetMgr(StdLog *p)
	: SocketHandler(p)
{
	m_pNetThread = new NetThread(this);
	m_pMutex = new Mutex();

	this->SetSlave();
	this->EnableRelease();
}

NetMgr::~NetMgr() 
{
	m_pNetThread->setExitFlag(true);
	this->Release();
}


void NetMgr::openSocket(std::string ip, uint32 port)
{
	//try
	//{
	//	StdoutLog log;
	//	MyHandler h(&log);

	//	TestSocket ts(h);
	//	printf(">>> TestSocket.Open\n");

	//	ts.Open("192.168.0.101", 10002);
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

	m_pMutex->Lock();

	this->Add(pClient);
	pClient->SetSlaveHandler(this);
	pClient->OnDetached();
	
	m_pMutex->Unlock();
}

void NetMgr::recAndSendMsg()
{
	m_pMutex->Lock();

	const std::map<SOCKET, Socket *>& allSockets = this->AllSockets();
	for (socket_m::iterator it = m_sockets.begin(); it != m_sockets.end(); ++it)
	{
		// 处理接收到的数据
		((NetClient*)(it->second))->getNetClientBuffer()->moveRecvSocket2RecvClient();
		// 处理发送数据
		((NetClient*)(it->second))->sendMsg();
	}

	m_pMutex->Unlock();
}
