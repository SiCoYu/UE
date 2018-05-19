#pragma once

#include "NetModuleDispatchHandle.h"
#include "BaseClassDef.h"	// M_DECLARE_SUPER_KW
#include "MClassMacros.h"	// M_DECLARE_CLASS

/**
    * @brief 游戏网络处理
    */
class GameNetNotify : public NetModuleDispatchHandle
{
	M_DECLARE_SUPER_KW(NetModuleDispatchHandle)
	M_DECLARE_CLASS(GameNetNotify)

protected:
	NetCmdDispatchHandle* mNetCmdDispatchHandle;

public:
	GameNetNotify();

	virtual void init() override;
	virtual void dispose() override;
}