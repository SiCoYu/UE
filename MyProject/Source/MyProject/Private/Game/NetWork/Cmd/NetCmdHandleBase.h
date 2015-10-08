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
	typedef FastDelegate1<ByteBuffer*> HandleDelegate;

public:
	std::map<int, HandleDelegate> m_id2HandleDic;

public:
	virtual void handleMsg(ByteBuffer* bu, uint8 byCmd, uint8 byParam);
};

#endif