#ifndef __NetCmdDispatchHandle_H
#define __NetCmdDispatchHandle_H

#include "Platform.h"		// uint8
// #include "Map.h"			// UE4 自己的 Tmap
#include "MDictionary.h"
#include "EventDispatchDelegate.h"	// FastDelegate1
#include "GObject.h"
#include "TypeDef.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class MByteBuffer;
class AddOnceEventDispatch;
class NetCmdDispatchInfo;

class NetCmdDispatchHandle : public GObject
{
	M_DECLARE_CLASS(NetCmdDispatchHandle, GObject)

public:
	MDictionary<uint8, AddOnceEventDispatch*> mId2HandleDic;

public:
	NetCmdDispatchHandle();
	virtual ~NetCmdDispatchHandle();

	virtual void init();
	virtual void dispose();

	void addParamHandle(uint8 paramId, EventDispatchDelegate handle);
	void removeParamHandle(uint8 paramId, EventDispatchDelegate handle);

	virtual void handleMsg(uint eventId, NetCmdDispatchInfo* cmd);
};

MY_END_NAMESPACE

#endif