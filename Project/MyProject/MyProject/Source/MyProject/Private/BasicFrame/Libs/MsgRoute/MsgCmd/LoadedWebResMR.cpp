#include "MyProject.h"
#include "LoadedWebResMR.h"
#include "MsgRouteId.h"

LoadedWebResMR::LoadedWebResMR()
	: MsgRouteBase(MsgRouteId::eMRID_LoadedWebRes)
{

}

void LoadedWebResMR::resetDefault()
{
	//m_task = null;
}