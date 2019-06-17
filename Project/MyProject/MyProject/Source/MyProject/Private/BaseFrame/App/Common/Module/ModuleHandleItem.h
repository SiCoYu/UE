#pragma once

#include "ModuleId.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class IModule;

/**
 * @brief 单一模块处理 Item 
 */
class ModuleHandleItem
{
public:
	ModuleId mModuleId;
    bool mIsLoaded;         // 指明模块是否加载过
	IModule* mModule;
};

MY_END_NAMESPACE