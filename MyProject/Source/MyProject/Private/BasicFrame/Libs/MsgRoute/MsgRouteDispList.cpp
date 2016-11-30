#include "MyProject.h"
#include "MsgRouteDispList.h"
#include "MsgRouteBase.h"
#include "MsgRouteDispHandle.h"

void MsgRouteDispList::addOneDisp(MsgRouteDispHandle* disp)
{
	if (m_dispList.IndexOf(disp) == -1)
	{
		m_dispList.Add(disp);
	}
}

void MsgRouteDispList::removeOneDisp(MsgRouteDispHandle* disp)
{
	if (m_dispList.IndexOf(disp) != -1)
	{
		m_dispList.Remove(disp);
	}
}

void MsgRouteDispList::handleMsg(MsgRouteBase* msg)
{
	for (auto item : m_dispList.getList())
	{
		item->handleMsg(msg);
	}

	//Ctx.m_instance.m_poolSys.deleteObj(msg);
}