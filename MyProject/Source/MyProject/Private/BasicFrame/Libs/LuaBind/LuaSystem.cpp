#include <MyProject.h>
#include <LuaSystem.h>

LuaSystem::LuaSystem();
{

}

LuaSystem::~LuaSystem()
{

}

void LuaSystem::init()
{
	L = luaL_newstate();
	luaL_openlibs(L);
}

void LuaSystem::dispose()
{
	lua_close(L);
}