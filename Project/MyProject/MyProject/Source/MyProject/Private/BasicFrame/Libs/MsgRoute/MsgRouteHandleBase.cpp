#include "MyProject.h"
#include "MsgRouteHandleBase.h"
#include "MsgRouteBase.h"
#include "UtilStr.h"
#include "Prequisites.h"
#include "AddOnceEventDispatch.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(MsgRouteHandleBase, GObject)

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
	uint8 key = (uint8)msgRouteId;

	if (!this->mId2HandleDic.containsKey(key))
	{
		this->mId2HandleDic[key] = MY_NEW AddOnceEventDispatch();
	}

	this->mId2HandleDic[key]->addEventHandle(handle);
}

void MsgRouteHandleBase::removeMsgRouteHandle(MsgRouteId msgRouteId, EventDispatchDelegate handle)
{
	uint8 key = ((uint8)msgRouteId);

	if (this->mId2HandleDic.containsKey(key))
	{
		this->mId2HandleDic[key]->removeEventHandle(handle);
	}
}

void MsgRouteHandleBase::handleMsg(uint eventId, IDispatchObject* dispObj)
{
	MsgRouteBase* msg = (MsgRouteBase*)dispObj;

	uint8 key = ((uint8)msg->mMsgId);

	if (this->mId2HandleDic.containsKey(key))
	{
		this->mId2HandleDic[key]->dispatchEvent(msg);
	}
	else
	{
		//GLogSys->log(UtilStr::Format(Ctx.m_instance.m_langMgr.getText(LangTypeId.eMsgRoute1, LangItemID.eItem1), (int)msg.mMsgId));
	}
}

MY_END_NAMESPACE