#pragma once

#include "NetCmdDispatchHandle.h"
#include "BaseClassDef.h"

class IDispatchObject;

class GameTimeCmdHandle : public NetCmdDispatchHandle
{
	M_DECLARE_SUPER_KW(GameTimeCmdHandle)

public:
	GameTimeCmdHandle();

	virtual void init() override;
	virtual void dispose() override;

	void onParamHandle(IDispatchObject* dispObj);
};