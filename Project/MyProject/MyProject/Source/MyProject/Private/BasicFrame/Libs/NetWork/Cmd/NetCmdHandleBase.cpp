#include "MyProject.h"
#include "NetCmdHandleBase.h"
#include "Common.h"
#include "UtilContainers.h"
#include "UtilStr.h"
#include "ByteBuffer.h"

NetCmdHandleBase::NetCmdHandleBase()
{
	
}

NetCmdHandleBase::~NetCmdHandleBase()
{
	
}

void NetCmdHandleBase::handleMsg(ByteBuffer* bu, uint8 byCmd, uint8 byParam)
{
	if (UtilMap::ContainsKey(mId2HandleDic, byParam))
	{
		(*mId2HandleDic[byParam])(bu);
	}
	else
	{
		GLogSys->log(UtilStr::Format("消息没有处理: byCmd = {0},  byParam = {1}", byCmd, byParam));
	}
}