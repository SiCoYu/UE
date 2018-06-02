#include "MyProject.h"
#include "NetCmdNotify.h"
#include "Prequisites.h"
#include "UtilStr.h"
#include "NetModuleDispatchHandle.h"
#include "CmdDispatchInfo.h"
#include "SafePointer.h"
#include "MByteBuffer.h"

MY_BEGIN_NAMESPACE(MyNS)

NetCmdNotify::NetCmdNotify()
	: mRevMsgCnt(0),
	  mHandleMsgCnt(0),
	  mIsStopNetHandle(false)
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
	this->mIsStopNetHandle = value;
}

void NetCmdNotify::addOneNofity(NetModuleDispatchHandle* disp)
{
	if (!this->mNetDispatchList.contains(disp))
    {
		this->mNetDispatchList.add(disp);
    }
}

void NetCmdNotify::removeOneNotify(NetModuleDispatchHandle* disp)
{
	if (this->mNetDispatchList.contains(disp))
    {
		this->mNetDispatchList.remove(disp);
    }
}

void NetCmdNotify::handleMsg(MByteBuffer* msg)
{
    //if (false == mIsStopNetHandle)  // 如果没有停止网络处理
    //{
		uint8 byCmd = 0;
		msg->readUnsignedInt8(byCmd);
		uint8 byParam = 0;
		msg->readUnsignedInt8(byParam);
		msg->setPos(0);

		this->mCmdDispInfo->bu = msg;
		this->mCmdDispInfo->byCmd = byCmd;
		this->mCmdDispInfo->byParam = byParam;

		for (auto item : this->mNetDispatchList.getList())
		{
			item->handleMsg(mCmdDispInfo);
		}
    //}
}

void NetCmdNotify::addOneRevMsg()
{
    ++this->mRevMsgCnt;

	GLogSys->log(UtilStr::Format("接收到消息数量 {0}", this->mRevMsgCnt));
}

void NetCmdNotify::addOneHandleMsg()
{
    ++this->mHandleMsgCnt;

	GLogSys->log(UtilStr::Format("处理消息数量 {0}", this->mHandleMsgCnt));
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

MY_END_NAMESPACE