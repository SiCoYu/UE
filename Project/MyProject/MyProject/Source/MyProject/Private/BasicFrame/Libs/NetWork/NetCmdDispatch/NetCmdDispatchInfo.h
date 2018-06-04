#pragma once

#include "IDispatchObject.h"
#include "HAL/Platform.h"
#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class MByteBuffer;

class NetCmdDispatchInfo : public GObject, public IDispatchObject
{
public:
	MByteBuffer* bu;
    uint8 byCmd;
    uint8 byParam;
};

MY_END_NAMESPACE