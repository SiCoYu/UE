#include "MyProject.h"
#include "NetDispHandle.h"
#include "ByteBuffer.h"
#include "UtilContainers.h"
#include "Common.h"
#include "UtilStr.h"
#include "NetCmdHandleBase.h"

void NetDispHandle::handleMsg(ByteBuffer* msg)
{
    uint8 byCmd = 0;
    msg->readUnsignedInt8(byCmd);
	uint8 byParam = 0;
    msg->readUnsignedInt8(byParam);
    msg->setPos(0);

	if (UtilMap::ContainsKey(m_id2DispDic, byCmd))
    {
		g_pLogSys->log(UtilStr::Format("处理消息: byCmd = {0},  byParam = {1}", byCmd, byParam));
        m_id2DispDic[byCmd]->handleMsg(msg, byCmd, byParam);
    }
    else
    {
		g_pLogSys->log(UtilStr::Format("消息没有处理: byCmd = {0},  byParam = {1}", byCmd, byParam));
    }

    //if(m_luaCSBridgeNetDispHandle != null)
    //{
    //    m_luaCSBridgeNetDispHandle.handleMsg(msg, byCmd, byParam);
    //}
}