#pragma once

#include "NetCmdDispatchHandle.h"
#include "BaseClassDef.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class IDispatchObject;

class GameTimeCmdHandle : public NetCmdDispatchHandle
{
	M_DECLARE_SUPER_KW(NetCmdDispatchHandle)

public:
	GameTimeCmdHandle();

	virtual void init() override;
	virtual void dispose() override;

	void onParamHandle(IDispatchObject* dispObj);
};

MY_END_NAMESPACE