#ifndef __UtilLuaSysLibWrap_H
	#error "UtilLuaSysLibWrap.inl file can only include in UtilLuaSysLibWrap.h"
#endif

MY_BEGIN_NAMESPACE(MyNS)

void UtilLuaSysLibWrap::PushTraceback(lua_State *L, lua_CFunction func)
{
	lua_pushcclosure(L, func, 0);
}

int UtilLuaSysLibWrap::LuaLoadBuffer(lua_State *L, const char * buff, int size, const char * name)
{
	return luaL_loadbuffer(L, buff, size, name);
}

int UtilLuaSysLibWrap::LuaPCall(lua_State *L, int nArgs, int nResults, int errfunc)
{
	return lua_pcall(L, nArgs, nResults, errfunc);
}

void UtilLuaSysLibWrap::LuaSetTop(lua_State *L, int newTop)
{
	lua_settop(L, newTop);
}

const char* UtilLuaSysLibWrap::LuaToString(lua_State *L, int index)
{
	return lua_tostring(L, index);
}

void UtilLuaSysLibWrap::LuaPushFunction(lua_State *L, lua_CFunction func)
{
	lua_pushcclosure(L, func, 0);
}

lua_CFunction UtilLuaSysLibWrap::LuaAtPanic(lua_State *L, lua_CFunction panic)
{
	return lua_atpanic(L, panic);
}

int UtilLuaSysLibWrap::LuaGetTop(lua_State *L)
{
	return lua_gettop(L);
}

void UtilLuaSysLibWrap::LuaRemove(lua_State *L, int index)
{
	lua_remove(L, index);
}

MY_END_NAMESPACE