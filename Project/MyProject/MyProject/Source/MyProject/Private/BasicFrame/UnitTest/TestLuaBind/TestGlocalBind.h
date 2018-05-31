#ifndef __TestGlocalBind_H
#define __TestGlocalBind_H

#include "LuaBindInc.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class TestGlocalBind
{
public:
	static void bind(lua_State* L);
};

MY_END_NAMESPACE

#endif