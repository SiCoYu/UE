#pragma once

#include "NetModuleDispatchHandle.h"
#include "MClassInfo.h"
#include "MClassMacros.h"	// M_DECLARE_CLASS
#include "MClassInfo.h"		// MClassInfo
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
    * @brief 游戏网络处理
    */
class GameNetNotify : public NetModuleDispatchHandle
{
	M_DECLARE_CLASS(GameNetNotify, NetModuleDispatchHandle)

protected:
	NetCmdDispatchHandle* mNetCmdDispatchHandle;

public:
	GameNetNotify();

	virtual void init() override;
	virtual void dispose() override;
};

MY_END_NAMESPACE