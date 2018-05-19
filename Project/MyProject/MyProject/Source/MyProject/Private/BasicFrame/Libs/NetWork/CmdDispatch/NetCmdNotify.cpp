#include "MyProject.h"
#include "NetCmdNotify.h"
#include "UtilContainers.h"
#include "Common.h"
#include "UtilStr.h"
#include "NetModuleDispatchHandle.h"
#include "CmdDispatchInfo.h"
#include "SafePointer.h"

NetCmdNotify::NetCmdNotify()
	: this->mRevMsgCnt(0),
	  this->mHandleMsgCnt(0),
	  this->mIsStopNetHandle(false)
{
	this->mCmdDispInfo = SAFE_NEW CmdDispatchInfo();
}

NetCmdNotify::~NetCmdNotify()
{

}

void NetCmdNotify::init()
{

}

void NetCmdNotify::dispose()
{

}

bool NetCmdNotify::getBStopNetHandle()
{
	return mIsStopNetHandle;
}

void NetCmdNotify::setBStopNetHandle(bool value)
{
	mIsStopNetHandle = value;
}

void NetCmdNotify::addOneNofity(NetModuleDispatchHandle* disp)
{
	if (UtilVector::IndexOf(mNetDispatchList, disp) == -1)
    {
        mNetDispatchList.push_back(disp);
    }
}

void NetCmdNotify::removeOneNotify(NetModuleDispatchHandle* disp)
{
	if (UtilVector::IndexOf(mNetDispatchList, disp) != -1)
    {
		UtilVector::Remove(mNetDispatchList, disp);
    }
}

void NetCmdNotify::handleMsg(ByteBuffer* msg)
{
    //if (false == mIsStopNetHandle)  // 如果没有停止网络处理
    //{
		uint8 byCmd = 0;
		msg->readUnsignedInt8(byCmd);
		uint8 byParam = 0;
		msg->readUnsignedInt8(byParam);
		msg->setPos(0);

		mCmdDispInfo->bu = msg;
		mCmdDispInfo->byCmd = byCmd;
		mCmdDispInfo->byParam = byParam;

		for (auto item : mNetDispatchList)
		{
			item->handleMsg(mCmdDispInfo);
		}
    //}
}

void NetCmdNotify::addOneRevMsg()
{
    ++mRevMsgCnt;

	GLogSys->log(UtilStr::Format("接收到消息数量 {0}", mRevMsgCnt));
}

void NetCmdNotify::addOneHandleMsg()
{
    ++mHandleMsgCnt;

	GLogSys->log(UtilStr::Format("处理消息数量 {0}", mHandleMsgCnt));
}

void NetCmdNotify::clearOneRevMsg()
{
    mRevMsgCnt = 0;
	GLogSys->log("清理接收消息数量");
}

void NetCmdNotify::clearOneHandleMsg()
{
    mHandleMsgCnt = 0;
	GLogSys->log("清理处理消息数量");
}