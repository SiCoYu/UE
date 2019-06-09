#pragma once

#include "ModuleDef.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 模块系统
 */
class IModuleSys
{
    virtual void loadModule(ModuleId moduleId) = 0;
	virtual void unloadModule(ModuleId moduleId) = 0;
};

MY_END_NAMESPACE