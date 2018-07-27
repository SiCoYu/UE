#include "MyProject.h"
#include "NetCmdNotify.h"
#include "Prequisites.h"
#include "UtilStr.h"
#include "NetModuleDispatchHandle.h"
#include "NetCmdDispatchInfo.h"
#include "SafePointer.h"
#include "MByteBuffer.h"
#include "UtilConvert.h"

MY_BEGIN_NAMESPACE(MyNS)

NetCmdNotify::NetCmdNotify()
	: mRevMsgCnt(0),
	  mHandleMsgCnt(0),
	  mIsStopNetHandle(false)
{
	this->mCmdDispInfo = MY_NEW NetCmdDispatchInfo();
}

NetCmdNotify::~NetCmdNotify()
{

}

void NetCmdNotify::init()
{

}

void NetCmdNotify::dispose()
{
	MY_SAFE_DISPOSE(this->mCmdDispInfo);
}

bool NetCmdNotify::isStopNetHandle()
{
	return mIsStopNetHandle;
}

void NetCmdNotify::setIsStopNetHandle(bool value)
{
	this->mIsStopNetHandle = value;
}

void NetCmdNotify::addOneNofity(NetModuleDispatchHandle* disp)
{
	if (!this->mNetCmdNotify.contains(disp))
    {
		this->mNetCmdNotify.add(disp);
    }
}

void NetCmdNotify::removeOneNotify(NetModuleDispatchHandle* disp)
{
	if (this->mNetCmdNotify.contains(disp))
    {
		this->mNetCmdNotify.remove(disp);
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

		for (auto item : this->mNetCmdNotify.getList())
		{
			item->handleMsg(mCmdDispInfo);
		}
    //}
}

void NetCmdNotify::addOneRevMsg()
{
    ++this->mRevMsgCnt;

	GLogSys->log(
		UtilStr::Format(
			"Receive Msg Num {0}", 
			UtilConvert::convInt2Str(this->mRevMsgCnt)
		)
	);
}

void NetCmdNotify::addOneHandleMsg()
{
    ++this->mHandleMsgCnt;

	GLogSys->log(
		UtilStr::Format(
			"Handle Msg Num {0}", 
			UtilConvert::convInt2Str(this->mHandleMsgCnt)
		)
	);
}

void NetCmdNotify::clearOneRevMsg()
{
    mRevMsgCnt = 0;
	GLogSys->log("Clear Receive Msg Num");
}

void NetCmdNotify::clearOneHandleMsg()
{
    mHandleMsgCnt = 0;
	GLogSys->log("Clear Handle Msg Num");
}

MY_END_NAMESPACE