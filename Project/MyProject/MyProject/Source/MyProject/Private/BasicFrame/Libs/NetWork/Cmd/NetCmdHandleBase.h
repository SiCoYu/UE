#ifndef __NetCmdHandleBase_H
#define __NetCmdHandleBase_H

#include "Platform.h"		// uint8
// #include "Map.h"			// UE4 自己的 Tmap
#include <map>
#include "FastDelegate.h"	// FastDelegate1

class ByteBuffer;

class NetCmdHandleBase
{
public:
	typedef fastdelegate::FastDelegate1<ByteBuffer*> HandleDelegate;

public:
	std::map<uint8, HandleDelegate*> mId2HandleDic;

public:
	NetCmdHandleBase();
	virtual ~NetCmdHandleBase();

	virtual void handleMsg(ByteBuffer* bu, uint8 byCmd, uint8 byParam);
};

#endif