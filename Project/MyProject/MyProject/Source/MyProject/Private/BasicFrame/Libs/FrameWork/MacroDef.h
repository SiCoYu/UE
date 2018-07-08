#pragma once

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class MacroDef
{
public:
	static /*const*/ bool ENABLE_LOG;
	static /*const*/ bool DEBUG_SYS;
	static /*const*/ bool XZ_MODE;
	static /*const*/ bool XY_MODE;
	
	static bool ENABLE_LUA_DEBUG;
};

MY_END_NAMESPACE