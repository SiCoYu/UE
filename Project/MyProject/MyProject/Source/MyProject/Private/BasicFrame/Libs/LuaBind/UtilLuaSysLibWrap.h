#ifndef __UtilLuaSysLibWrap_H
#define __UtilLuaSysLibWrap_H

#include <string>
#include "LuaBridgeInc.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class UtilLuaSysLibWrap
{
public:
	static int LUA_MULTRET;		// lua.h  LUA_MULTRET

public:
	inline static void PushTraceback(lua_State *L, lua_CFunction func)
	{
		lua_pushcclosure(L, func, 0);
	}

	inline static int LuaLoadBuffer(lua_State *L, const char * buff, int size, const char * name)
	{
		return luaL_loadbuffer(L, buff, size, name);
	}

	inline static int LuaPCall(lua_State *L, int nArgs, int nResults, int errfunc)
	{
		return lua_pcall(L, nArgs, nResults, errfunc);
	}

	inline static void LuaSetTop(lua_State *L, int newTop)
	{
		lua_settop(L, newTop);
	}

	inline static const char* LuaToString(lua_State *L, int index)
	{
		return lua_tostring(L, index);
	}

	inline static void LuaSetTop(lua_State *L, int newTop)
	{
		lua_settop(L, newTop);
	}

	inline static void LuaPushFunction(lua_State *L, lua_CFunction func)
	{
		lua_pushcclosure(L, func, 0);
	}

	inline static lua_CFunction LuaAtPanic(lua_State *L, lua_CFunction panic)
	{
		return lua_atpanic(L, panic);
	}

	inline static int LuaGetTop(lua_State *L, )
	{
		return lua_gettop(L);
	}

	inline static void LuaRemove(lua_State *L, int index)
	{
		lua_remove(L, index);
	}
};

MY_END_NAMESPACE

#include "UtilLuaSysLibWrap.inl"

#endif