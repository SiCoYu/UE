#ifndef __NetDispatchHandle_H
#define __NetDispatchHandle_H

#include <map>
#include "Platform.h"		// uint8

class NetCmdHandleBase;
class ByteBuffer;

class NetDispatchHandle
{
public:
	std::map<uint8, NetCmdHandleBase*> mId2DispDic;
    //LuaCSBridgeNetDispHandle m_luaCSBridgeNetDispHandle;     // Lua 网络事件处理器

public:
	NetDispatchHandle();
	virtual ~NetDispatchHandle();

	virtual void handleMsg(ByteBuffer* msg);
};

#endif