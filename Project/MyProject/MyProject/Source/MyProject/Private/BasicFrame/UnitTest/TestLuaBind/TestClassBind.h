#ifndef __TestClassBind_H
#define __TestClassBind_H

#include "LuaBindInc.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @url https://segmentfault.com/a/1190000005765697
 */
class TestClassBind
{
public:
	static void bind(lua_State* L);
};

MY_END_NAMESPACE

#endif