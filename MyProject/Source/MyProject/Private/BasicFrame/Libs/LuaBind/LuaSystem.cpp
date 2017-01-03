#include <MyProject.h>
#include "LuaSystem.h"
#include "LuaCppBind.h"

LuaSystem::LuaSystem()
{

}

LuaSystem::~LuaSystem()
{

}

void LuaSystem::init()
{
	L = luaL_newstate();
	luaL_openlibs(L);

	LuaCppBind::bind(L);
}

void LuaSystem::dispose()
{
	lua_close(L);
}