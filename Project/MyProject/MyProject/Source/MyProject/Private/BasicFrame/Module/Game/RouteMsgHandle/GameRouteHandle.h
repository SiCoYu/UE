#pragma once

#include "MsgRouteHandleBase.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class IDispatchObject;

class GameRouteHandle : public MsgRouteHandleBase
{
	M_DECLARE_CLASS(GameRouteHandle, MsgRouteHandleBase)

public:
	GameRouteHandle();

	virtual void init() override;
	virtual void dispose() override;

protected:
	void threadLog(IDispatchObject* dispObj);
	void onSocketOpened(IDispatchObject* dispObj);
};

MY_END_NAMESPACE