#include "MyProject.h"
#include "NetDispList.h"
#include "UtilContainers.h"
#include "Common.h"
#include "UtilStr.h"
#include "NetDispHandle.h"

NetDispList::NetDispList()
	: mRevMsgCnt(0),
	  mHandleMsgCnt(0),
	  mIsStopNetHandle(false)
{

}

NetDispList::~NetDispList()
{

}

void NetDispList::init()
{

}

void NetDispList::dispose()
{

}

bool NetDispList::getBStopNetHandle()
{
	return mIsStopNetHandle;
}

void NetDispList::setBStopNetHandle(bool value)
{
	mIsStopNetHandle = value;
}

void NetDispList::addOneDispatch(NetDispHandle* disp)
{
	if (UtilVector::IndexOf(mNetDispList, disp) == -1)
    {
        mNetDispList.push_back(disp);
    }
}

void NetDispList::removeOneDispatch(NetDispHandle* disp)
{
	if (UtilVector::IndexOf(mNetDispList, disp) != -1)
    {
		UtilVector::Remove(mNetDispList, disp);
    }
}

void NetDispList::handleMsg(ByteBuffer* msg)
{
    //if (false == mIsStopNetHandle)  // 如果没有停止网络处理
    //{
        for (auto item : mNetDispList)
        {
            item->handleMsg(msg);
        }
    //}
}

void NetDispList::addOneRevMsg()
{
    ++mRevMsgCnt;

	GLogSys->log(UtilStr::Format("接收到消息数量 {0}", mRevMsgCnt));
}

void NetDispList::addOneHandleMsg()
{
    ++mHandleMsgCnt;

	GLogSys->log(UtilStr::Format("处理消息数量 {0}", mHandleMsgCnt));
}

void NetDispList::clearOneRevMsg()
{
    mRevMsgCnt = 0;
	GLogSys->log("清理接收消息数量");
}

void NetDispList::clearOneHandleMsg()
{
    mHandleMsgCnt = 0;
	GLogSys->log("清理处理消息数量");
}