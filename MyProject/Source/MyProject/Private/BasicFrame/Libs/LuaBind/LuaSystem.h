#pragma once

extern "C" 
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}  // extern "C"

#include "LuaBridge/LuaBridge.h"

/**
* @brief ϵͳ����
*/
class LuaSystem
{
protected:
	lua_State* L;

public:
	LuaSystem();
	~LuaSystem();

protected:
	void init();
	void dispose();
};