#ifndef __NetCmdDispatchHandle_H
#define __NetCmdDispatchHandle_H

#include "Platform.h"		// uint8
// #include "Map.h"			// UE4 自己的 Tmap
#include "MDictionary.h"
#include "EventDispatchDelegate.h"	// FastDelegate1

class ByteBuffer;
class AddOnceEventDispatch;

class NetCmdDispatchHandle
{
public:
	MDictionary<uint8, AddOnceEventDispatch*> mId2HandleDic;

public:
	NetCmdDispatchHandle();
	virtual ~NetCmdDispatchHandle();

	void addParamHandle(int paramId, EventDispatchDelegate handle);
	void removeParamHandle(int paramId, EventDispatchDelegate handle);

	virtual void handleMsg(CmdDispatchInfo* cmd);
};

#endif