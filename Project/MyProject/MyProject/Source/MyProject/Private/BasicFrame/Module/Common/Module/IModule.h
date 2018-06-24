#pragma once

#include "ModuleDef.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class IModule
{
    virtual void init() = 0;
	virtual void dispose() = 0;
};

MY_END_NAMESPACE