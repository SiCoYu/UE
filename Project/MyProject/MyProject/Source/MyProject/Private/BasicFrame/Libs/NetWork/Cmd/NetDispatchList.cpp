#include "MyProject.h"
#include "NetDispatchList.h"
#include "UtilContainers.h"
#include "Common.h"
#include "UtilStr.h"
#include "NetDispatchHandle.h"

NetDispatchList::NetDispatchList()
	: mRevMsgCnt(0),
	  mHandleMsgCnt(0),
	  mIsStopNetHandle(false)
{

}

NetDispatchList::~NetDispatchList()
{

}

void NetDispatchList::init()
{

}

void NetDispatchList::dispose()
{

}

bool NetDispatchList::getBStopNetHandle()
{
	return mIsStopNetHandle;
}

void NetDispatchList::setBStopNetHandle(bool value)
{
	mIsStopNetHandle = value;
}

void NetDispatchList::addOneDispatch(NetDispatchHandle* disp)
{
	if (UtilVector::IndexOf(mNetDispatchList, disp) == -1)
    {
        mNetDispatchList.push_back(disp);
    }
}

void NetDispatchList::removeOneDispatch(NetDispatchHandle* disp)
{
	if (UtilVector::IndexOf(mNetDispatchList, disp) != -1)
    {
		UtilVector::Remove(mNetDispatchList, disp);
    }
}

void NetDispatchList::handleMsg(ByteBuffer* msg)
{
    //if (false == mIsStopNetHandle)  // 如果没有停止网络处理
    //{
        for (auto item : mNetDispatchList)
        {
            item->handleMsg(msg);
        }
    //}
}

void NetDispatchList::addOneRevMsg()
{
    ++mRevMsgCnt;

	GLogSys->log(UtilStr::Format("接收到消息数量 {0}", mRevMsgCnt));
}

void NetDispatchList::addOneHandleMsg()
{
    ++mHandleMsgCnt;

	GLogSys->log(UtilStr::Format("处理消息数量 {0}", mHandleMsgCnt));
}

void NetDispatchList::clearOneRevMsg()
{
    mRevMsgCnt = 0;
	GLogSys->log("清理接收消息数量");
}

void NetDispatchList::clearOneHandleMsg()
{
    mHandleMsgCnt = 0;
	GLogSys->log("清理处理消息数量");
}