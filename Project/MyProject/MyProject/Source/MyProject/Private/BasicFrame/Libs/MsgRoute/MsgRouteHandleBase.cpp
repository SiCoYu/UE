#include "MyProject.h"
#include "MsgRouteHandleBase.h"
#include "MsgRouteBase.h"
#include "UtilContainers.h"
#include "UtilStr.h"
#include "Common.h"

MsgRouteHandleBase::MsgRouteHandleBase()
{
	
}

MsgRouteHandleBase::~MsgRouteHandleBase()
{
	
}

void MsgRouteHandleBase::addMsgRouteHandle(MsgRouteId msgRouteId, MEventDispatchAction<IDispatchObject> handle)
{
	if (!this->mId2HandleDic.containsKey((int)msgRouteId))
	{
		this->mId2HandleDic[(int)msgRouteId] = new AddOnceEventDispatch();
	}

	this->mId2HandleDic[(int)msgRouteId].addEventHandle(handle);
}

void MsgRouteHandleBase::removeMsgRouteHandle(MsgRouteId msgRouteId, MEventDispatchAction<IDispatchObject> handle)
{
	if (this->mId2HandleDic.containsKey((int)msgRouteId))
	{
		this->mId2HandleDic[(int)msgRouteId].removeEventHandle(handle);
	}
}

void MsgRouteHandleBase::handleMsg(IDispatchObject* dispObj, uint uniqueId)
{
	MsgRouteBase* msg = (MsgRouteBase*)dispObj;

	int key = ((int)msg->mMsgId);

	if (this.mId2HandleDic.containsKey((int)msg->mMsgId))
	{
		this->mId2HandleDic[key](msg);
	}
	else
	{
		//GLogSys->log(UtilStr::Format(Ctx.m_instance.m_langMgr.getText(LangTypeId.eMsgRoute1, LangItemID.eItem1), (int)msg.mMsgId));
	}
}