#include "MyProject.h"
#include "MsgRouteHandleBase.h"
#include "MsgRouteBase.h"
#include "UtilStr.h"
#include "Prequisites.h"
#include "AddOnceEventDispatch.h"

MY_BEGIN_NAMESPACE(MyNS)

MsgRouteHandleBase::MsgRouteHandleBase()
{
	
}

MsgRouteHandleBase::~MsgRouteHandleBase()
{
	
}

void MsgRouteHandleBase::init()
{

}

void MsgRouteHandleBase::dispose()
{

}

void MsgRouteHandleBase::addMsgRouteHandle(MsgRouteId msgRouteId, EventDispatchDelegate handle)
{
	if (!this->mId2HandleDic.containsKey((int)msgRouteId))
	{
		this->mId2HandleDic[(int)msgRouteId] = MY_NEW AddOnceEventDispatch();
	}

	this->mId2HandleDic[(int)msgRouteId]->addEventHandle(handle);
}

void MsgRouteHandleBase::removeMsgRouteHandle(MsgRouteId msgRouteId, EventDispatchDelegate handle)
{
	if (this->mId2HandleDic.containsKey((int)msgRouteId))
	{
		this->mId2HandleDic[(int)msgRouteId]->removeEventHandle(handle);
	}
}

void MsgRouteHandleBase::handleMsg(IDispatchObject* dispObj, uint uniqueId)
{
	MsgRouteBase* msg = (MsgRouteBase*)dispObj;

	int key = ((int)msg->mMsgId);

	if (this->mId2HandleDic.containsKey((int)msg->mMsgId))
	{
		this->mId2HandleDic[key]->dispatchEvent(msg);
	}
	else
	{
		//GLogSys->log(UtilStr::Format(Ctx.m_instance.m_langMgr.getText(LangTypeId.eMsgRoute1, LangItemID.eItem1), (int)msg.mMsgId));
	}
}

MY_END_NAMESPACE