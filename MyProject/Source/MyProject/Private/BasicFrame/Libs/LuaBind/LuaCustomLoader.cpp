#include "MyProject.h"
#include "LuaCustomLoader.h"
#include <string>
#include <string.h>
#include <stdio.h>
#include "luaconf.h"

std::string g_searchsRootPath = "D:/file/opensource/unity-game-git/unitygame/Tools/LuaCppWrap/LuaScript";

void dotAddLoader(lua_State *L)
{
	lua_pushcfunction(L, dotLoadLua);
	int loaderFunc = lua_gettop(L);

	lua_getglobal(L, "package");
	lua_getfield(L, -1, "searchers");
	int loaderTable = lua_gettop(L);

	// Shift table elements right
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
	fileName += ".lua";
	fileName = g_searchsRootPath + "/" + fileName;

	const char* fullPath = fileName.c_str();
	FILE* hFile = nullptr;
	hFile = fopen(fullPath, "r");

	lua_pushcfunction(L, traceback);	// 如果 luaL_loadbuffer 错误,继续调用 traceback
	int oldTop = lua_gettop(L);

	if (hFile == nullptr) 
	{
		lua_pop(L, 1);
		return 0;
	}

	fseek(hFile, 0, SEEK_END);
	int size = ftell(hFile);		// 这个地方是 31 ,明明是 29
	fseek(hFile, 0, SEEK_SET);
	if (size > 0)
	{
		char* buffer = new char[size];
		memset(buffer, 0, size);
		fread(buffer, size, 1, hFile);

		for (int idx = size - 1; idx >= 0; --idx)
		{
			if (buffer[idx] == 0 || buffer[idx] == -1)	// 将最后的 0 或者 -1 减掉, luaL_loadbuffer 长度必须和字符数量相等,并且不能有 0 或者 -1, -1 在 fgetc 读取文件的时候,最后竟然将结束符 -1 也读取出来了,然后 feof 才为 true,奇怪
			{
				--size;
			}
			else
			{
				break;
			}
		}

		fclose(hFile);

		// 不知道为什么,从文件读取进来的字符内容 "function add()\n\treturn 10\nend" ,但是文件检查大小竟然是 31,明明是 29,最后多了两个  "\0\0" ,只要把 size 改成 29 就可以正确执行了
		if (luaL_loadbuffer(L, buffer, size, fileName.c_str()) != LUA_OK)
		{
			lua_pop(L, 1);
		}

		delete buffer;
	}

	//int top = lua_gettop(L);
	//int type = lua_type(L, -1);		// LUA_TFUNCTION
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