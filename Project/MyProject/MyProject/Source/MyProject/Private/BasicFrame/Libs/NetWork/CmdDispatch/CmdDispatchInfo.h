#pragma once

#include "IDispatchObject.h"
#include "HAL/Platform.h"

class MByteBuffer;

class CmdDispatchInfo : public IDispatchObject
{
    public MByteBuffer* bu;
    public uint8 byCmd;
    public uint8 byParam;
};