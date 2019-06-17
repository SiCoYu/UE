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

void UtilLuaSysLibWrap::LuaSetGlobal(lua_State *L, const char* name)
{
	lua_setglobal(L, name);
}

void UtilLuaSysLibWrap::LuaGetGlobal(lua_State *L, const char* name)
{
	lua_getglobal(L, name);
}

void UtilLuaSysLibWrap::LuaGetField(lua_State *L, int index, const char* key)
{
	lua_getfield(L, index, key);
}

void UtilLuaSysLibWrap::LuaRawGet(lua_State *L, int idx)
{
	lua_rawget(L, idx);
}

void UtilLuaSysLibWrap::LuaRawGetI(lua_State *L, int tableIndex, int index)
{
	lua_rawgeti(L, tableIndex, index);
}

void UtilLuaSysLibWrap::LuaPushString(lua_State *L, const char* str)
{
	lua_pushstring(L, str);
}

void UtilLuaSysLibWrap::LuaSetField(lua_State *L, int idx, const char* key)
{
	lua_setfield(L, idx, key);
}

void UtilLuaSysLibWrap::LuaPop(lua_State *L, int amount)
{
	lua_pop(L, amount);
}

MY_END_NAMESPACE