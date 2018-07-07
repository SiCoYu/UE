#ifndef __UtilLuaSysLibWrap_H
#define __UtilLuaSysLibWrap_H

#include <string>
#include "LuaBridgeInc.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class UtilLuaSysLibWrap
{
	public static int LuaLoadBuffer(lua_State *L, const char * buff, int size, const char * name)
	{
		return luaL_loadbuffer(L, buff, size, name);
	}

	public static int LuaPCall(lua_State *L, int nArgs, int nResults, int errfunc)
	{
		return lua_pcall(L, nArgs, nResults, errfunc);
	}

	public static void LuaSetTop(lua_State *L, int newTop)
	{
		lua_settop(L, newTop);
	}

	public static const char * LuaToString(lua_State *L, int index)
	{
		return lua_tostring(L, index);
	}

	public static void LuaSetTop(lua_State *L, int newTop)
	{
		lua_settop(L, newTop);
	}

	public static void LuaPushFunction(lua_State *L, lua_CFunction func)
	{
		lua_pushcclosure(L, func, 0);
	}
};

MY_END_NAMESPACE

#include "UtilLuaSysLibWrap.inl"

#endif