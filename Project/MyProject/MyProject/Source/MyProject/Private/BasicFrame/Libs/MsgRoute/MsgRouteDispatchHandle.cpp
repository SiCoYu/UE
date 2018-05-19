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

void MsgRouteDispatchHandle::init()
{

}

void MsgRouteDispatchHandle::dispose()
{

}

void MsgRouteDispatchHandle::addRouteHandle(int groupId, EventDispatchDelegate handle)
{
	this.mEventDispatchGroup.addEventHandle(groupId, handle);
}

void MsgRouteDispatchHandle::removeRouteHandle(int groupId, EventDispatchDelegate handle)
{
	this.mEventDispatchGroup.removeEventHandle(groupId, handle);
}

void MsgRouteDispatchHandle::handleMsg(MsgRouteBase* msg)
{
	std::string textStr = "";

	if (this->mEventDispatchGroup.hasEventHandle((int)msg->mMsgType))
	{
		textStr = "bbb";
		this->mEventDispatchGroup.dispatchEvent((int)msg->mMsgType, msg);
	}
	else
	{
		textStr = "aaaa";
	}
}