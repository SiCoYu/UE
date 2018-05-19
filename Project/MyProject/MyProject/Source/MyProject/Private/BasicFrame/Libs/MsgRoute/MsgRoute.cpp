#include "MyProject.h"
#include "MsgRoute.h"

SocketOpenedMR::SocketOpenedMR()
	: MsgRouteBase(MsgRouteId::eMRIDSocketOpened)
{

}

SocketCloseedMR::SocketCloseedMR()
	: MsgRouteBase(MsgRouteId::eMRIDSocketClosed)
{

}

LoadedWebResMR::LoadedWebResMR()
	: MsgRouteBase(MsgRouteId::eMRIDLoadedWebRes)
{

}

void LoadedWebResMR::resetDefault()
{
	//m_task = null;
}

ThreadLogMR::ThreadLogMR()
	: MsgRouteBase(MsgRouteId::eMRIDThreadLog)
{

}