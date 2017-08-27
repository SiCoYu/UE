#ifndef __NetDispHandle_H
#define __NetDispHandle_H

#include <map>
#include "Platform.h"		// uint8

class NetCmdHandleBase;
class ByteBuffer;

class NetDispHandle
{
public:
	std::map<uint8, NetCmdHandleBase*> mId2DispDic;
    //LuaCSBridgeNetDispHandle m_luaCSBridgeNetDispHandle;     // Lua 网络事件处理器

public:
	NetDispHandle();
	virtual ~NetDispHandle();

	virtual void handleMsg(ByteBuffer* msg);
};

#endif