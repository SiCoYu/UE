#pragma once

#include "ModuleDef.h"

/**
 * @brief 模块系统
 */
class IModuleSys
{
    virtual void loadModule(ModuleId moduleID) = 0;
	virtual void unloadModule(ModuleId moduleID) = 0;
};