#pragma once

#include "ModuleDef.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 模块系统
 */
class IModuleSys
{
    virtual void loadModule(ModuleId moduleID) = 0;
	virtual void unloadModule(ModuleId moduleID) = 0;
};

MY_END_NAMESPACE