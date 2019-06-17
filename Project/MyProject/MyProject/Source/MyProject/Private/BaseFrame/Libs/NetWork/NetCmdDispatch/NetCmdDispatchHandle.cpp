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
#include "UtilConvert.h"

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

void NetCmdDispatchHandle::addParamHandle(uint8 paramId, EventDispatchDelegate handle)
{
	if (!this->mId2HandleDic.containsKey(paramId))
	{
		AddOnceEventDispatch* addOnceEventDispatch = MY_NEW AddOnceEventDispatch();
		this->mId2HandleDic.add(paramId, addOnceEventDispatch);
	}
	else
	{
		// 日志
	}

	this->mId2HandleDic.value(paramId)->addEventHandle(handle);
}

void NetCmdDispatchHandle::removeParamHandle(uint8 paramId, EventDispatchDelegate handle)
{
	if (this->mId2HandleDic.containsKey(paramId))
	{
		this->mId2HandleDic.value(paramId)->removeEventHandle(handle);
	}
	else
	{

	}
}

void NetCmdDispatchHandle::handleMsg(uint eventId, IDispatchObject* dispObj)
{
	NetCmdDispatchInfo* cmd = (NetCmdDispatchInfo*)dispObj;

	if (this->mId2HandleDic.containsKey(cmd->byParam))
	{
		this->mId2HandleDic[cmd->byParam]->dispatchEvent(cmd->bu);
	}
	else
	{
		GLogSys->log(
			UtilStr::Format(
				"Msg Not Handle: byCmd = {0}, byParam = {1}", 
				UtilConvert::convInt2Str(cmd->byCmd),
				UtilConvert::convInt2Str(cmd->byParam)
			)
		);
	}
}

MY_END_NAMESPACE