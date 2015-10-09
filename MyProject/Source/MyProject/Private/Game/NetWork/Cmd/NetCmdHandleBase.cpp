#include "MyProject.h"
#include "NetCmdHandleBase.h"
#include "Common.h"
#include "UtilContainers.h"

void NetCmdHandleBase::handleMsg(ByteBuffer* bu, uint8 byCmd, uint8 byParam)
{
	if (UtilMap::ContainsKey(m_id2HandleDic, byParam))
	{
		m_id2HandleDic[byParam](bu);
	}
	else
	{
		g_pLogSys->log(string.Format("消息没有处理: byCmd = {0},  byParam = {1}", byCmd, byParam));
	}
}