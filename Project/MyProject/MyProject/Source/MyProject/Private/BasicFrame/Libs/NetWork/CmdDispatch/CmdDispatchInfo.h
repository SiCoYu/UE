#pragma once

#include "IDispatchObject.h"
#include "HAL/Platform.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class MByteBuffer;

class CmdDispatchInfo : public IDispatchObject
{
public:
	MByteBuffer* bu;
    uint8 byCmd;
    uint8 byParam;
};

MY_END_NAMESPACE