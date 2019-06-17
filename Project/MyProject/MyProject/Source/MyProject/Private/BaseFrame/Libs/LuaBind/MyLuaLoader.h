#ifndef __MyLuaLoader_H
#define __MyLuaLoader_H

/**
 * @brief ������� loadlib.c
 */
#include "lua.hpp"
#include <string>

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class MyLuaLoader
{
public:
	// �Ƴ��ַ������������� 0 �� EOF(-1) ����
	static int removeZeroAndEof(const char* buffer, int size);
	static int checkResult(lua_State *L, int stat, const char *filename);

	static void addCFunctionLualoader(lua_State *L, lua_CFunction handle);
	static void addCClosureLualoader(lua_State *L, lua_CFunction handle);

	static int loadLuaFromBufferUseFunction(lua_State *L);
	static int loadLuaFromFileUseFunction(lua_State *L);

	static int loadLuaFromBufferUseClosure(lua_State *L);
	static int loadLuaFromFileUseClosure(lua_State *L);

	static int loadLuaFromFile(lua_State *L, std::string fileName);

	static int Loader(lua_State *L);
};

MY_END_NAMESPACE

#endif