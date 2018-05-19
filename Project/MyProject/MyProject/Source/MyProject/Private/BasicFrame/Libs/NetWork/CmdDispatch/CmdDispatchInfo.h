#pragma once

#include "IDispatchObject.h"
#include "HAL/Platform.h"

class MByteBuffer;

class CmdDispatchInfo : public IDispatchObject
{
public:
	MByteBuffer* bu;
    uint8 byCmd;
    uint8 byParam;
};