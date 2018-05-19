#include "MyProject.h"
#include "NetCmdDispatchHandle.h"
#include "Common.h"
#include "UtilContainers.h"
#include "UtilStr.h"
#include "MByteBuffer.h"

NetCmdDispatchHandle::NetCmdDispatchHandle()
{
	
}

NetCmdDispatchHandle::~NetCmdDispatchHandle()
{
	
}

void NetCmdDispatchHandle::init()
{

}

void NetCmdDispatchHandle::dispose()
{

}

void NetCmdDispatchHandle::addParamHandle(int paramId, EventDispatchDelegate handle)
{
	if (!this->mId2HandleDic.containsKey(paramId))
	{
		this.mId2HandleDic[paramId] = new AddOnceEventDispatch();
	}
	else
	{
		// 日志
	}

	this.mId2HandleDic[paramId].addEventHandle(handle);
}

void NetCmdDispatchHandle::removeParamHandle(int paramId, EventDispatchDelegate handle)
{
	if (this->mId2HandleDic.containsKey(paramId))
	{
		this->mId2HandleDic[paramId].removeEventHandle(handle);
	}
	else
	{

	}
}

void NetCmdDispatchHandle::handleMsg(CmdDispatchInfo* cmd)
{
	if (this->mId2HandleDic.containsKey(cmd.byParam))
	{
		this->mId2HandleDic[cmd->byParam].dispatchEvent(cmd->bu);
	}
	else
	{
		GLogSys->log(UtilStr::Format("消息没有处理: byCmd = {0},  byParam = {1}", cmd->byCmd, cmd->byParam));
	}
}