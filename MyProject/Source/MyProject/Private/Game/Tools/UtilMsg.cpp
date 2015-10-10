#include "MyProject.h"
#include "UtilMsg.h"
#include "Common.h"
#include "UtilStr.h"

// 发送消息， bnet 如果 true 就直接发送到 socket ，否则直接进入输出消息队列
void UtilMsg::sendMsg(stNullUserCmd& msg, bool bnet)
{
	g_pShareData->m_tmpBA = g_pNetMgr->getSendBA();
	if (g_pShareData->m_tmpBA != nullptr)
    {
		msg.serialize(g_pShareData->m_tmpBA);
    }
    else
    {
		g_pLogSys->log("socket buffer null");
    }
    if (bnet)
    {
        // 打印日志
		g_pShareData->m_tmpStr = UtilStr::Format("发送消息: byCmd = {0}, byParam = {1}", msg.byCmd, msg.byParam);
		g_pLogSys->log(g_pShareData->m_tmpStr);
    }
	g_pNetMgr->send(bnet);
}

void UtilMsg::checkStr(std::string str)
{
	if (UtilStr::IsNullOrEmpty(str))
    {
		g_pLogSys->log("str is null");
    }
}

// 格式化消息数据到数组形式
void UtilMsg::formatBytes2Array(char* bytes, uint32 len)
{
    std::string str = "{ ";
    bool isFirst = true;
    for (int idx = 0; idx < len; ++idx)
    {
        if (isFirst)
        {
            isFirst = false;
        }
        else
        {
            str += ", ";
        }
        str += bytes[idx];
    }

    str += " }";

	g_pLogSys->log(str);
}