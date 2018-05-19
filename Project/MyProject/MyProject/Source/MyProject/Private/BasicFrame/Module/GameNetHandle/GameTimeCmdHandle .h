#pragma once

#include "NetCmdDispatchHandle.h"

class GameTimeCmdHandle : public NetCmdDispatchHandle
{
public:
	GameTimeCmdHandle();

	virtual void init() override;
	virtual void dispose() override;
};