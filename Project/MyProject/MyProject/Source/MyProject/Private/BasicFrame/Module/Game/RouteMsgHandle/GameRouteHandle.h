#pragma once

#include "MsgRouteHandleBase.h"

class GameRouteHandle : public MsgRouteHandleBase
{
public:
	GameRouteHandle();

	virtual void init() override;
	virtual void dispose() override;

protected:
	void threadLog(IDispatchObject dispObj, uint);
	void onSocketOpened(IDispatchObject dispObj, uint);
};