#pragma once

#include "NetCmdDispatchHandle.h"

class IDispatchObject;

class GameTimeCmdHandle : public NetCmdDispatchHandle
{
public:
	GameTimeCmdHandle();

	virtual void init() override;
	virtual void dispose() override;

	void onParamHandle(IDispatchObject* dispObj, uint uniqueId);
};