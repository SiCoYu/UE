#pragma once

#include "ISceneEventNotify.h"
#include "MsgRouteDispatchHandle.h"
#include "MClassInfo.h"
#include "MClassMacros.h"	// M_DECLARE_CLASS
#include "MClassInfo.h"		// MClassInfo
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class GameRouteHandle;

class GameRouteNotify : public MsgRouteDispatchHandle
{
	M_DECLARE_CLASS(GameRouteNotify, MsgRouteDispatchHandle)

public:
    GameRouteHandle* mGameRouteHandle;

public:
	GameRouteNotify();
	virtual void init() override;
	virtual void dispose() override;
};

MY_END_NAMESPACE