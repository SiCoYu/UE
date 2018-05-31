#include "MyProject.h"
#include "MsgRouteDispatchHandle.h"
#include "MsgRouteBase.h"	// MsgRouteBase
#include <string>
#include "UtilContainers.h"
#include "Prequisites.h"
#include "UtilStr.h"
#include "MsgRouteHandleBase.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(MsgRouteDispatchHandle, GObject)

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
	this->mEventDispatchGroup.addEventHandle(groupId, handle);
}

void MsgRouteDispatchHandle::removeRouteHandle(int groupId, EventDispatchDelegate handle)
{
	this->mEventDispatchGroup.removeEventHandle(groupId, handle);
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

MY_END_NAMESPACE