#include "MyProject.h"
#include "MsgRouteDispatchList.h"
#include "MsgRouteBase.h"
#include "MsgRouteDispatchHandle.h"

void MsgRouteDispatchList::addOneDispatch(MsgRouteDispatchHandle* disp)
{
	if (this->mDispatchList.indexOf(disp) == -1)
	{
		this->mDispatchList.add(disp);
	}
}

void MsgRouteDispatchList::removeOneDispatch(MsgRouteDispatchHandle* disp)
{
	if (this->mDispatchList.IndexOf(disp) != -1)
	{
		this->mDispatchList.Remove(disp);
	}
}

void MsgRouteDispatchList::handleMsg(MsgRouteBase* msg)
{
	for (auto item : this->mDispatchList.getList())
	{
		item->handleMsg(msg);
	}

	//Ctx.m_instance.mPoolSys.deleteObj(msg);
}