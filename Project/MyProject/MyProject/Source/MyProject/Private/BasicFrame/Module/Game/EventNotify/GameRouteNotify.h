#pragma once

#include "ISceneEventNotify.h"
#include "MsgRouteDispatchHandle.h"
#include "BaseClassDef.h"	// M_DECLARE_SUPER_KW
#include "MClassMacros.h"	// M_DECLARE_CLASS
#include "MClassInfo.h"		// MClassInfo

class GameRouteHandle;

class GameRouteNotify : public MsgRouteDispatchHandle
{
	M_DECLARE_SUPER_KW(MsgRouteDispatchHandle)
	M_DECLARE_CLASS(GameRouteNotify)

public:
    GameRouteHandle* mGameRouteHandle;

public:
	GameRouteNotify();
	virtual void init() override;
	virtual void dispose() override;
};