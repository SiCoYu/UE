#include "MyProject.h"
#include "MsgRoute.h"

SocketOpenedMR::SocketOpenedMR()
	: MsgRouteBase(MsgRouteId::eMRID_SocketOpened)
{

}

SocketCloseedMR::SocketCloseedMR()
	: MsgRouteBase(MsgRouteId::eMRID_SocketClosed)
{

}

LoadedWebResMR::LoadedWebResMR()
	: MsgRouteBase(MsgRouteId::eMRID_LoadedWebRes)
{

}

void LoadedWebResMR::resetDefault()
{
	//m_task = null;
}

ThreadLogMR::ThreadLogMR()
	: MsgRouteBase(MsgRouteId::eMRID_ThreadLog)
{

}

ThreadLogMR::~ThreadLogMR()
{

}