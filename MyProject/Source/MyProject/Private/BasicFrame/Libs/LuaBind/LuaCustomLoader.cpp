#include "MyProject.h"
#include "LuaCustomLoader.h"
#include <string>
#include <string.h>
#include <stdio.h>
#include "luaconf.h"
#include "Common.h"

void dotAddLoader(lua_State *L)
{
	lua_pushcfunction(L, dotLoadLua);
	int loaderFunc = lua_gettop(L);

	lua_getglobal(L, "package");
	lua_getfield(L, -1, "searchers");
	int loaderTable = lua_gettop(L);

	for (int e = (int)lua_rawlen(L, loaderTable) + 1; e > 1; e--)
	{
		lua_rawgeti(L, loaderTable, e - 1);
		lua_rawseti(L, loaderTable, e);
	}
	lua_pushvalue(L, loaderFunc);
	lua_rawseti(L, loaderTable, 1);
	lua_settop(L, 0);
}

int dotLoadLua(lua_State *L)
{
	std::string fileName = lua_tostring(L, 1);
	fileName = GFileSys->getLuaPath(fileName);

	const char* fullPath = fileName.c_str();
	FILE* hFile = nullptr;
	hFile = fopen(fullPath, "rt");
	std::string retErr;

	// 如果 luaL_loadbuffer 错误,继续调用 traceback
	lua_pushcfunction(L, traceback);
	int oldTop = lua_gettop(L);

	if (hFile == nullptr) 
	{
		lua_settop(L, oldTop - 1);
		return 0;
	}

	fseek(hFile, 0, SEEK_END);
	int size = ftell(hFile);
	fseek(hFile, 0, SEEK_SET);

	if (size > 0)
	{
		char* buffer = new char[size];
		memset(buffer, 0, size);
		fread(buffer, size, 1, hFile);

		for (int idx = size - 1; idx >= 0; --idx)
		{
			if (buffer[idx] == 0 || buffer[idx] == -1)
			{
				--size;
			}
			else
			{
				break;
			}
		}

		if (LUA_OK == luaL_loadbuffer(L, buffer, size, fileName.c_str()))
		{
			if (LUA_OK == lua_pcall(L, 0, LUA_MULTRET, oldTop))
			{
				int newTop = lua_gettop(L);
				int retNum = newTop - oldTop;

				int type = lua_type(L, newTop);
				if (LUA_TFUNCTION == type)
				{

				}
				lua_replace(L, oldTop -1);
			}
			else
			{
				retErr = lua_tostring(L, -1);
			}
		}
		else
		{
			retErr = lua_tostring(L, -1);
		}

		delete buffer;
	}

	fclose(hFile);
	lua_settop(L, oldTop);

	return 1;
}

int traceback(lua_State *L)
{
	// debug.traceback ([thread,] [message])
	lua_getglobal(L, "debug");
	lua_getfield(L, -1, "traceback");
	lua_pushvalue(L, 1);
	lua_pushnumber(L, 2);
	lua_call(L, 2, 1);

	char* error;
	if (lua_type(L, -1) == LUA_TSTRING)
	{
		error = (char*)lua_tostring(L, -1);
	}
	return 1;
}