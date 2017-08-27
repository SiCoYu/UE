#include "MyProject.h"
#include "MsgRouteHandleBase.h"
#include "MsgRouteBase.h"
#include "UtilContainers.h"
#include "UtilStr.h"
#include "Common.h"

MsgRouteHandleBase()
{
	
}

MsgRouteHandleBase::~MsgRouteHandleBase()
{
	
}

void MsgRouteHandleBase::handleMsg(MsgRouteBase* msg)
{
	int key = ((int)msg->m_msgID);
	if (UtilMap::ContainsKey(mId2HandleDic, key))
	{
		mId2HandleDic[key](msg);
	}
	else
	{
		//GLogSys->log(UtilStr::Format(Ctx.m_instance.m_langMgr.getText(LangTypeId.eMsgRoute1, LangItemID.eItem1), (int)msg.m_msgID));
	}
}