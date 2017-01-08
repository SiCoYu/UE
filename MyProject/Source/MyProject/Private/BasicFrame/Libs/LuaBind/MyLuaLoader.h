#ifndef __MyLuaLoader_H_
#define __MyLuaLoader_H_

/**
 * @brief 具体参照 loadlib.c
 */
#include "lua.hpp"
#include <string>

void addLualoader(lua_State *L);
int loadLuaFromBuffer(lua_State *L);
int loadLuaFromFile(lua_State *L);
// 移除字符串缓冲区最后的 0 和 EOF(-1) 符号
int removeZeroAndEof(const char* buffer, int size);
int checkResult(lua_State *L, int stat, const char *filename);

#endif