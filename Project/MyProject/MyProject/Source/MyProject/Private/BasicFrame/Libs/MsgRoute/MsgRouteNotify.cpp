#include "MyProject.h"
#include "MsgRouteNotify.h"
#include "MsgRouteBase.h"
#include "MsgRouteDispatchHandle.h"

MY_BEGIN_NAMESPACE(MyNS)

void MsgRouteNotify::addOneNotify(MsgRouteDispatchHandle* disp)
{
	if (this->mDispatchList.contains(disp))
	{
		this->mDispatchList.add(disp);
	}
}

void MsgRouteNotify::removeOneNotify(MsgRouteDispatchHandle* disp)
{
	if (this->mDispatchList.contains(disp))
	{
		this->mDispatchList.remove(disp);
	}
}

void MsgRouteNotify::handleMsg(MsgRouteBase* msg)
{
	for (auto item : this->mDispatchList.getList())
	{
		item->handleMsg(msg);
	}

	//Ctx.m_instance.mPoolSys.deleteObj(msg);
}

MY_END_NAMESPACE