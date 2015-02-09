#include "MyProject.h"
#include "NetMgr.h"
#include "NetClient.h"
#include "NetThread.h"
#include "NetClientBuffer.h"

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
	this->Release();
}


void NetMgr::openSocket(std::string ip, uint32 port)
{
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