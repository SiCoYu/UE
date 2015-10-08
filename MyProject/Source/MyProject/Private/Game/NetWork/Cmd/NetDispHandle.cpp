#include "MyProject.h"
#include "NetCmdHandleBase.h"
#include "ByteBuffer.h"

void NetDispHandle::handleMsg(ByteBuffer msg)
{
    byte byCmd = 0;
    msg.readUnsignedInt8(ref byCmd);
    byte byParam = 0;
    msg.readUnsignedInt8(ref byParam);
    msg.setPos(0);

    if(m_id2DispDic.ContainsKey(byCmd))
    {
        Ctx.m_instance.m_logSys.log(string.Format("处理消息: byCmd = {0},  byParam = {1}", byCmd, byParam));
        m_id2DispDic[byCmd].handleMsg(msg, byCmd, byParam);
    }
    else
    {
        Ctx.m_instance.m_logSys.log(string.Format("消息没有处理: byCmd = {0},  byParam = {1}", byCmd, byParam));
    }

    if(m_luaCSBridgeNetDispHandle != null)
    {
        m_luaCSBridgeNetDispHandle.handleMsg(msg, byCmd, byParam);
    }
}