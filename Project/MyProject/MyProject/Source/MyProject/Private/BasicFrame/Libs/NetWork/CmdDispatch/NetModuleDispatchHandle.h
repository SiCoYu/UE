#ifndef __NetModuleDispatchHandle_H
#define __NetModuleDispatchHandle_H

#include <map>
#include "Platform.h"		// uint8
#include "EventDispatchDelegate.h"

class NetCmdDispatchHandle;
class ByteBuffer;
class AddOnceEventDispatch;
class CmdDispatchInfo;

class NetModuleDispatchHandle
{
public:
	std::map<uint8, AddOnceEventDispatch*> mId2DispatchDic;
    //LuaCSBridgeNetDispHandle mLuaCSBridgeNetDispHandle;     // Lua 网络事件处理器

public:
	NetModuleDispatchHandle();
	virtual ~NetModuleDispatchHandle();

	virtual void init();
	virtual void dispose();

	void addCmdHandle(int cmdId, EventDispatchDelegate handle);
	void removeCmdHandle(int cmdId, EventDispatchDelegate handle);

	virtual void handleMsg(CmdDispatchInfo* cmdDispInfo);
};

#endif