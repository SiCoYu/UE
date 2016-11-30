#include "MyProject.h"
#include "MsgRoute.h"

SocketOpenedMR::SocketOpenedMR()
	: MsgRouteBase(eMRIDSocketOpened)
{

}

SocketCloseedMR::SocketCloseedMR()
	: MsgRouteBase(eMRIDSocketClosed)
{

}

LoadedWebResMR::LoadedWebResMR()
	: MsgRouteBase(eMRIDLoadedWebRes)
{

}

void LoadedWebResMR::resetDefault()
{
	//m_task = null;
}

ThreadLogMR::ThreadLogMR()
	: MsgRouteBase(eMRIDThreadLog)
{

}