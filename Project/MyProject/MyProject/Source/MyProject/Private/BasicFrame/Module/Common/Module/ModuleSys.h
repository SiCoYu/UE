#pragma once

#include "MDictionary.h"
#include "ModuleId.h"
#include "ModuleHandleItem.h"
#include "IModuleSys.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 主要是各个模块的管理
 */

class ModuleSys : public IModuleSys
{
protected:
	MDictionary<ModuleId, ModuleHandleItem> mType2ItemDic;

public:
	ModuleSys();

	void init();
	void dispose();

protected:
	void _registerHandler();

public:
	void loadModule(ModuleId moduleId);
	void unloadModule(ModuleId moduleId);
};

MY_END_NAMESPACE