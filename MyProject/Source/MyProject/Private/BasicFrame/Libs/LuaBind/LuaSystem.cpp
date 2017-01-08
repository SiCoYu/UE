#include <MyProject.h>
#include "LuaSystem.h"
#include "LuaCppBind.h"
#include "MyLuaLoader.h"

LuaSystem::LuaSystem()
{

}

LuaSystem::~LuaSystem()
{

}

void LuaSystem::init()
{
	// �򿪻�����
	L = luaL_newstate();
	luaL_openlibs(L);

	// �� Socket
	lua_getglobal(L, "package");
	lua_getfield(L, -1, "preload");

	lua_pushcfunction(L, luaopen_socket_core);
	lua_setfield(L, -2, "socket.core");

	lua_pushcfunction(L, luaopen_mime_core);
	lua_setfield(L, -2, "mime.core");

	lua_pop(L, 2);

	lua_settop(L, 0);

	// ���Զ��������
	addCFunctionLualoader(L);

	// ���ⲿ��
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