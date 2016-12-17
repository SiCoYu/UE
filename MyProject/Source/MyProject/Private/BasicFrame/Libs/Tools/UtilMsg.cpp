#include "MyProject.h"
#include "UtilMsg.h"
#include "Common.h"
#include "UtilStr.h"

// 发送消息， bnet 如果 true 就直接发送到 socket ，否则直接进入输出消息队列
void UtilMsg::sendMsg(stNullUserCmd& msg, bool bnet)
{
	GShareData->m_tmpBA = GNetMgr->getSendBA();
	if (GShareData->m_tmpBA != nullptr)
    {
		msg.serialize(GShareData->m_tmpBA);
    }
    else
    {
		GLogSys->log("socket buffer null");
    }
    if (bnet)
    {
        // 打印日志
		GShareData->m_tmpStr = UtilStr::Format("发送消息: byCmd = {0}, byParam = {1}", msg.byCmd, msg.byParam);
		GLogSys->log(GShareData->m_tmpStr);
    }
	GNetMgr->send(bnet);
}

void UtilMsg::checkStr(std::string str)
{
	if (UtilStr::IsNullOrEmpty(str))
    {
		GLogSys->log("str is null");
    }
}

// 格式化消息数据到数组形式
void UtilMsg::formatBytes2Array(char* bytes, uint32 len)
{
    std::string str = "{ ";
    bool isFirst = true;
    for (int idx = 0; idx < (int)len; ++idx)
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

	GLogSys->log(str);
}