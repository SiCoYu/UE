#include "MyProject.h"
#include "LoadedWebResMR.h"
#include "MsgRouteId.h"

MY_BEGIN_NAMESPACE(MyNS)

LoadedWebResMR::LoadedWebResMR()
	: MsgRouteBase(MsgRouteId::eMRID_LoadedWebRes)
{

}

void LoadedWebResMR::resetDefault()
{
	//m_task = nullptr;
}

MY_END_NAMESPACE