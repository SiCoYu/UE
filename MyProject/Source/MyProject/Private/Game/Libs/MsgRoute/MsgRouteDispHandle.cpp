#include "MyProject.h"
#include "MsgRouteDispHandle.h"
#include "MsgRouteBase.h"
#include <string>
#include "UtilContainers.h"
#include "Common.h"
#include "UtilStr.h"
#include "MsgRouteHandleBase.h"

void MsgRouteDispHandle::handleMsg(MsgRouteBase* msg)
{
	std::string textStr = "";
	int key = 0;
	key = (int)msg->m_msgType;
	if (UtilMap::ContainsKey(m_id2DispDic, key))
	{
		//textStr = Ctx.m_instance.m_langMgr.getText(LangTypeId.eMsgRoute1, LangItemID.eItem2);
		g_pLogSys->log(UtilStr::Format(textStr.c_str(), (int)msg->m_msgType));
		m_id2DispDic[key]->handleMsg(msg);
	}
	else
	{
		//textStr = Ctx.m_instance.m_langMgr.getText(LangTypeId.eMsgRoute1, LangItemID.eItem3);
		g_pLogSys->log(UtilStr::Format(textStr.c_str(), (int)msg->m_msgID));
	}
}