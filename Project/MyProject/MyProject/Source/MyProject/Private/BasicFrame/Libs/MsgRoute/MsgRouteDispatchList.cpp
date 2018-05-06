#include "MyProject.h"
#include "MsgRouteDispatchList.h"
#include "MsgRouteBase.h"
#include "MsgRouteDispHandle.h"

void MsgRouteDispatchList::addOneDispatch(MsgRouteDispHandle* disp)
{
	if (this->mDispList.IndexOf(disp) == -1)
	{
		this->mDispList.Add(disp);
	}
}

void MsgRouteDispatchList::removeOneDispatch(MsgRouteDispHandle* disp)
{
	if (this->mDispList.IndexOf(disp) != -1)
	{
		this->mDispList.Remove(disp);
	}
}

void MsgRouteDispatchList::handleMsg(MsgRouteBase* msg)
{
	for (auto item : this->mDispList.getList())
	{
		item->handleMsg(msg);
	}

	//Ctx.m_instance.mPoolSys.deleteObj(msg);
}