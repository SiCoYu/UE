#include "MyProject.h"
#include "MsgRouteDispatchList.h"
#include "MsgRouteBase.h"
#include "MsgRouteDispatchHandle.h"

void MsgRouteDispatchList::addOneDispatch(MsgRouteDispatchHandle* disp)
{
	if (this->mDispList.IndexOf(disp) == -1)
	{
		this->mDispList.Add(disp);
	}
}

void MsgRouteDispatchList::removeOneDispatch(MsgRouteDispatchHandle* disp)
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