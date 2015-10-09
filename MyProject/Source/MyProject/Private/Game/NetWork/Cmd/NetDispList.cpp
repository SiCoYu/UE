#include "MyProject.h"
#include "NetDispList.h"
#include "UtilContainers.h"
#include "Common.h"
#include "UtilStr.h"

NetDispList::NetDispList()
	: m_revMsgCnt(0),
	  m_handleMsgCnt(0),
	  m_bStopNetHandle(false)
{

}

bool NetDispList::getBStopNetHandle()
{
	return m_bStopNetHandle;
}

void NetDispList::setBStopNetHandle(bool value)
{
	m_bStopNetHandle = value;
}

void NetDispList::addOneDisp(NetDispHandle* disp)
{
	if (UtilVector::IndexOf(m_netDispList, disp) == -1)
    {
        m_netDispList.push_back(disp);
    }
}

void NetDispList::removeOneDisp(NetDispHandle* disp)
{
	if (UtilVector::IndexOf(m_netDispList, disp) != -1)
    {
		UtilVector::Remove(m_netDispList, disp);
    }
}

void NetDispList::handleMsg(ByteBuffer* msg)
{
    //if (false == m_bStopNetHandle)  // 如果没有停止网络处理
    //{
        for (auto item : m_netDispList)
        {
            item->handleMsg(msg);
        }
    //}
}

void NetDispList::addOneRevMsg()
{
    ++m_revMsgCnt;

	g_pLogSys->log(UtilStr::Format("接收到消息数量 {0}", m_revMsgCnt));
}

void NetDispList::addOneHandleMsg()
{
    ++m_handleMsgCnt;

	g_pLogSys->log(string.Format("处理消息数量 {0}", m_handleMsgCnt));
}

void NetDispList::clearOneRevMsg()
{
    m_revMsgCnt = 0;
	g_pLogSys->log("清理接收消息数量");
}

void NetDispList::clearOneHandleMsg()
{
    m_handleMsgCnt = 0;
	g_pLogSys->log("清理处理消息数量");
}