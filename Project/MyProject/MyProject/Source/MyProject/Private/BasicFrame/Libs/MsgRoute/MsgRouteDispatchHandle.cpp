#include "MyProject.h"
#include "MsgRouteDispatchHandle.h"
#include "MsgRouteBase.h"
#include <string>
#include "UtilContainers.h"
#include "Common.h"
#include "UtilStr.h"
#include "MsgRouteHandleBase.h"

MsgRouteDispatchHandle::MsgRouteDispatchHandle()
{
	
}

MsgRouteDispatchHandle::~MsgRouteDispatchHandle()
{
	
}

void MsgRouteDispatchHandle::handleMsg(MsgRouteBase* msg)
{
	std::string textStr = "";
	int key = 0;
	key = (int)msg->mMsgType;

	if (UtilMap::ContainsKey(this->mId2DispDic, key))
	{
		//textStr = Ctx.m_instance.m_langMgr.getText(LangTypeId.eMsgRoute1, LangItemID.eItem2);
		GLogSys->log(UtilStr::Format(textStr.c_str(), (int)msg->mMsgType));
		this->mId2DispDic[key]->handleMsg(msg);
	}
	else
	{
		//textStr = Ctx.m_instance.m_langMgr.getText(LangTypeId.eMsgRoute1, LangItemID.eItem3);
		GLogSys->log(UtilStr::Format(textStr.c_str(), (int)msg->mMsgId));
	}
}