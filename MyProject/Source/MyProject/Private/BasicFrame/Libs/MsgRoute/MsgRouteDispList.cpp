#include "MyProject.h"
#include "MsgRouteDispList.h"
#include "MsgRouteBase.h"
#include "MsgRouteDispHandle.h"

void MsgRouteDispList::addOneDisp(MsgRouteDispHandle* disp)
{
	if (mDispList.IndexOf(disp) == -1)
	{
		mDispList.Add(disp);
	}
}

void MsgRouteDispList::removeOneDisp(MsgRouteDispHandle* disp)
{
	if (mDispList.IndexOf(disp) != -1)
	{
		mDispList.Remove(disp);
	}
}

void MsgRouteDispList::handleMsg(MsgRouteBase* msg)
{
	for (auto item : mDispList.getList())
	{
		item->handleMsg(msg);
	}

	//Ctx.m_instance.mPoolSys.deleteObj(msg);
}