#include "MyProject.h"
#include "NetModuleDispatchHandle.h"
#include "ByteBuffer.h"
#include "UtilContainers.h"
#include "Common.h"
#include "UtilStr.h"
#include "NetCmdDispatchHandle.h"
#include "AddOnceEventDispatch.h"

NetModuleDispatchHandle::NetModuleDispatchHandle()
{
	
}

NetModuleDispatchHandle::~NetModuleDispatchHandle()
{
	
}

void NetModuleDispatchHandle::init()
{

}

void NetModuleDispatchHandle::dispose()
{

}

void NetModuleDispatchHandle::addCmdHandle(int cmdId, EventDispatchDelegate handle)
{
	if (!this->mId2DispatchDic.containsKey(cmdId))
	{
		this->mId2DispatchDic[cmdId] = new AddOnceEventDispatch();
	}

	this->mId2DispatchDic[cmdId].addEventHandle(handle);
}

void NetModuleDispatchHandle::removeCmdHandle(int cmdId, EventDispatchDelegate handle)
{
	if (this->mId2DispatchDic.containsKey(cmdId))
	{
		this->mId2DispatchDic[cmdId].removeEventHandle(handle);
	}
	else
	{
		// 日志
	}
}

void NetModuleDispatchHandle::handleMsg(CmdDispatchInfo* cmdDispInfo)
{
	if (UtilMap::ContainsKey(this->mId2DispatchDic, cmdDispInfo->byCmd))
    {
		GLogSys->log(UtilStr::Format("处理消息: byCmd = {0},  byParam = {1}", cmdDispInfo->byCmd, cmdDispInfo->byParam));
		this->mId2DispatchDic[cmdDispInfo->byCmd]->dispatchEvent(cmdDispInfo);
    }
    else
    {
		GLogSys->log(UtilStr::Format("消息没有处理: byCmd = {0},  byParam = {1}", cmdDispInfo->byCmd, cmdDispInfo->byParam));
    }

    //if(mLuaCSBridgeNetDispHandle != null)
    //{
    //    mLuaCSBridgeNetDispHandle.handleMsg(msg, byCmd, byParam);
    //}
}