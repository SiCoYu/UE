#include "MyProject.h"
#include "UtilMsg.h"
#include "Prequisites.h"
#include "UtilStr.h"
#include "UtilConvert.h"

MY_BEGIN_NAMESPACE(MyNS)

// 发送消息， bnet 如果 true 就直接发送到 socket ，否则直接进入输出消息队列
void UtilMsg::sendMsg(NullUserCmd& msg, bool bnet)
{
	GShareData->mTmpBA = GNetMgr->getSendBA();

	if (GShareData->mTmpBA != nullptr)
    {
		msg.serialize(GShareData->mTmpBA);
    }
    else
    {
		GLogSys->log("socket buffer nullptr");
    }
    if (bnet)
    {
        // 打印日志
		GShareData->mTmpStr = UtilStr::Format(
			"Send msg: byCmd = {0}, byParam = {1}", 
			UtilConvert::convInt2Str(msg.byCmd),
			UtilConvert::convInt2Str(msg.byParam)
		);
		GLogSys->log(GShareData->mTmpStr);
    }
	GNetMgr->send(bnet);
}

void UtilMsg::checkStr(std::string str)
{
	if (UtilStr::IsNullOrEmpty(str))
    {
		GLogSys->log("str is nullptr");
    }
}

// 格式化消息数据到数组形式
void UtilMsg::formatBytes2Array(char* bytes, uint32 len)
{
    std::string str = "{ ";
    bool isFirst = true;
    for (int index = 0; index < (int)len; ++index)
    {
        if (isFirst)
        {
            isFirst = false;
        }
        else
        {
            str += ", ";
        }
        str += bytes[index];
    }

    str += " }";

	GLogSys->log(str);
}

MY_END_NAMESPACE