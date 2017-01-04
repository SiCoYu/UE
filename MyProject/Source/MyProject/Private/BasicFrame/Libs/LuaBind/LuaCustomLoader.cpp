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

	lua_pushcfunction(L, traceback);	// ��� luaL_loadbuffer ����,�������� traceback
	int oldTop = lua_gettop(L);

	if (hFile == nullptr) 
	{
		lua_pop(L, 1);
		return 0;
	}

	fseek(hFile, 0, SEEK_END);
	int size = ftell(hFile);		// ����ط��� 31 ,������ 29
	fseek(hFile, 0, SEEK_SET);
	if (size > 0)
	{
		char* buffer = new char[size];
		memset(buffer, 0, size);
		fread(buffer, size, 1, hFile);

		for (int idx = size - 1; idx >= 0; --idx)
		{
			if (buffer[idx] == 0 || buffer[idx] == -1)	// ������ 0 ���� -1 ����, luaL_loadbuffer ���ȱ�����ַ��������,���Ҳ����� 0 ���� -1, -1 �� fgetc ��ȡ�ļ���ʱ��,���Ȼ�������� -1 Ҳ��ȡ������,Ȼ�� feof ��Ϊ true,���
			{
				--size;
			}
			else
			{
				break;
			}
		}

		fclose(hFile);

		// ��֪��Ϊʲô,���ļ���ȡ�������ַ����� "function add()\n\treturn 10\nend" ,�����ļ�����С��Ȼ�� 31,������ 29,����������  "\0\0" ,ֻҪ�� size �ĳ� 29 �Ϳ�����ȷִ����
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