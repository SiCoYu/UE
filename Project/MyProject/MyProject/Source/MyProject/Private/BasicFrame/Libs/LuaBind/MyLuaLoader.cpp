#include "MyProject.h"
#include "MyLuaLoader.h"
#include <string>
#include <string.h>
#include <stdio.h>
#include "luaconf.h"
#include "Prequisites.h"
//#include <iostream>		// ifstream
//#include <fstream>

MY_BEGIN_NAMESPACE(MyNS)

int MyLuaLoader::removeZeroAndEof(const char* buffer, int size)
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

int MyLuaLoader::checkResult(lua_State *L, int stat, const char *filename)
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

void MyLuaLoader::addCFunctionLualoader(lua_State *L)
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

void MyLuaLoader::addCClosureLualoader(lua_State *L)
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

int MyLuaLoader::loadLuaFromBufferUseFunction(lua_State *L)
{
	std::string fileName = luaL_checkstring(L, 1);
	return MyLuaLoader::loadLuaFromFile(L, fileName);
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
	retCode = MyLuaLoader::checkResult(L, (LUA_OK == luaL_loadfile(L, fileName.c_str())), fileName.c_str());

	return retCode;
}

int MyLuaLoader::loadLuaFromBufferUseClosure(lua_State *L)
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
	retCode = MyLuaLoader::checkResult(L, (LUA_OK == luaL_loadbuffer(L, buffer, size, fileName.c_str())), fileName.c_str());
	lua_remove(L, fnameindex);

	delete[] buffer;
	fclose(hFile);

	return retCode;
}

int MyLuaLoader::loadLuaFromFileUseClosure(lua_State *L)
{
	std::string fileName = luaL_checkstring(L, 1);
	fileName = GFileSys->getLuaPath(fileName);

	if (0 == fileName.length())
	{
		return 1;
	}

	int retCode = 0;
	retCode = MyLuaLoader::checkResult(L, (LUA_OK == luaL_loadfile(L, fileName.c_str())), fileName.c_str());
	return retCode;
}

// 这个仅仅是加载代码，如果要执行，还要调用 lua_pcall 才能执行
int MyLuaLoader::loadLuaFromFile(lua_State *L, std::string fileName)
{
	fileName = GFileSys->getLuaPath(fileName);

	if (0 == fileName.length())
	{
		// 加载失败返回 1
		return 1;
	}
	else
	{
		int retCode = 0;

		const char* fullPath = fileName.c_str();
		FILE* hFile = nullptr;

		/**
		 * @url http://www.cplusplus.com/reference/cstdio/fopen/
		 * In order to open a file as a binary file, a "b" character has to be included in the mode string.
		 */
		hFile = fopen(fullPath, "rb");
		int error = 0;
		int size = 0;
		char* buffer = nullptr;

		if (nullptr != hFile)
		{
			fseek(hFile, 0, SEEK_END);
			error = ferror(hFile);
			size = ftell(hFile);
			error = ferror(hFile);
			fseek(hFile, 0, SEEK_SET);
			error = ferror(hFile);

			buffer = new char[size + 1];
			memset(buffer, 0, size + 1);
			size_t retSize = fread(buffer, size, 1, hFile);
			error = ferror(hFile);

			size = removeZeroAndEof(buffer, size);

			int fnameindex = lua_gettop(L) + 1;
			lua_pushfstring(L, "@%s", fullPath);
			retCode = MyLuaLoader::checkResult(L, (LUA_OK == luaL_loadbuffer(L, buffer, size, fileName.c_str())), fileName.c_str());
			lua_remove(L, fnameindex);

			delete[] buffer;
			fclose(hFile);
		}
		else
		{

		}

		return retCode;
	}
}

MY_END_NAMESPACE