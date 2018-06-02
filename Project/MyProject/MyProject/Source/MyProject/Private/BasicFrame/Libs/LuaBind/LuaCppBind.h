#pragma once

#include "LuaBridgeInc.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class LuaCppBind
{
public:
	static void bind(lua_State* L);
};

MY_END_NAMESPACE