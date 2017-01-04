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
	// �򿪻�����
	L = luaL_newstate();
	luaL_openlibs(L);

	// �� Socket
	luaopen_mime_core(L);
	luaopen_socket_core(L);

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