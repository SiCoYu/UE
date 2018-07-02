#include "MyProject.h"
#include "MyLuaLoader.h"
#include <string>
#include <string.h>
#include <stdio.h>
#include "luaconf.h"
#include "Prequisites.h"

void addCFunctionLualoader(lua_State *L)
{
	lua_getglobal(L, "package");
	lua_getfield(L, -1, "searchers");
	int loaderTable = lua_gettop(L);

	for (int e = (int)lua_rawlen(L, loaderTable) + 1; e > 1; e--)
	{
		lua_rawgeti(L, loaderTable, e - 1);
		lua_rawseti(L, loaderTable, e);
	}

	lua_pushcfunction(L, loadLuaFromBufferUseFunction);
	lua_rawseti(L, loaderTable, 1);

	lua_settop(L, 0);
}

void addCClosureLualoader(lua_State *L)
{
	lua_getglobal(L, "package");
	int package = lua_gettop(L);
	lua_getfield(L, -1, "searchers");
	int loaderTable = lua_gettop(L);

	for (int e = (int)lua_rawlen(L, loaderTable) + 1; e > 1; e--)
	{
		lua_rawgeti(L, loaderTable, e - 1);
		lua_rawseti(L, loaderTable, e);
	}

	lua_pushvalue(L, package);
	lua_pushinteger(L, 100);
	lua_pushcclosure(L, loadLuaFromBufferUseClosure, 2);
	lua_rawseti(L, loaderTable, 1);

	lua_settop(L, 0);
}

int loadLuaFromBufferUseFunction(lua_State *L)
{
	std::string fileName = luaL_checkstring(L, 1);
	return loadLuaFromFile(fileName);
}

int loadLuaFromFileUseFunction(lua_State *L)
{
	std::string fileName = luaL_checkstring(L, 1);
	fileName = GFileSys->getLuaPath(fileName);

	if (0 == fileName.length())
	{
		return 1;
	}

	int retCode = 0;
	retCode = checkResult(L, (LUA_OK == luaL_loadfile(L, fileName.c_str())), fileName.c_str());
	return retCode;
}

int loadLuaFromBufferUseClosure(lua_State *L)
{
	if (lua_getfield(L, lua_upvalueindex(1), "searchers") != LUA_TTABLE)
	{
		luaL_error(L, "'package.searchers' must be a table");
	}

	int val = lua_tointeger(L, lua_upvalueindex(2));

	std::string fileName = luaL_checkstring(L, 1);
	fileName = GFileSys->getLuaPath(fileName);

	if (0 == fileName.length())
	{
		return 1;
	}

	int retCode = 0;

	const char* fullPath = fileName.c_str();
	FILE* hFile = nullptr;
	hFile = fopen(fullPath, "r");

	fseek(hFile, 0, SEEK_END);
	int size = ftell(hFile);
	fseek(hFile, 0, SEEK_SET);

	char* buffer = new char[size];
	memset(buffer, 0, size);
	fread(buffer, size, 1, hFile);
	size = removeZeroAndEof(buffer, size);

	int fnameindex = lua_gettop(L) + 1;
	lua_pushfstring(L, "@%s", fullPath);
	retCode = checkResult(L, (LUA_OK == luaL_loadbuffer(L, buffer, size, fileName.c_str())), fileName.c_str());
	lua_remove(L, fnameindex);

	delete[] buffer;
	fclose(hFile);

	return retCode;
}

int loadLuaFromFileUseClosure(lua_State *L)
{
	std::string fileName = luaL_checkstring(L, 1);
	fileName = GFileSys->getLuaPath(fileName);

	if (0 == fileName.length())
	{
		return 1;
	}

	int retCode = 0;
	retCode = checkResult(L, (LUA_OK == luaL_loadfile(L, fileName.c_str())), fileName.c_str());
	return retCode;
}

int removeZeroAndEof(const char* buffer, int size)
{
	for (int index = size - 1; index >= 0; --index)
	{
		if (buffer[index] == 0 || buffer[index] == -1)
		{
			--size;
		}
		else
		{
			break;
		}
	}

	return size;
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

int loadLuaFromFile(std::string fileName)
{
	fileName = GFileSys->getLuaPath(fileName);

	if (0 == fileName.length())
	{
		return 1;
	}

	int retCode = 0;

	const char* fullPath = fileName.c_str();
	FILE* hFile = nullptr;
	hFile = fopen(fullPath, "r");

	fseek(hFile, 0, SEEK_END);
	int size = ftell(hFile);
	fseek(hFile, 0, SEEK_SET);

	char* buffer = new char[size];
	memset(buffer, 0, size);
	fread(buffer, size, 1, hFile);
	size = removeZeroAndEof(buffer, size);

	int fnameindex = lua_gettop(L) + 1;
	lua_pushfstring(L, "@%s", fullPath);
	retCode = checkResult(L, (LUA_OK == luaL_loadbuffer(L, buffer, size, fileName.c_str())), fileName.c_str());
	lua_remove(L, fnameindex);

	delete[] buffer;
	fclose(hFile);

	return retCode;
}