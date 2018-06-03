#include "MyProject.h"
#include "NetCmdDispatchHandle.h"
#include "Prequisites.h"
#include "UtilStr.h"
#include "MByteBuffer.h"
#include "AddOnceEventDispatch.h"
#include "NetCmdDispatchInfo.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(NetCmdDispatchHandle, GObject)

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
		this->mId2HandleDic[paramId] = MY_NEW AddOnceEventDispatch();
	}
	else
	{
		// 日志
	}

	this->mId2HandleDic[paramId]->addEventHandle(handle);
}

void NetCmdDispatchHandle::removeParamHandle(int paramId, EventDispatchDelegate handle)
{
	if (this->mId2HandleDic.containsKey(paramId))
	{
		this->mId2HandleDic[paramId]->removeEventHandle(handle);
	}
	else
	{

	}
}

void NetCmdDispatchHandle::handleMsg(NetCmdDispatchInfo* cmd)
{
	if (this->mId2HandleDic.containsKey(cmd->byParam))
	{
		this->mId2HandleDic[cmd->byParam]->dispatchEvent(cmd->bu);
	}
	else
	{
		GLogSys->log(UtilStr::Format("消息没有处理: byCmd = {0},  byParam = {1}", cmd->byCmd, cmd->byParam));
	}
}

MY_END_NAMESPACE