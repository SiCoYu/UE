#ifndef __MyLuaLoader_H_
#define __MyLuaLoader_H_

/**
 * @brief ������� loadlib.c
 */
#include "lua.hpp"
#include <string>

void addLualoader(lua_State *L);
int loadLuaFromBuffer(lua_State *L);
int loadLuaFromFile(lua_State *L);
// �Ƴ��ַ������������� 0 �� EOF(-1) ����
int removeZeroAndEof(const char* buffer, int size);
int checkResult(lua_State *L, int stat, const char *filename);

#endif