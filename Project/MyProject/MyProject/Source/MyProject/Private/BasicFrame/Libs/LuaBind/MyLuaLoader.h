#ifndef __MyLuaLoader_H_
#define __MyLuaLoader_H_

/**
 * @brief ������� loadlib.c
 */
#include "lua.hpp"
#include <string>

void addCFunctionLualoader(lua_State *L);
void addCClosureLualoader(lua_State *L);
int loadLuaFromBufferUseFunction(lua_State *L);
int loadLuaFromFileUseFunction(lua_State *L);
int loadLuaFromBufferUseClosure(lua_State *L);
int loadLuaFromFileUseClosure(lua_State *L);
// �Ƴ��ַ������������� 0 �� EOF(-1) ����
int removeZeroAndEof(const char* buffer, int size);
int checkResult(lua_State *L, int stat, const char *filename);

int loadLuaFromFile(std::string fileName);

#endif