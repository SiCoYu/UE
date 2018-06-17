#pragma once

#include "NetCmdDispatchHandle.h"
#include "TypeDef.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class IDispatchObject;

class GameTimeCmdHandle : public NetCmdDispatchHandle
{
	M_DECLARE_CLASS(GameTimeCmdHandle, NetCmdDispatchHandle)

public:
	GameTimeCmdHandle();

	virtual void init() override;
	virtual void dispose() override;

	void onParamHandle(IDispatchObject* dispObj, uint eventId = 0);
};

MY_END_NAMESPACE