#ifndef __NetDispHandle_H
#define __NetDispHandle_H

#include <map>

class NetCmdHandleBase;
class ByteBuffer;

class NetDispHandle
{
public:
	std::map<int, NetCmdHandleBase> m_id2DispDic;
    //LuaCSBridgeNetDispHandle m_luaCSBridgeNetDispHandle;     // Lua 网络事件处理器

public:
	virtual void handleMsg(ByteBuffer* msg);
}

#endif