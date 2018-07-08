#ifndef __UtilLuaSysLibWrap_H
#define __UtilLuaSysLibWrap_H

#include <string>
#include "LuaBridgeInc.h"
#include "PlatformDefine.h"

// 静态成员变量被 lua.h  LUA_MULTRET 宏定义替换成 -1 ，导致编译错误
//#ifdef LUA_MULTRET
//	#undef LUA_MULTRET
//#endif

MY_BEGIN_NAMESPACE(MyNS)

// lua.h  LUA_MULTRET
//#ifndef LUA_MULTRET
//	#define LUA_MULTRET -1
//#endif

class UtilLuaSysLibWrap
{
public:
	// 被 lua.h  LUA_MULTRET 宏定义替换成 -1 ，导致编译错误
	//static int LUA_MULTRET;		// lua.h  LUA_MULTRET

public:
	inline static void PushTraceback(lua_State *L, lua_CFunction func);
	inline static int LuaLoadBuffer(lua_State *L, const char * buff, int size, const char * name);
	inline static int LuaPCall(lua_State *L, int nArgs, int nResults, int errfunc);
	inline static void LuaSetTop(lua_State *L, int newTop);

	inline static const char* LuaToString(lua_State *L, int index);
	inline static void LuaPushFunction(lua_State *L, lua_CFunction func);
	inline static lua_CFunction LuaAtPanic(lua_State *L, lua_CFunction panic);
	inline static int LuaGetTop(lua_State *L);
	inline static void LuaRemove(lua_State *L, int index);
	inline static  void LuaSetGlobal(lua_State *L, const char* name)
	{
		lua_setglobal(L, name);
	}

	inline static void LuaGetGlobal(lua_State *L, const char* name)
	{
		lua_getglobal(L, name);
	}
	inline static void LuaGetField(lua_State *L, int index, const char* key)
	{
		lua_getfield(L, index, key);
	}

	inline static void LuaRawGet(lua_State *L, int idx)
	{
		lua_rawget(L, idx);
	}

	inline static void LuaRawGetI(lua_State *L, int tableIndex, int index)
	{
		lua_rawgeti(L, tableIndex, index);
	}
	inline static void LuaPushString(lua_State *L, const char* str)
	{
		lua_pushstring(L, str);
	}
	inline static void LuaSetField(lua_State *L, int idx, string key)
	{
		lua_setfield(L, idx, key);
	}
	inline static void LuaPop(lua_State *L, int amount)
	{
		lua_pop(L, amount);
	}
};

MY_END_NAMESPACE

#include "UtilLuaSysLibWrap.inl"

#endif