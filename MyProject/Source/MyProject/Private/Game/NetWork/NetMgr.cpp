#include "MyProject.h"
#include "NetMgr.h"
#include "NetClient.h"

NetMgr::NetMgr(StdLog *p)
	: SocketHandler(p)
{

}

NetMgr::~NetMgr() 
{

}


void NetMgr::openSocket(std::string ip, uint32 port)
{
	NetClient* pClient = new NetClient(*this);
	pClient->Open(ip, port);
	m_pSocketThread = new SocketThread(pClient);
}