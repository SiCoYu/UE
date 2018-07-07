#ifndef __MyLuaLoader_H
#define __MyLuaLoader_H

/**
 * @brief 具体参照 loadlib.c
 */
#include "lua.hpp"
#include <string>

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class MyLuaLoader
{
public:
	// 移除字符串缓冲区最后的 0 和 EOF(-1) 符号
	static int removeZeroAndEof(const char* buffer, int size);
	static int checkResult(lua_State *L, int stat, const char *filename);

	static void addCFunctionLualoader(lua_State *L);
	static void addCClosureLualoader(lua_State *L);

	static int loadLuaFromBufferUseFunction(lua_State *L);
	static int loadLuaFromFileUseFunction(lua_State *L);

	static int loadLuaFromBufferUseClosure(lua_State *L);
	static int loadLuaFromFileUseClosure(lua_State *L);

	static int loadLuaFromFile(lua_State *L, std::string fileName);
};

MY_END_NAMESPACE

#endif