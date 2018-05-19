#pragma once

#include "MsgRouteHandleBase.h"
#include "BaseClassDef.h"

class GameRouteHandle : public MsgRouteHandleBase
{
	M_DECLARE_SUPER_KW(MsgRouteHandleBase)

public:
	GameRouteHandle();

	virtual void init() override;
	virtual void dispose() override;

protected:
	void threadLog(IDispatchObject* dispObj);
	void onSocketOpened(IDispatchObject* dispObj);
};