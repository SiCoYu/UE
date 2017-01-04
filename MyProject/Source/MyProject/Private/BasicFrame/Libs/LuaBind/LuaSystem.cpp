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
	// 打开基本库
	L = luaL_newstate();
	luaL_openlibs(L);

	// 打开 Socket
	luaopen_mime_core(L);
	luaopen_socket_core(L);

	// 绑定外部库
	LuaCppBind::bind(L);
}

void LuaSystem::dispose()
{
	lua_close(L);
}

lua_State* LuaSystem::getLuaVM()
{
	return L;
}

void LuaSystem::doString(std::string str)
{
	luaL_dostring(L, str.c_str());
}