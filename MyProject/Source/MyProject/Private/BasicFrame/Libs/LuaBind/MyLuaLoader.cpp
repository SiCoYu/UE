#include "MyProject.h"
#include "MyLuaLoader.h"
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
	std::string fileName = luaL_checkstring(L, 1);
	fileName = GFileSys->getLuaPath(fileName);

	if (0 == fileName.length())
	{
		return 1;
	}

	int retCode = 0;

	const char* fullPath = fileName.c_str();
	FILE* hFile = nullptr;
	hFile = fopen(fullPath, "rt");

	fseek(hFile, 0, SEEK_END);
	int size = ftell(hFile);
	fseek(hFile, 0, SEEK_SET);

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

	retCode = checkResult(L, (LUA_OK == luaL_loadbuffer(L, buffer, size, fileName.c_str())), fileName.c_str());
	//retCode = checkResult(L, (LUA_OK == luaL_loadfile(L, fileName.c_str())), fileName.c_str());

	delete[] buffer;
	fclose(hFile);

	return retCode;
}

int checkResult(lua_State *L, int stat, const char *filename)
{
	if (stat) 
	{
		lua_pushstring(L, filename);
		return 2;
	}
	else
	{
		return luaL_error(L, "error loading module '%s' from file '%s':\n\t%s",
			lua_tostring(L, 1), filename, lua_tostring(L, -1));
	}
}