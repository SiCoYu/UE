#ifndef __TestClassBind_H
#define __TestClassBind_H

#include "LuaBindInc.h"

/**
 * @url https://segmentfault.com/a/1190000005765697
 */
class TestClassBind
{
public:
	static void bind(lua_State* L);
};

#endif